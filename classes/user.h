/**
 * @file card.h
 * 
 * Modulo che contiene le funzioni relativi agli User
 * 
 * @author Luca Serafini
 * @date Novembre 2025
 */

#ifndef USER_H
#define USER_H

#include "structs/enums.h"

typedef struct User_s{

    User_t _user; // Id dell'utente (numero di porta)

    int _actual_managed_card; // carta attualmente utilizzata dall'utente

    User_card_status _status; // Stao della carta dell'utente

    struct User_s* _next; // Lista degli utenti

}User_s;


/**
 * @brief Funzione che inizializza un user
 * 
 * La funzione crea un'utente nello heap e lo ritorna
 * 
 * @param usr id dell'utente da creare
 * 
 * @return la funzione ritorna il riferimento all'User nel caso abbia successo, NULL altrimenti
 */
User_s* User_init(User_t usr);

/**
 * @brief distruttore dell'User
 * 
 * La dunzione libera lo spazio occupato da un User
 * 
 * @param user utente da eliminare
 */
void User_delete(User_s* user);

/**
 * @brief funzione che crea un utente e lo inserisce in lista utenti della board
 * 
 * L'inserimento dell'utente avviene in ordine di porta
 * 
 * @param users lista degli utenti della lavagna
 * @param usr id del nuovo utente
 * 
 * @return ritorna 0 se ha successo, -1 altrimenti
 */
int insert_User_in_list(User_s** users, User_t usr);

/**
 * @brief La funzione estrae un'utente dalla lista
 * 
 * La funzione scorre la lista per cercare l'utente usr, se lo trova lo elimina
 * 
 * @param usr id dell'utente da estrarre
 * 
 * @return la funzione ritorna 0 se l'utente è stato trovato, -1 altrimenti
 */
int extract_User(User_s** user_list, User_t usr);

/**
 * @brief La funzione ottiene il riferimento ad un'utente tramite il suo id
 *
 * @param top riferimento alla lista degli utenti
 * @param port porta dell'utente da ottenere
 * 
 * @return la funzione ritorna il riferimento all'utente se esiste, altrimenti NULL
 */
User_s* get_User_by_port(User_s* top, User_t port);

/**
 * @brief Ottiene lo stato relativo all'utente
 * 
 * @param user utente 
 * 
 * @return stato dell'utente
 */
User_card_status get_User_status(User_s* user);

/**
 * @brief Ottiene la card relativa all'utente
 * 
 * @param user utente 
 * 
 * @return id della card dell'utente
 */
int get_User_card(User_s* user);

/**
 * @brief La funzione permette di modificare la card dell'utente
 * 
 * La funzione assegna all'utente nella lista la card ad esso assegnata
 * 
 * @param user utente a cui modificare lo stato
 * @param card_id id della card
 * 
 * @return la funzione ritorna 0 se ha successo, -1 altrimenti
 */
int set_User_card(User_s* user, int card_id);

/**
 * @brief La funzione permette di modificare lo stato dell'utente
 * 
 * La funzione assegna all'utente nella lista lo stato in cui si deve trovare
 * 
 * @param user utente a cui modificare lo stato
 * @param status stato che deve essere modificato
 * 
 * @return la funzione ritorna 0 se ha successo, -1 altrimenti
 */
int set_User_status(User_s* user, User_card_status status);

/**
 * @brief 
 */
void get_Users(User_s* top, User_t users[], int users_number);

/**
 * @brief debug print function
 */
void prova_print(User_s *user_list);

#endif