#include "user/print.h"

/**
 * @brief implementazione della print_conn
 */
void print_in_conn(int card_id){

    // Stampo le informazioni relative ai comandi
    printf("Ti trovi nello stato di CONNESSIONE\nPuoi utilizzare i seguenti comandi:\n");

    // Stampo i primi comandi
    printf("- SHOW_LAVAGNA: utilizzato per stampare la lavagna\n- CREATE_CARD: utilizzato per creare una card\n");

    // Stampo l'ACK
    if (card_id != -1) printf("- ACK_CARD: per accettare la carta %d, hai 120 secondi per farlo e poi verrai disconnesso\n", card_id);

    // QUIT
    printf("- QUIT: esci\n");

}

/**
 * @brief implementazione della print_in_card
 */
void print_in_card(int card_id){

     // Stampo le informazioni relative ai comandi
    printf("Ti trovi nello stato CARD e stai gestendo la card con id %d\nPuoi utilizzare i seguenti comandi:\n", card_id);

    // Stampo i primi comandi
    printf("- SHOW_LAVAGNA: utilizzato per stampare la lavagna\n- CREATE_CARD: utilizzato per creare una card\n");

    // Stampo l'ACK
    printf("- CARD_DONE: conferma la card che hai in gestione\n");

    // QUIT
    printf("- QUIT: esci\n");

}

/**
 * @brief implementazione della print_in_card
 */
void print_in_ping(int card_id){

     // Stampo le informazioni relative ai comandi
    printf("Ti trovi nello stato di PING per la card con id %d\nPuoi utilizzare i seguenti comandi:\n", card_id);

    // Stampo i primi comandi
    printf("- SHOW_LAVAGNA: utilizzato per stampare la lavagna\n");

    printf("- CARD_DONE: conferma la card che hai in gestione\n");

    printf("- PONG_LAVAGNA: conferma che sei ancora attivo\n");

    // QUIT
    printf("- QUIT: esci\n");

}

/**
 * @brief implementazione della handle_print
 */
void handle_print(User_Status status, int card_id){

    if (status == CONN) print_in_conn(card_id);
    else if (status == CARD) print_in_card(card_id);
    else if (status == PING_USER) print_in_ping(card_id);

}

