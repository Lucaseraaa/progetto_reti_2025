#include "stdio.h"
#include <stdlib.h>
#include "string.h"
#include "time.h"
#include "structs/enums.h"
#include "card.h"

/**
 * @brief Implementazione della Card_init
 */
Card_s* Card_init(int id, Column_type colonna, const char* testo, User_t utente){
    
    // Definisco il tempo
    time_t rawtime;
    time(&rawtime);

    // Creazione della card
    Card_s* c = malloc(sizeof(Card_s));
    if (!c) return NULL;

    // Assegnazione attributi
    c->_id = id;
    c->_colonna = colonna;
    c->_utente = utente;

    // Copio testo attività
    c->_testo_attivita = strdup(testo);
    if (!c->_testo_attivita) {
        free(c);
        return NULL;
    }

    // Salvo la data
    c->_timestamp = *localtime(&rawtime);

    // Assegno a NULL il next
    c->_next = NULL;
    
    return c;

}

/**
 * @brief Implementazione della funzione Card_delete
 */
void Card_delete(Card_s* c){
    if(c) {
        free(c->_testo_attivita); // Libero il testo allocato nello heap
        free(c); 
    }
}

/**
 * @brief Implementazione della find_free_card
 */
int find_free_card(Card_s* c, User_t usr_id){

    if (c != NULL){

        // TODO timestamp
        time_t rawtime;
        time(&rawtime);
        
        c->_utente = usr_id;
        c->_timestamp = *localtime(&rawtime);
        
        return c->_id;
    
    }

    return -1;
}

void print_card(Card_s* c){
    
    printf("Carta: %d\nUtente: %d\nTesto: %s\n", c->_id, c->_utente, c->_testo_attivita);

}