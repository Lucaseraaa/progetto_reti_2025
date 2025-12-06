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
 * @brief debug print function
 */
void prova_print(User_s *user_list);

#endif