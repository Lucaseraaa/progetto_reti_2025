#include "functions/functions_board.h"
#include "classes/timer.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/signal.h>

/**
 * @brief implementazione della user_register
 */
int user_register(Board_s *kanban, User_t port, int descp){
    
    // Controllo che l'utente abbia inserito la porta corretta
    if (port < MIN_PORT) {
        printf("Devi inserire una porta maggiore di 5678, %d non va bene!\n", port);
        return -1;
    }
    // Inserimento dell'utente in lista
    User_s **users = &kanban->_usr;
    
    int s = insert_User_in_list(users, port, descp);

    if(s == -1){
        printf("L'utente con porta %d non è stato allocato \n", port);
        return -1;
    }

    // Incremento il numero di utenti connessi
    kanban->_connected_user++;    

    return 0;
}

/**
 * @brief implementazione della user_assign_card 
 */
int user_assign_card(Board_s* kanban, User_s* user, int* card_id){

    // Ottengo l'utente con porta port
    User_t port = get_User_port(user);

    int cid;
    if (assign_card_to_User(kanban, port, &cid) == -1) return -1;
    *card_id = cid;

    int sc = set_User_card(user, *card_id);
    int ss = set_User_status(user, USR_TO_DO);

    if (!sc || !ss ) return -1;
    else return 0;

}

/**
 * @brief implementazione della user_confirm_card
 */
int user_confirm_card(Board_s* kanban, User_t port, int status){

    User_s* user = get_User_by_port(kanban->_usr, port);

    if(user == NULL) return -1;
    int card_id = get_User_card(user);

    printf("Card id: %d\n", card_id);

    if (status == 0){

        // Status == 0 --> l'utente ha accettato la card
        printf("L'utente ha accettato la card\n");
        confirm_card_to_User(kanban, card_id);
        set_User_status(user, USR_DOING);

    }else{

        // Status != 0 --> l'utente si è disconnesso o non ha accettato
        unassign_card_to_user(kanban, card_id); 
        set_User_card(user, USR_NOTHING);
        set_User_card(user, -1);

    }
    
    remove_all_Timer_in_list(&timer, get_User_port(user), NONE);
    
    return 0;
    
}

/**
 * @brief implementazione della user_exit
 */
int user_exit(Board_s *kanban, User_s* user){

    // Controllo se l'utente esiste
    int sock = user->_socket;
    int port = get_User_port(user); // Ottengo la porta dell'utente

    if (user== NULL) return -1;

    // Controllo se l'utente sta scrivendo una kanban
    int card_id = get_User_card(user);

    if (card_id != -1){

        // Devo riportare la card ad uno stato consistente
        User_card_status status = get_User_status(user);
        if (status == USR_TO_DO){
            edit_Card_user(kanban->_colonne[TO_DO]._card, card_id, 0);
        }else if (status == USR_DOING){
            edit_Card_user(kanban->_colonne[TO_DO]._card, card_id, 0);
            swap_card_between_Column(card_id, &kanban->_colonne[DOING], &kanban->_colonne[DONE]);
        }
        
    }

    // Elimino l'utente
    extract_User(&kanban->_usr, port);

    // Riduco il numero di utenti
    kanban->_connected_user--;

    printf("L'utente %d con socket %d è uscito dal gruppo!\n", port, sock);
    return 0;
}

/**
 * @brief implementazione della setup_card
 */
int insert_card(Board_s* board, int id, char* card_text, Column_type c){

    Column_s* column = &board->_colonne[c];
    Card_s *new_card = Card_init(id, c, card_text, 0);
    if (new_card == NULL) return -1;
    return insert_card_in_Column(column, new_card);
     
}

/**
 * @brief implementazione della timer_handler
 */
void timer_handler(int n){

    // Estraggo il timer in testa ed eseguo la funzione designata
    int r = execute_Timer_head_function(&timer);

    if (r == -1){
        // Caso in cui non ci sono eventi
        // Potrei aver eliminato l'unico evento dal Timer
        return;
    }

    // In base al valore di r decido cosa fare
    if (r == 0){
        // In questo caso la lista contiene altri elementi dopo l'estrazione
        // Devo rigenerare l'alert
        print_timer_list(timer);
        alarm(get_next_timer(timer));
    }else printf("Il timer non ha registrato altri eventi!\n");

}

/**
 * @brief implementazione della board_init
 */
void board_init(Board_s *board, int id, char* cards[]){

    // Utilizzo la funzione messa a disposizione dalla board.h
    Board_Connection_init(board, id, cards);

}

/**
 * @brief implementazione della switch_card_between_columns
 */
int switch_card_between_columns(Board_s* board, int card_id, Column_type from, Column_type to){

    int diff = (int)from - (int)to;
    if (abs(diff) != 1) return -1;

    return swap_card_between_Column(card_id, &board->_colonne[from], &board->_colonne[to]);

}

/**
 * @brief implementazione della generate_event_in_timer
 */
void generate_event_in_Timer(Timer_s** timer, User_t port, Timer_Operation_Type operation_type, void* operation_function, int add_time){

    // Inserimento dell'evento in lista 
    time_t event_time = time(NULL) + add_time;
    int ins = insert_Timer_in_list(timer, event_time, operation_function, port, operation_type);
    
    if (ins == 1) alarm(add_time); // Nel caso in cui aggiunga un elemento in testa, resetto il timer
    
    print_timer_list(*timer);

}
