/**
 * @file colonna.h
 * 
 * Modulo che contiene le funzioni per interagire con le struct Colonna_s
 * 
 * @author Luca Serafini
 * @date Novembre 2025
 */

#ifndef COLONNA_H
#define COLONNA_H
#include "classes/card.h"
#include "structs/enums.h"

/**
 * @brief Struttura che identifica una colonna
*/
 typedef struct {
    Column_type _column;
    Card_s *_card; // Lista di card
    int _card_number; // Salva il numero di card in lista
} Column_s;

/**
 * @brief Funzione che inizializza una variabile Colonna_s
 * 
 * @param column column a cui la variabile appartiene
 * 
 * @return un'istanza di Colonna_s
 */
Column_s Colonna_init(Column_type column);

#endif