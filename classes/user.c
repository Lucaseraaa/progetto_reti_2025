#include <stdio.h>
#include <stdlib.h>
#include "classes/user.h"


/**
 * @brief implementazione della User_init
 */
User_s* User_init(User_t usr){
    
    User_s* new_user = malloc(sizeof(User_s));
    if (new_user == NULL) return NULL;

    // Creazione dell'user
    new_user->_user = usr;
    new_user->_actual_managed_card = -1;
    new_user->_status = USR_NOTHING;
    new_user->_next = NULL;
    
    return new_user;
}

/**
 * @brief implementazione della User_delete
 */
void User_delete(User_s* user){
    free(user);
}

/**
 * @brief implementazione della insert_User_in_list 
 */
int insert_User_in_list(User_s** users, User_t usr){

    User_s* new_user = User_init(usr);
    if (!new_user) return -1;

    // Caso lista vuota
    if (*users == NULL){
        *users = new_user;
        return 0;
    }

    // Trovo l'ultimo nodo
    User_s* s = *users;
    while (s->_next != NULL)
        s = s->_next;

    s->_next = new_user;
    return 0;

}

/**
 * @brief implementazione della extract_User
 */
int extract_User(User_s **user_list, User_t usr){
    
    User_s* it_usr = *user_list;
    User_s* prec_usr = NULL;

    // Cerca nodo
    while (it_usr != NULL && it_usr->_user != usr){
        prec_usr = it_usr;
        it_usr = it_usr->_next;
    }

    // Non trovato
    if (it_usr == NULL) return -1;

    // Caso: testa della lista
    if (prec_usr == NULL){
        *user_list = it_usr->_next;
    }
    else {
        // Caso: in mezzo o in fondo
        prec_usr->_next = it_usr->_next;
    }

    // Stacco e libero
    it_usr->_next = NULL;
    User_delete(it_usr);

    return 0;
}

/**
 * @brief implementazione della get_User_by_port
 */
User_s* get_User_by_port(User_s* top, User_t port){

    for(User_s* s = top; s != NULL; s = s->_next){
        if(s->_user == port) return s;
    }

    return NULL;

}

/**
 * @brief implementazione della set_User_status
 */
User_card_status get_User_status(User_s* user){
    
    return user->_status;
    
}

/**
 * @brief implementazione della set_User_status
 */
int get_User_card(User_s* user){

    return user->_actual_managed_card;
    
}

/**
 * @brief implementazione della set_User_status
 */
int set_User_status(User_s* user, User_card_status status){

    user->_status = status;
    
}

/**
 * @brief implementazione della set_User_status
 */
int set_User_card(User_s* user, int card_id){

    user->_actual_managed_card = card_id;
    
}

/**
 * Debug print function
 */
void prova_print(User_s *user_list){

    for(User_s* s = user_list; s != NULL; s = s->_next){
        printf("Utente %d\n", s->_user);
    }
}