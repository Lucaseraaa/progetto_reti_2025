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

#include <time.h>
#include "structs/enums.h"


/**
 * @brief Struttura dati che identifica una Card
 */
typedef struct {
    int _id;
    Column _colonna;
    char* _testo_attivita;
    int _utente;
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
Card_s* Card_init(int id, Column colonna, const char* testo, int utente);

/**
 * @brief Funzione utilizzata per deallocare una Card
 * 
 * La funzione dealloca una Card selezionata dallo HEAP
 * 
 * @param c Card da deallocare
 */
void Card_delete(Card_s* c);


#endif