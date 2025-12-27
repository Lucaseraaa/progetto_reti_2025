/**
 * @file enums.h
 * @brief File che definisce gli enum necessari al progetto
 */
#ifndef enums_h
#define enums_h

#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

// Trova un'altra sistemazione
#define MIN_PORT 5679
#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 5678
#define EVENT_QUEUE_SIZE 32

/**
 * @brief enum che definisce i possibili stati delle colonne
 */
typedef enum {
    TO_DO,
    DOING,
    DONE
} Column_type;

/**
 * @brief enum che definisce i possibili stati di un'utente in una card
 */
typedef enum {
    USR_NOTHING,
    USR_TO_DO,
    USR_DOING
} User_card_status;

typedef unsigned int User_t;

typedef enum {
    PING, 
    PONG,
    HANDLE,
    NONE
} Timer_Operation_Type;

typedef struct Timer_Event {

    User_t user;
    Timer_Operation_Type operation;

}Timer_Event;

typedef struct Timer_Queue {

    Timer_Event buffer[EVENT_QUEUE_SIZE]; // L'array di storage
    int head;  // Indice del primo elemento (da estrarre)
    int tail;  // Indice del prossimo slot libero (dove inserire)
    int count; // Numero attuale di elementi nella coda

}Timer_Queue;

/**
 * @brief Struttura dati utilizzata per evidenziare lo stato attuale dell'utente
 */
typedef enum {

    DIS, // Utente disconnesso
    CONN, // Utente connessio e senza card
    SLEEP_CARD, // Utente ha preso la card ed è in timeout
    CARD, // Utente che ha preso una card 
    PING_USER // Utente che ha ricevuto una PING

} User_Status;

/**
 * @brief Struttura dati per inviare comandi dalla lavagna all'utente
 */
typedef enum {

    BU_HANLDE_CARD,
    BU_PING_USER,


} Board_to_User_command;

/**
 * @brief Struttura dati per inviare comandi dall'utente alla lavagna
 */
typedef enum {

    UB_QUIT,
    UB_SHOW_LAVAGNA,
    UB_ACK_CARD,
    UB_PONG_LAVAGNA,
    UB_CARD_DONE,
    UB_CREATE_CARD,
    UB_REQUEST_USER_LIST,
    UB_REVIEW_CARD,
    UB_REVIEW

} User_to_Board_command;

typedef struct User_to_User_message{

    uint16_t _sender_port;
    int16_t _command;

} User_to_User_message;
#endif