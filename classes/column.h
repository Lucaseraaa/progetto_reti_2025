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
 typedef struct Column_s {
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
Column_s Column_init(Column_type column);

/**
 * @brief Funzione che inserisce un nuovo elemento in una coda di Card_s di una Column_s
 * 
 * L'inserimento viene effettuato semopre in coda, e il prametro colonna della Card_s
 * viene sempre sostituito da quello della card
 * 
 * @param column colonna dove inserire la carta
 * @param card carta da inserire nella coda delle colonne
 * 
 */
void insert_card_in_Column(Column_s* column, Card_s* card);

/**
 * @brief funzione di debug per stampare tutte le carde di una Column_s
 * 
 * Funzione che stampa in ordine tutte le Carte nella lista di una Column
 * 
 * @param column colonna da cui ricercare le Card
 */
void print_all_Cards(Column_s column);

#endif