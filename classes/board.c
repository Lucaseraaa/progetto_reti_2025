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
int append_card(Board_s *board, int card_id, char* descrizione, Column_type type){
    
    // Prendo la colonna dei TO_DO
    Column_s *column = &board->_colonne[type];

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

/**
 * @brief implementazione della unassign_card_to_user
 */
void unassign_card_to_user(Board_s* board, int card_id){

    Column_s *column = &board->_colonne[TO_DO];

    // Riassegno alla lavagna la card
    edit_Card_user(column->_card, card_id, 0);

}

// gcc -I. -Iclasses -Istructs test.c classes/*.c -o test
// gcc -I. -Iclasses -Istructs -Ifunctions -Inetwork -Iserver test.c classes/*.c functions/*.c network/*.c server/*.c -o test
// gcc -I. -Iclasses -Istructs -Ifunctions test.c classes/*.c functions/*.c -o test

void print_Board(Board_s* board){

    printf("\nLavagna (%d)\n", board->_id);
    char* column_names[3] = {"TO-DO", "DOING", "DONE"};

    for(int i = 0; i < 3; i++){

        Card_s* cards;
        
        printf("\nColonna: %s\n", column_names[i]);
        for (cards = board->_colonne[i]._card; cards != NULL;cards = cards->_next){
            printf("\nTask %d", cards->_id);
            if(cards->_utente != 0 && i == 0) printf(" - in attesa di essere confermato da %d", cards->_utente);
            else if(i == 1) printf(" - preso da %d", cards->_utente);
            printf("\n%s\n", cards->_testo_attivita);
        }
    
    }
    
}

/**
 * @brief implementazione della board_to_string
 */
char* board_to_string(Board_s* board) {

    // Alloco il buffer per la stringa
    char* buffer = (char*)malloc(4096 * sizeof(char));
    if (buffer == NULL) {
        return NULL;
    }
    
    char temp[512];
    buffer[0] = '\0';
    
    // Intestazione
    sprintf(temp, "\nLavagna (%d)\n", board->_id);
    strcat(buffer, temp);
    
    char* column_names[3] = {"TO-DO", "DOING", "DONE"};
    
    for(int i = 0; i < 3; i++) { 
        Card_s* cards;
        sprintf(temp, "\nColonna: %s\n", column_names[i]);
        strcat(buffer, temp);
        
        for (cards = board->_colonne[i]._card; cards != NULL; cards = cards->_next) {
            sprintf(temp, "\nTask %d", cards->_id);
            strcat(buffer, temp);
            
            if(cards->_utente != 0 && i == 0) {
                sprintf(temp, " - in attesa di essere confermato da %d", cards->_utente);
                strcat(buffer, temp);
            }
            else if(i == 1) {
                sprintf(temp, " - preso da %d", cards->_utente);
                strcat(buffer, temp);
            }
            
            sprintf(temp, "\n%s\n", cards->_testo_attivita);
            strcat(buffer, temp);
        }
    }
    
    return buffer;
}

/**
 * @brief implementazione della Board_connection_init
 */
void Board_Connection_init(Board_s *board, int id, char* cards[]){
    
    *board = Board_init(id);
    for (int i = 0; i < 10; i++) append_card(board, i, cards[i], TO_DO);

}