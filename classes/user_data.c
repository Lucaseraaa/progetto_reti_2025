
#include "classes/user_data.h"

/**
 * @brief implementazione della User_Data_init
 */
void User_Data_init(User_Data_s* ud, User_t port){

    ud->_port = port;
    ud->_status = DIS;
    ud->_card_id = -1;
    ud->_connected_users = 0;
    ud->_others = NULL;
    ud->_board_socket = ud->_user_socket = -1;

}

/**
 * @brief implementazione della User_Data_delete
 */
void User_Data_delete(User_Data_s* ud){

    free(ud->_others);

}

/**
 * @brief funzione che chiude la connessione tra utente e lavagna e tra utente e gli altri utenti
 * 
 * La funzione chiude i socket eventualmente attivi e elimina eventuale memoria heap
 * 
 * @param ud riferimento all'User_Data
 */
void user_close(User_Data_s* ud){
    
    // Chiudo i socket
    if (ud->_board_socket != -1) close(ud->_board_socket);
    if (ud->_user_socket != -1) close(ud->_user_socket);

    User_Data_delete(ud);

}

/**
 * @brief implementazione della user_connect
 */
int user_connect(User_Data_s* ud, int connected_user, User_t users[], int user_sock){

    // Non posso andare a CON da altri stati se non DIS e CARD
    if (ud->_status != DIS && ud->_status != CARD) return -1;

    // Assegno CONN allo stato
    ud->_status = CONN;
    ud->_connected_users = connected_user;

    printf("RICONTO GLI UTENTI: %d\n", connected_user);
    if(connected_user > 0){

        ud->_others = malloc(connected_user*sizeof(User_t));
        for(int i = 0; i < ud->_connected_users; i++){
            printf("UTENTE INSERITO: %d\n", ntohl(users[i]));
            ud->_others[i] = ntohl(users[i]);
        }
    
    }

    if (user_sock != -1) ud->_board_socket = user_sock;

    return 0;
    
}

/**
 * @brief implementazione della user_handle_card
 */
int user_handle_card(User_Data_s* ud, int card_id){
    
    if(ud->_status != CONN) return -1;

    ud->_card_id = card_id;
    return 0;

}

void print_debug(User_Data_s* ud){

    printf("DEBUG PRINT\n");

    printf("UTENTE: %d\nStato: %d\nSocket: %d\nUtenti:\n", ud->_port, ud->_status, ud->_board_socket);

    for(int i = 0; i < ud->_connected_users; i++){
        printf("%d\n", ud->_others[i]);
    }
}

