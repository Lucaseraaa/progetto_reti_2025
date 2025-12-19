#include "user/print.h"

/**
 * @brief implementazione della print_conn
 */
void print_conn(int card_id){

    // Stampo le informazioni relative ai comandi
    printf("Ti trovi nello stato di CONNESSIONE\nPuoi utilizzare i seguenti comandi:\n");

    // Stampo i primi comandi
    printf("- SHOW_LAVAGNA: utilizzato per stampare la lavagna\n- CREATE_CARD: utilizzato per creare una card\n");

    // Stampo l'ACK
    if (card_id != -1) printf("- ACK_CARD: per accettare la carta %d\n", card_id);

    // QUIT
    printf("- QUIT: esci\n");

}

/**
 * @brief implementazione della handle_print
 */
void handle_print(User_Status status, int card_id){

    if (status == CONN) print_conn(status);

}

