#include "functions/functions_board.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

/**
 * @brief implementazione della user_register
 */
int user_register(Board_s *kanban, User_t port){
    
    // Controllo che l'utente abbia inserito la porta corretta
    if (port < MIN_PORT) {
        printf("Devi inserire una porta maggiore di 5678\n");
        return -1;
    }
    // Inserimento dell'utente in lista
    User_s **users = &kanban->_usr;
    
    int s = insert_User_in_list(users, port);

    if(s == -1){
        printf("L'utente con porta %d non è stato allocato per mancanza di spazio\n", port);
        return -1;
    }

    // Incremento il numero di utenti connessi
    kanban->_connected_user++;    

}