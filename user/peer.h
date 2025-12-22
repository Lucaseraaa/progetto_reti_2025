/**
 * @file peer.h
 * 
 * Modulo che contiene le funzioni peer relative agli utenti
 * 
 * @author Luca Serafini
 * @date Dicembre 2025
 */


#ifndef PEER
#define PEER

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "structs/enums.h"
#include "user_data.h"

typedef struct Review_User_s{

    User_t* _remaning_users; // Array di utenti che non hanno risposto alla review della card

    int _remaning_users_number; // Dimensione dell'array _remaning_users

}Review_User_s;

/**
 * @brief funzione che inizializza una variabile del tipo Review_User_s
 * 
 * La funzione copia gli utenti _others dalla User_Data_s selezionata, per poi interagire con essa in
 * altre funzioni
 * 
 * @param ud istanza di User_Data_s 
 * 
 * @return ritorna il puntatore al nuovo elemento se ha successo, altrimenti NULL
 */
Review_User_s* Review_User_init(User_Data_s* ud);

/**
 * @brief funzione che allinea gli utenti rispetto alla User_Data_s aggiornata
 * 
 * @param ru Review_user da modificare
 * @param ud istanza di User_Data_s
 * 
 * @return 0 se ha successo, -1 altrimenti
 */
int refresh_review_users(Review_User_s* ru, User_Data_s* ud);

/**
 * @brief la funzione segnala che l'utente con port user ha compiuto l'azione di revisione
 * 
 * Viene eliminato dall'array degli utenti rimasti
 * 
 * @param ud elemento che contiene l'array
 * @param user utente da rimuovere
 * 
 * @return 0 se ha successo, -1 viceversa
 */
int review_complete(User_Data_s* ud, User_t user);

#endif