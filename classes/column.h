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

/**
 * @brief Funzione che estrae una Card da una lista di una Column
 * 
 * La funzione estrae una Card dalla corrispondente lista della column
 * con id specificato nei parametri
 * 
 * @param id id della Card da estrarre
 * @param column colonna da dove estrarre la card
 * 
 * @return ritorna il riferimento alla Card se esiste, altrimenti NULL 
 */
Card_s* extract_card_with_id(int id, Column_s* column);

/**
 * @brief Funzione che scambia una card dalla coda di una colonna ad un'altra
 * 
 * La funzione scambia la Card con identificativo specificato dalla colonna 
 * sorgente, se esiste, a quella destinataria
 * 
 * @param id id della Card da spostare
 * @param src Column da dove estrarre la card
 * @param dest Column dove inserire la Card
 * 
 * @return ritorna 0 se l'operazione ha successo, -1 altrimenti
 */
int swap_card_between_Column(int card_id, Column_s *src, Column_s *dest);

#endif