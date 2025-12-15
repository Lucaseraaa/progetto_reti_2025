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

typedef struct Timer_s {

    time_t _timestamp; // Timestamp di quando avviare una funzione

    void* _function; // Puntatore alla funzione

    Timer_Operation_Type operation; // Tipo di operazione

    int _param; // Parametro della funzione

    struct Timer_s* _next; // Puntatore al prossimo elemento della lista
    
} Timer_s;

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
 * @brief funzione utilizzata per inserire un timer nella lista
 * 
 * L'inserimento avviene in ordine crescente in base al remining_time
 * Nel caso in cui venisse inserita prima di un elemento, il remining time del successivo deve essere decrementato del remining_time
 * del nuovo Timer
 * 
 * @param list lista dove inserkire il nuovo timer
 * @param remining_time tempo rimasto al timer
 * @param function puntatore alla funzione da eseguire allo scadere del timer
 * @param param parametro della funzione
 * @param type tipo di operazione da svolgere
 * 
 * @return 1 se avviene inserimento in testa, 0 se ha successo senza inserimento in testa, -1 se ci sono errori
 */
int insert_Timer_in_list(Timer_s* list, time_t timestamp, void* function, int param, Timer_Operation_Type type);

#endif