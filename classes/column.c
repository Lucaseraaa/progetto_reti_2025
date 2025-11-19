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

Card_s* extract_card_with_id(int id, Column_s* column){

    Card_s* it_card;
    Card_s* prec_card;
    for(
        it_card = column->_card, prec_card = NULL;
        it_card != NULL && it_card->_id != id;
        prec_card = it_card,it_card = it_card->_next
    );

    // Non ho trovato l'elemento
    if (it_card == NULL) return NULL;
    else if (prec_card == NULL) column->_card = column->_card->_next;
    else if (it_card->_next != NULL) prec_card->_next = it_card->_next;
    else prec_card->_next = NULL;

    it_card->_next = NULL;

    return it_card;
}

int swap_card_between_Column(int card_id, Column_s *src, Column_s *dest){

    Card_s* switching_card = extract_card_with_id(card_id, src);
    if (switching_card == NULL) return -1;
    insert_card_in_Column(dest, switching_card);  
    return 1;

}

/**
 * @brief Implementazione della funzione print_all_Cards
 */
void print_all_Cards(Column_s column){

    for(Card_s* c = column._card; c != NULL; c = c->_next) print_card(c);

}
