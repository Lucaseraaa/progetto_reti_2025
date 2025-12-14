
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "classes/user.h"
#include "structs/enums.h"
#include <arpa/inet.h>
#include <unistd.h>


/**
 * @brief implementazione della User_init
 */
User_s* User_init(User_t usr, int descp){
    
    User_s* new_user = malloc(sizeof(User_s));
    if (new_user == NULL) return NULL;

    // Creazione dell'user
    new_user->_user = usr;
    new_user->_actual_managed_card = -1;
    new_user->_status = USR_NOTHING;
    new_user->_next = NULL;
    new_user->_socket = descp;
    
    return new_user;
}

/**
 * @brief implementazione della User_delete
 */
void User_delete(User_s* user){
    
    printf("Operaziione di chiusora del socket: %d\n", close(user->_socket));
    free(user);

}

/**
 * @brief implementazione della insert_User_in_list 
 */
int insert_User_in_list(User_s** users, User_t usr, int descp){

    // Inizializzazione dell'utente
    User_s* new_user = User_init(usr, descp);
    if (!new_user) return -1;

    if (*users == NULL) {
        *users = new_user;
        return 0;
    }

    if ((*users)->_user == new_user->_user) {
        User_delete(new_user); // Pulizia dello Heap
        return -1;
    }

    if ((*users)->_user > new_user->_user) {
        new_user->_next = *users;
        *users = new_user;
        return 0;
    }

    
    User_s* current = *users;


    while (current->_next != NULL && current->_next->_user < new_user->_user) {
        current = current->_next;
    }

    if (current->_next != NULL && current->_next->_user == new_user->_user) {
        User_delete(new_user); // Pulizia dello heap
        return -1;
    }

    new_user->_next = current->_next;
    current->_next = new_user;

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
 * @brief implementazione della get_Users
 */
void get_Users(User_s* top, User_t users[], int users_number){
    
    User_s* s = top;
    for(int i = 0; i < users_number; i++, s = s -> _next){
        users[i] = s->_user;
    }

}

/**
 * @brief implementazione della get_User_by_port
 */
User_s* get_User_by_port(User_s* top, User_t port){

    for(User_s* s = top; s != NULL && s->_user <= port; s = s->_next){
        if(s->_user == port) return s;
    }

    return NULL;

}

/**
 * @brief implementazione della get_User_by_socket
 */
User_s* get_User_by_socket(User_s* top, int sock){

    for(User_s* s = top; s != NULL; s = s->_next){
        if(s->_socket == sock) return s;
    }

    return NULL;

}

/**
 * @brief implementazione della set_User_status
 */
User_t get_User_port(User_s* user){
    
    return user->_user;

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
        printf("Utente %d con socket %d\n", s->_user, s->_socket);
    }
}