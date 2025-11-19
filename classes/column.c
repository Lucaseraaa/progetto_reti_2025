#include <stdio.h>
#include "classes/column.h"

/**
 * @brief Implementazione della funzione Colonna_init
 */
Column_s Column_init(Column_type column){

    Column_s colonna;

    colonna._column = column;
    colonna._card = NULL;
    colonna._card_number = 0;

    return colonna;

}

/**
 * @brief implementazione della funzione insert_card_in_Column
 */
void insert_card_in_Column(Column_s* column, Card_s* card){

    // Nel caso non faccia parte della colonna, lo faccio diventare
    card->_colonna = column->_column;

    // Caso semplice, la lista è vuota
    if (column->_card == NULL){
        column->_card = card;
        return;
    }

    // Trovo l'ultima card 
    Card_s *it_card;
    for(it_card = column->_card; it_card->_next != NULL; it_card = it_card->_next);

    it_card->_next = card;

    return;

}

/**
 * @brief Implementazione della funzione print_all_Cards
 */
void print_all_Cards(Column_s column){

    for(Card_s* c = column._card; c != NULL; c = c->_next) print_card(c);

}