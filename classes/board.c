#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


// gcc -I. -Iclasses -Istructs test.c classes/*.c -o test

void print_Board(Board_s* board){

    printf("| - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - |\n");
    printf("|                                                Lavagna - %d                                               |\n", board->_id);
    printf("| - - - - - - - - - - - - - - - - - | - - - - - - - - - - - - - - - - - | - - - - - - - - - - - - - - - - - |\n");

    for (int i = 0; i < COLUMN_NUMBER; i++){
        
        Column_s column = board->_colonne[i];
        printf("COLONNA NUMBER: %d\n", column._card_number);
        for (Card_s* scorri = column._card; scorri != NULL; scorri = scorri->_next){
            
            // Stampo il Task num
            printf("| Task %d\n", scorri->_id);

            char* task = scorri->_testo_attivita;
            int task_len = strlen(task);
            int init = 0;

            while(task_len != 0){
                printf("%.*s", init, task+init+task_len-1);
                task_len -= (task_len >= 107) ? 107 : task_len;
                printf("\n");
            }
            

        }

    }

    printf("|               To Do               |               Doing               |               Done!               |\n");
    printf("| - - - - - - - - - - - - - - - - - | - - - - - - - - - - - - - - - - - | - - - - - - - - - - - - - - - - - |\n");
    
}