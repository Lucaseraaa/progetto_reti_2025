#include <stdio.h>
#include <stdlib.h>
#include "classes/board.h"
#include "structs/enums.h"

/**
 * @brief implementazione della Board_init
 */
Board_s Board_init(int id){
    
    // Dichiarazione board
    Board_s kanban;
    
    kanban._id = id;

    // Inizializzo delle column vuote
    for (int i = 0; i < 3; i++) kanban._colonne[i] = Column_init(i);

    return kanban;

}



void print_Board(Board_s* board){

    printf("| - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - |\n");
    printf("|                                                Lavagna - %d                                               |\n", board->_id);
    printf("| - - - - - - - - - - - - - - - - - | - - - - - - - - - - - - - - - - - | - - - - - - - - - - - - - - - - - |\n");
    printf("|               To Do               |               Doing               |               Done!               |\n");
    printf("| - - - - - - - - - - - - - - - - - | - - - - - - - - - - - - - - - - - | - - - - - - - - - - - - - - - - - |\n");
    
}