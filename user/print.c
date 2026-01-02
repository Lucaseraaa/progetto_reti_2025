#include "user/print.h"

/**
 * @brief implementazione della print_conn
 */
void print_in_conn(int card_id, Review_User* user_needs_review, int user_needs_review_number){

    // Stampo le informazioni relative ai comandi
    printf("\nTi trovi nello stato di CONNESSIONE\nPuoi utilizzare i seguenti comandi:\n");

    // Stampo i primi comandi
    printf("- SHOW_LAVAGNA: utilizzato per stampare la lavagna\n- CREATE_CARD <task_id> <task_body>: utilizzato per creare una card\n");

    // Lista di utenti
    printf("- REQUEST_USER_LIST: richiedi la lista di utenti\n");

    if (user_needs_review_number > 0) printf("- REVIEW: conferma la revisione alla card %d relativa all'utente %d\n", user_needs_review[0].card_id, user_needs_review[0].user);

    // Stampo l'ACK
    if (card_id != -1) printf("- ACK_CARD: per accettare la carta %d, hai 120 secondi per farlo e poi verrai disconnesso\n", card_id);
    

    // QUIT
    printf("- QUIT: esci\n");

}

/**
 * @brief implementazione della print_in_ping
 */
void print_in_sleep_card(int card_id, Review_User* user_needs_review, int user_needs_review_number){

    printf("\nTi trovi nello stato SLEEP_CARD, stai svolgendo la card %d\nPuoi utilizzare i seguenti comandi:\n", card_id);
    if (user_needs_review_number > 0) printf("- REVIEW: conferma la revisione alla card %d relativa all'utente %d\n", user_needs_review[0].card_id, user_needs_review[0].user);
    else printf("Non è disponibile nessun comando in questo stato\n");

}

/**
 * @brief implementazione della print_in_card
 */
void print_in_card(int card_id, Review_User* user_needs_review, int user_needs_review_number){

    // Stampo le informazioni relative ai comandi
    printf("\nTi trovi nello stato CARD e stai gestendo la card con id %d\nPuoi utilizzare i seguenti comandi:\n", card_id);

    // Stampo i primi comandi
    printf("- SHOW_LAVAGNA: utilizzato per stampare la lavagna\n- CREATE_CARD <task_id> <task_body>: utilizzato per creare una card\n");

    // Lista di utenti
    if (review.req == 0) printf("- REVIEW_CARD: richiedi la revisione del tuo lavoro\n");
    else if (review.req  == 1 && review._remaning_users_number == 0) printf("- CARD_DONE: conferma la card che hai in gestione\n"); 
    if (user_needs_review_number > 0) printf("- REVIEW: conferma la revisione alla card %d relativa all'utente %d\n", user_needs_review[0].card_id, user_needs_review[0].user);

    // QUIT
    printf("- QUIT: esci\n");

}

/**
 * @brief implementazione della print_in_card
 */
void print_in_ping(int card_id){

     // Stampo le informazioni relative ai comandi
    printf("\nTi trovi nello stato di PING per la card con id %d\nPuoi utilizzare i seguenti comandi:\n", card_id);

    printf("- PONG_LAVAGNA: conferma che sei ancora attivo\n");

    // QUIT
    printf("- QUIT: esci\n");

}

/**
 * @brief implementazione della handle_print
 */
void handle_print(User_Status status, int card_id, Review_User* user_needs_review, int user_needs_review_number){

    if (status == CONN) print_in_conn(card_id, user_needs_review, user_needs_review_number);
    else if (status == SLEEP_CARD) print_in_sleep_card(card_id, user_needs_review, user_needs_review_number);
    else if (status == CARD) print_in_card(card_id, user_needs_review, user_needs_review_number);
    else if (status == PING_USER) print_in_ping(card_id);

}

