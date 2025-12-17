#include <string.h>
#include "command.h"
#include "classes/timer.h"

char* columns_name[] = {"TO-DO", "DOING", "DONE"};
extern Board_s kanban;
extern Timer_s* timer;

/**
 * @brief implementazione della SHOW_LAVAGNA
 */
void show_lavagna(){

    print_Board(&kanban);

}

/**
 * @brief implementazione della get_lavagna
 */
int get_lavagna(User_s* user){

    // Ottengo la lavagna
    char* board = board_to_string(&kanban);

    // Scrivo sul socket
    int sock = user->_socket; // todo: cambia con setter

    int board_len = htonl(strlen(board));

    // Invio la lunghezza della lavagna attuale
    int n = write(sock, &board_len, sizeof(int));

    if (n != sizeof(int)){
        perror("Errore nell'invio della lunghezza della lavagna");
        return -1;
    } 

    // Invio la lavanga
    int k = write(sock, board, strlen(board));
    if (k != (int)strlen(board)){
        perror("Errore nell'invio della lavagna");
        return -1;
    }

    free(board);
    
    return 0;
}


int quit(User_s* user){

    // Rimozione dei timer dell'utente
    remove_all_Timer_in_list(&timer, get_User_port(user), NONE);

    // L'utente viene eliminato
    int exit = user_exit(&kanban, user);
    printf("Ritorno: %d\n", exit);
    
    if (exit == 0) return 1;
    else return -1;
    

}

/**
 * @brief implementazione della MOVE_CARD
 */
int move_card(Board_s* board, int card_id, Column_type from, Column_type to){
    int r = switch_card_between_columns(board, card_id, from, to);
    if (r == -1) printf("Lo scambio non è stato effettuato\n");
    else printf("Card con id %d spostata con successo da %s a %s\n", card_id, columns_name[from], columns_name[to]);
    return r;
}

/**
 * @brief implementazione della HANDLE_CARD
 */
void handle_card(){

    // Scorro tutti gli utenti per assegnare una card
    for(User_s* user = kanban._usr; user != NULL; user = user->_next){

        int card_id;
        printf("HANDLE CARD\n");
        // Se l'utente ha già una card, non lo considero
        if (get_User_status(user) != USR_NOTHING) continue;
        printf("HANDLE SUCCESSO\n");
        int s = user_assign_card(&kanban, user, &card_id);
        printf("Ritorno dall'operazione: %d\n", s);
        if (s != 0) continue;

        // Invio la card all'utente
        int user_socket = user->_socket;
          
        // Invio la lista degli utenti
        insert_Timer_in_list(&timer, time(NULL) + ACK_TIME, ack_alert, get_User_port(user), ACK_TIME);

        printf("L'utente %d ha assegnata la card %d\n", user->_user, card_id);
    }

}

/**
 * @brief implementazione della ack_alert
 */
void* ack_alert(User_t user){

    printf("RIMOZIONE DELL'UTENTE %d DAL POOL A CAUSA DI ACK MANCATA\n", user);
    quit(get_User_by_port(kanban._usr, user));

}

/**
 * @brief implementazione della PONG_USER
 */
void* pong_user(User_t user){

    printf("RIMOZIONE DELL'UTENTE %d DAL POOL\n", user);
    quit(get_User_by_port(kanban._usr, user));

}

/**
 * @brief implementazione della PING_USER
 */
void* ping_user(User_t user){

    printf("EFFETTUO PING DELL'UTENTE %d\n", user);
    insert_Timer_in_list(&timer, time(NULL) + PONG_TIME, pong_user, user, PONG);

}

/**
 * @brief implementazione della ACK_CARD
 */
int ack_card(User_s* user){

    if(user_confirm_card(&kanban, get_User_port(user), 0) == -1) {
        printf("L'utente %d non può fare ACK\n", get_User_port(user));
        return -1;
    }

    generate_event_in_Timer(&timer, get_User_port(user), PING, ping_user, PING_TIME);

    return 0;

}

/**
 * @brief implementazione della CARD_DONE
 */
int card_done(User_s* user){

    int doing_card_id = get_User_card(user);
    remove_all_Timer_in_list(&timer, get_User_port(user), NONE);
    return switch_card_between_columns(&kanban, doing_card_id, DOING, DONE);
    
}

/**
 * @brief implementazione della PONG_LAVAGNA
 */
int pong_lavagna(User_s* user){


    printf("L'utente %d ha chiamato la PONG_LAVAGNA\n", get_User_port(user));

    // La funzione controlla se l'utente ha la card in doing
    if(user->_status = USR_DOING){

        // In tal caso prova ad eliminare la PONG
        int pong_delete = remove_all_Timer_in_list(&timer, get_User_port(user), PONG);

        // Nel caso di rimozione della PONG, devo rifare partire la PING
        if (pong_delete == 0) insert_Timer_in_list(&timer, time(NULL)+PING_TIME, ping_user, get_User_port(user), PING);
        
        return pong_delete;

    }else return -1;

}

/**
 * @brief implementazione della handle_command
 */
int handle_command(char* command, int sock){

    // Ottengo il rifermento all'utente che deve compiere il comando
    User_s* user = get_User_by_socket(kanban._usr, sock);
    if (user == NULL) {
        perror("Utente non trovato");
        return -1;
    }

    // Lista delle istruzioni e delle funzioni associate
    if(strcmp(command, "SHOW_LAVAGNA") == 0) return get_lavagna(user);
    else if (strcmp(command, "QUIT") == 0) return quit(user);
    else if (strcmp(command, "ACK_CARD") == 0) return ack_card(user);
    else if (strcmp(command, "CARD_DONE") == 0) return card_done(user);
    else if (strcmp(command, "PONG_LAVAGNA") == 0) return pong_lavagna(user);

    return 0;

}