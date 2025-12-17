#include "user/command.h"

/**
 * @brief implementazione della show_lavagna
 */
void show_lavagna(){

    // Ottengo il socket dell'utente 
    int user_socket = user_data._board_socket;
    
    int board_size;
    recv(user_socket, &board_size, sizeof(int), 0);

    // Dimensione corretta della lavagna
    board_size = ntohl(board_size);
    char lavagna[board_size];
    
    // Ricevo la lavagna
    if (recv(user_socket, &lavagna, board_size, 0) < board_size){
        printf("Non sono riuscito a stampare la lavagna, non è arrivata intera!"); 
        return;
    }

    // Stampo la lavagna
    printf("%s", lavagna);


}