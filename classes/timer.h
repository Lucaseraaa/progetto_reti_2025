/**
 * @file timer.h
 * 
 * Modulo che contiene le funzioni relativi al Timer
 * 
 * @author Luca Serafini
 * @date Dicembre 2025
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "structs/enums.h"

#define PING_TIME 10
#define PONG_TIME 10
#define ACK_TIME 120

// Struttura dati relativa al timer
typedef struct Timer_s {

    time_t _timestamp; // Timestamp di quando avviare una funzione

    void* _function; // Puntatore alla funzione

    Timer_Operation_Type _operation; // Tipo di operazione

    User_t _param; // Parametro della funzione

    struct Timer_s* _next; // Puntatore al prossimo elemento della lista
    
} Timer_s;

typedef void (*TimerCallback)(int);

/**
 * @brief Funzione che inizializza un timer
 * 
 * @param remining_time tempo rimasto al timer
 * @param function puntatore alla funzione da eseguire allo scadere del timer
 * @param param parametro della funzione
 * @param type tipo di operazione da svolgere
 * 
 * @return puntatore al nuovo timer, altrimenti NULL
 */

Timer_s* Timer_init(time_t timestamp, void* function, int param, Timer_Operation_Type type);

/**
 * @brief funzione che elimina il timer, deallocando le strutture dati
 * 
 * @param t elemento da deallocare
 */
void Timer_delete(Timer_s* t);

/**
 * @brief funzione che estrae un elemento dalla testa di una lista timer
 * 
 * @param lista di estrazione
 * 
 * @return NULL se la lista è vuota, riferimento all'elemento se ha successo
 */
Timer_s* Timer_extract(Timer_s** list);

/**
 * @brief funzione che ritorna il tempo che deve passare per il prossimo alert
 * 
 * La funzione fa una differenza tra il timestamp attuale e quello indicato nel primo elemento del timer
 * di modo da ottenere il tempo da aspettare per il prossimo alert 
 * 
 * @param list timer
 * 
 * @return la funzione ritorna il tempo 
 */
int get_next_timer(Timer_s* list);

/**
 * @brief funzione utilizzata per inserire un timer nella lista
 * 
 * L'inserimento avviene in ordine crescente in base al remining_time
 * Nel caso in cui venisse inserita prima di un elemento, il remining time del successivo deve essere decrementato del remining_time
 * del nuovo Timer
 * 
 * @param list lista dove inserkire il nuovo timer
 * @param remining_time tempo rimasto al timer
 * @param function puntatore alla funzione da eseguire allo scadere del timer
 * @param param parametro della funzione, ovvero la porta dell'utente
 * @param type tipo di operazione da svolgere
 * 
 * @return 1 se avviene inserimento in testa, 0 se ha successo senza inserimento in testa, -1 se ci sono errori
 */
int insert_Timer_in_list(Timer_s** list, time_t timestamp, void* function, User_t param, Timer_Operation_Type type);

/**
 * @brief funzione che rimuove tutti gli eventi nel timer relativi ad un utente
 * 
 * Tramire il parametro type si deve specificare NONE se si vuole eliminare un evento qualsiasi, oppure il tipo se serve specifico
 * 
 * @param list timer
 * @param user porta dell'utente
 * @param type tipo di evento
 * 
 * @return 0 se ha successo, -1 viceversa
 */
int remove_all_Timer_in_list(Timer_s** list, User_t user, Timer_Operation_Type type);

/**
 * @brief funzione che permette di eseguire la funzione in testa alla lista
 * 
 * @param list lista da cui estrarre la funzione
 * 
 * @return la funzione ritorna -1 in caso di errore, 1 nel caso in cui dopo l'estrazione la lista diventa vuota, 0 negli altri casi
 */
int execute_Timer_head_function(Timer_s** list);

void print_timer_list(Timer_s* list);

#endif