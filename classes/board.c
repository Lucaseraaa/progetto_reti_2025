#include <stdio.h>
#include <stdlib.h>
#include "classes/board.h"
#include "structs/enums.h"

Board_s Board_init(int id){
    
    // Dichiarazione board
    Board_s kanban;
    
    kanban._id = id;

    return kanban;

}

void print_Board(Board_s* board){

    printf("| - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - |\n");
    printf("|                                                Lavagna - %d                                               |\n", board->_id);
    printf("| - - - - - - - - - - - - - - - - - | - - - - - - - - - - - - - - - - - | - - - - - - - - - - - - - - - - - |\n");
    printf("|               To Do               |               Doing               |               Done!               |\n");
    printf("| - - - - - - - - - - - - - - - - - | - - - - - - - - - - - - - - - - - | - - - - - - - - - - - - - - - - - |\n");
    
    Column_s* columns = board->_colonne;

}