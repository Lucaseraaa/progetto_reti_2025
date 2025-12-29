
#include "classes/user_data.h"

/**
 * @brief implementazione della User_Data_init
 */
void User_Data_init(User_Data_s* ud, User_t port){

    ud->_port = port;
    ud->_status = DIS;
    ud->_card_id = -1;
    ud->_connected_users = 0;
    ud->_board_socket = ud->_user_socket = -1;
    ud->_users_need_review_number = 0;

    ud->_others = NULL;
    ud->_users_need_review = NULL;

}

/**
 * @brief implementazione della User_Data_delete
 */
void User_Data_delete(User_Data_s* ud){

    free(ud->_others);
    free(ud->_users_need_review);

}

/**
 * @brief funzione che chiude la connessione tra utente e lavagna e tra utente e gli altri utenti
 * 
 * La funzione chiude i socket eventualmente attivi e elimina eventuale memoria heap
 * 
 * @param ud riferimento all'User_Data
 */
void user_close(User_Data_s* ud){
    
    // Chiudo i socket
    if (ud->_board_socket != -1) close(ud->_board_socket);
    if (ud->_user_socket != -1) close(ud->_user_socket);

    User_Data_delete(ud);

}

/**
 * @brief implementazione della user_connect
 */
int user_connect(User_Data_s* ud, int connected_user, User_t users[], int user_sock){

    // Non posso andare a CON da altri stati se non DIS e CARD
    if (ud->_status != DIS && ud->_status != CARD) return -1;

    // Assegno CONN allo stato
    ud->_status = CONN;
    ud->_connected_users = connected_user;

    if(connected_user > 0){

        ud->_others = malloc(connected_user*sizeof(User_t));
        for(int i = 0; i < ud->_connected_users; i++) ud->_others[i] = ntohl(users[i]);

    }

    if (user_sock != -1) ud->_board_socket = user_sock;

    return 0;
    
}

/**
 * @brief implementazione della others_users
 */
int other_users(User_Data_s* ud, int connected_user, User_t users[]){
    
    if (ud->_status != CARD && ud->_status != CONN) return -1;

    ud->_connected_users = connected_user;
    free(ud->_others); // Libero l'array precedente 

    if(connected_user > 0){

        ud->_others = malloc(connected_user*sizeof(User_t));
        for(int i = 0; i < ud->_connected_users; i++) {

            ud->_others[i] = ntohl(users[i]);

        }
    }

    return 0;

}

/**
 * @brief implementazione della user_handle_card
 */
int user_handle_card(User_Data_s* ud, int card_id){
    
    if(ud->_status != CONN) return -1;

    ud->_card_id = card_id;
    return 0;

}

/**
 * @brief implementazione della append_user_review
 */
void push_user_review(User_Data_s* ud, Review_User user_card_to_review){

    // Controllo se l'utente è già presente
    for (int i = 0; i < ud->_users_need_review_number; i++) {
        if (ud->_users_need_review[i].user == user_card_to_review.user) {
            // Utente già presente, non aggiungo nulla
            return;
        }
    }

    // Aumento il numero di utenti che richiedono revizione
    ud->_users_need_review_number++;

    // Realloco la memoria, per gestire un utente in più
    Review_User* temp = realloc(ud->_users_need_review, ud->_users_need_review_number * sizeof(Review_User));

    // Fallisco nel caso non ci sia più memoria disponibile
    if (temp == NULL) {
        perror("Errore di memoria, fallisco: ");
        exit(EXIT_FAILURE);
        return; 
    }

    // Aggiorno l'array
    ud->_users_need_review = temp;
    ud->_users_need_review[ud->_users_need_review_number - 1] = user_card_to_review;

}

void pop_user_review(User_Data_s* ud){

    if (ud->_users_need_review_number <= 0 || ud->_users_need_review == NULL) return;

    if (ud->_users_need_review_number == 1) {
        
        // Caso in cui ci sia un solo utente 
        free(ud->_users_need_review);
        ud->_users_need_review = NULL;
        ud->_users_need_review_number = 0;
    
    } 
    else {

        // Caso in cui ci sono più utenti
        // Shifto tutti gli utenti a sinistra di una posizione
        memmove(
            ud->_users_need_review,           
            ud->_users_need_review + 1,       
            (ud->_users_need_review_number - 1) * sizeof(Review_User) 
        );

        // 5. Riduco la dimensione dell'array
        int new_count = ud->_users_need_review_number - 1;
        Review_User* temp = realloc(ud->_users_need_review, new_count * sizeof(Review_User));
        
        // Nota: realloc in riduzione difficilmente fallisce, ma è bene aggiornare
        if (temp != NULL) {
            ud->_users_need_review = temp;
        }
        
        ud->_users_need_review_number = new_count;
        printf("HO SOLO UN CONTROLLO DA FARE: %d\n", ud->_users_need_review_number);
    }
    printf("PER SICUREZZA: %d\n", ud->_users_need_review_number);

}

void print_debug(User_Data_s* ud){

    printf("DEBUG PRINT\n");

    printf("UTENTE: %d\nStato: %d\nSocket: %d\nUtenti:\n", ud->_port, ud->_status, ud->_board_socket);

    for(int i = 0; i < ud->_connected_users; i++){
        printf("%d\n", ud->_others[i]);
    }
}

