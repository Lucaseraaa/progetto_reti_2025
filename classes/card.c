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
 * @brief Implementazione della get_Card_by_id
 */
Card_s* get_Card_by_id(Card_s* c, int id){

    for(Card_s* crd = c; crd != NULL; crd = crd->_next){
        if(crd->_id == id){
            return crd;
        }
    }
    return NULL;

}

/**
 * @brief Implementazione della find_free_card
 */
int find_free_card(Card_s* c, User_t usr_id){

    for(Card_s* card = c; card != NULL; card = card->_next){
        
        // Caso in cui l'utente non è ancora assegnato alla card
        if(card->_utente == 0){
            time_t rawtime;
            time(&rawtime);
        
            card->_utente = usr_id;
            card->_timestamp = *localtime(&rawtime);
        
            return card->_id;
        }
    }

    return -1;
}

/**
 * @brief implementazione della edit_Card_user
 */
int edit_Card_user(Card_s* top, int id, User_t user){

    Card_s* card = get_Card_by_id(top, id);

    if (card == NULL) return -1;
    
    card->_utente = user;
    return 0;
    
}

void print_card(Card_s* c){
    
    printf("Carta: %d\nUtente: %d\nTesto: %s\n", c->_id, c->_utente, c->_testo_attivita);

}