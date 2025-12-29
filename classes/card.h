/**
 * @file card.h
 * 
 * Modulo che contiene le funzioni per interagire con le struct Card_s
 * 
 * @author Luca Serafini
 * @date Novembre 2025
 */


#ifndef CARD_H
#define CARD_H

#include <stdlib.h>
// #include <stdio.h>
#include <string.h>
#include <time.h>
#include "structs/enums.h"


/**
 * @brief Struttura dati che identifica una Card
 */
typedef struct Card_s{
    int _id;
    Column_type _colonna;
    char* _testo_attivita;
    User_t _utente;
    struct tm _timestamp;
    struct Card_s* _next;
} Card_s;


/**
 * @brief Funzione utilizzata per creare una card nello heap
 * 
 * Questa funzione inizializza una Card nello HEAP, allocandola dinamicamente
 * e copiano i parametri
 * 
 * @param id id della Card
 * @param colonna colonna dove la Card è posizionata
 * @param testo stringa che contiene la descrizione della Card
 * @param utente identificativo dell'utente (porta)
 * 
 * @return ritorna la card specificata, se non c'è spazio nello heap NULL 
 * 
 * @note quando si desidera eliminare la card va deallocata tramite la funzione delete_card
 */
Card_s* Card_init(int id, Column_type colonna, const char* testo, User_t utente);

/**
 * @brief Funzione utilizzata per deallocare una Card
 * 
 * La funzione dealloca una Card selezionata dallo HEAP
 * 
 * @param c Card da deallocare
 */
void Card_delete(Card_s* c);

/**
 * @brief Funzione che permette di restituire la reference ad una card tramite il suo id
 * 
 * La funzione scorre tutte le card e trova quella con id specificato, altrimenti restituisce
 * NULL
 * 
 * @param c puntatore alla lista della card
 * @param id id della card che si vuole ricevere
 * 
 * @return puntatore alla card se esiste, altrimenti NULL
 */
Card_s* get_Card_by_id(Card_s* c, int id);

/**
 * @brief Funzione che cerca una carta libera e l'assegna all'utente specificato
 * 
 * La funzione scorre la lista delle card per trovarne una disponibile da assegnare all'utente
 * con id usr_id
 * 
 * @param c puntatore alla lista di card
 * @param usr_id id dell'utente che vuole appropiarsi della card
 * 
 * @return ritorna l'id della card se c'è n'è una disponibile, -1 altrimenti
 */
int find_free_card(Card_s* c, User_t usr_id);

/**
 * @brief Funzione di debug che stampa una Card
 * 
 * La funzione, data una Card, permette di stampare i suoi attributi
 * 
 * @param c Riferimento alla Card da stampare
 */
void print_card(Card_s* c);

/**
 * @brief Funzione che modifica l'user in una card
 * 
 * La funzione cerca la card con un determinato id e l'assegna all'utente specificato
 * 
 * @param top puntatore alla cima della lista
 * @param id id della card da modificare
 * @param user utente a cui assegnare la card
 * 
 * @return ritorna 0 se l'operazione ha successo, -1 viceversa
 */
int edit_Card_user(Card_s* top, int id, User_t user);

#endif