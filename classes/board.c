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
    kanban._connected_user = 0;
    kanban._usr = NULL;

    // Inizializzo delle column vuote
    for (int i = 0; i < 3; i++) kanban._colonne[i] = Column_init(i);

    return kanban;

}

/**
 * @brief implementaziione della append_card
 */
int append_card(Board_s *board, int card_id, char* descrizione){
    
    // Prendo la colonna dei TO_DO
    Column_s *column = &board->_colonne[TO_DO];

    Card_s *new_card = Card_init(card_id, TO_DO, descrizione, 0); // Utente 0 è la lavagna 
    
    if (new_card == NULL) return -1;

    insert_card_in_Column(column, new_card);
    return 0;

}

/**
 * @brief implementazione della assign_card_to_User
 */
int assign_card_to_User(Board_s *board, User_t usr_id, int* card_id){
    
    Column_s *column = &board->_colonne[TO_DO];

    // Controllo che esista la card da assegnare
    *card_id = find_free_card(column->_card, usr_id);
    if (*card_id == -1) return -1;

    return 0;

}

/**
 * @brief implementazione della confirm_card_to_User
 */
int confirm_card_to_User(Board_s *board, int card_id){

    return swap_card_between_Column(card_id, &board->_colonne[TO_DO], &board->_colonne[DOING]);

}

// gcc -I. -Iclasses -Istructs test.c classes/*.c -o test
// gcc -I. -Iclasses -Istructs -Ifunctions test.c classes/*.c functions/*.c -o test

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