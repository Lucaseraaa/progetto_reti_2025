#include <string.h>
#include "command.h"

char* columns_name[] = {"TO-DO", "DOING", "DONE"};
extern Board_s kanban;

/**
 * @brief implementazione della SHOW_LAVAGNA
 */
void show_lavagna(Board_s* board){

    print_Board(board);

}

/**
 * @brief implementazione della get_lavagna
 */
int get_lavagna(User_s* user){

    // Ottengo la lavagna
    char* board = board_to_string(&kanban);

    // Scrivo sul socket
    int sock = user->_socket; // todo: cambia con setter

    int board_len = strlen(board);
    char board_len_str[5]; // Dichiaro la lunghezza massima della lavagna
    sprintf(board_len_str, "%d", board_len);

    // Invio la lunghezza della lavagna attuale
    int n = write(sock, board_len_str, strlen(board_len_str));
    if (n != strlen(board_len_str)){
        perror("Errore nell'invio della lunghezza della lavagna");
        return -1;
    } 

    // Invio la lavanga
    int k = write(sock, board, strlen(board));
    if (k != strlen(board)){
        perror("Errore nell'invio della lavagna");
        return -1;
    }

    return 0;
}


int quit(User_s* user){

    // L'utente viene eliminato
    int exit = user_exit(&kanban, user);
    printf("Ritorno: %d", exit);
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
 * @brief implementazione della handle_command
 */
int handle_command(char* command, int sock){

    User_s* user = get_User_by_socket(kanban._usr, sock);
    
    if (user == NULL) {
        perror("Utente non trovato");
        return -1;
    }

    if(strcmp(command, "SHOW_LAVAGNA") == 0) return get_lavagna(user);
    else if (strcmp(command, "QUIT") == 0) return quit(user);

    return 0;

}