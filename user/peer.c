#include "user/peer.h"

/**
 * @brief implementazione della Review_User_init
 */
Review_User_s* Review_User_init(User_Data_s* ud){

    // Creazione dell'oggetto
    Review_User_s* r = malloc(sizeof(Review_User_s));
    if (r == NULL) return NULL;

    // Imposto il numero di utenti
    r->_remaning_users_number = ud->_connected_users;  

    // Inserimento delle porte
    r->_remaning_users = malloc(r->_remaning_users_number*sizeof(User_t));
    if (r->_remaning_users == NULL) return NULL;

    for (int i = 0; i < r->_remaning_users_number; i++) r->_remaning_users[i] = ud->_others[i];
    
    return r;

}

/**
 * @brief implementazione della Review_User_delete
 */
void Review_User_delete(Review_User_s* ru){

    free(ru->_remaning_users);

    free(ru);

}

/**
 * @brief implementazione della refresh_review_users
 */
int refresh_review_users(Review_User_s* ru, User_Data_s* ud){

    // Imposto il numero di utenti
    ru->_remaning_users_number = ud->_connected_users;  

    // Inserimento delle porte
    free(ru->_remaning_users);
    ru->_remaning_users = malloc(ru->_remaning_users_number*sizeof(User_t));
    if(ru->_remaning_users == NULL) return -1;

    for (int i = 0; i < ru->_remaning_users_number; i++) ru->_remaning_users[i] = ud->_others[i];

    return 0;
}

/**
 * @brief implementazione della review_complete
 */
int review_complete(User_Data_s* ud, User_t user){
    if (ud == NULL) return -1;

    // Utenti 
    Review_User_s* r = &review; 

    if (r->_remaning_users == NULL || r->_remaning_users_number <= 0) {
        return -1; // Nessun utente da rimuovere o array non inizializzato
    }

    int found_index = -1;

    // Creazione dell'indice dell'utente
    for (int i = 0; i < r->_remaning_users_number; i++) {
        if (r->_remaning_users[i] == user) {
            found_index = i;
            break;
        }
    }

    // Se non trovo l'utente
    if (found_index == -1) return -1; 
    
    // Riallineo l'array
    for (int i = found_index; i < r->_remaning_users_number - 1; i++) r->_remaning_users[i] = r->_remaning_users[i + 1];
    r->_remaning_users_number--;

    // Ridimensiono la memoria
    if (r->_remaning_users_number == 0) {
    
        free(r->_remaning_users);
        r->_remaning_users = NULL;
    
    } else {
        
        // Riduco la dimensione dell'array
        User_t* temp = realloc(r->_remaning_users, r->_remaning_users_number * sizeof(User_t));
        
        // Controllo di sicurezza su realloc (anche se in riduzione raramente fallisce)
        if (temp != NULL) {
            r->_remaning_users = temp;
        }
    }

    return 0;
}

/**
 * @brief funzione di utilità per cercare se esiste un utente nella lista
 */
int is_user_in_list(User_t user, User_t* list, int list_size) {

    for (int i = 0; i < list_size; i++) {
        if (list[i] == user) {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief implementazione della filter_disconnected_users
 */
void filter_disconnected_users(Review_User_s* ru, User_t* current_users, int connected_count) {
    int write_idx = 0;

    // Controllo gli utenti rimasti
    for (int i = 0; i < ru->_remaning_users_number; i++) {
        if (is_user_in_list(ru->_remaning_users[i], current_users, connected_count)) {
            ru->_remaning_users[write_idx++] = ru->_remaning_users[i];
        }
    }
    ru->_remaning_users_number = write_idx;

}