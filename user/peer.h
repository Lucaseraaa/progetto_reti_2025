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
#include <string.h>
#include "structs/enums.h"
#include "user_data.h"


typedef struct Review_User_s{

    User_t* _remaning_users; // Array di utenti che non hanno risposto alla review della card

    int _remaning_users_number; // Dimensione dell'array _remaning_users

    int req;

}Review_User_s;

extern Review_User_s review;

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
 * @brief funzione che dealloca una variabile di tipo Review_User_s
 * 
 * @param ru riferimento all'oggetto da eliminare
 */
void Review_User_delete(Review_User_s* ru);

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


/**
 * @brief funzione che filtra gli utenti della Review_User
 * 
 * La funzione elimina dagli utenti rimanenti quelli che non sono più attivi
 * 
 * @param ru riferimento alla Review_User
 * @param current_users array degli utenti correnti
 * @param connected_count numero degli utenti presenti in current_users
 */
void filter_disconnected_users(Review_User_s* ru, User_t* current_users, int connected_count);


/**
 * @brief funzione che invia a tutti gli utenti della Review_User un messaggio
 * 
 * @param ru riferimento alla review user
 * @param user_sock socket UDP per l'invio dei messaggi
 * @param card_id id della card della revisione
 */
void send_all_users_notification(Review_User_s* ru, int user_sock, int card_id);

#endif