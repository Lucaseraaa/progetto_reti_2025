/**
 * @file function_board.h
 * 
 * Modulo che contiene le funzioni utilizzabili dalla lavagna
 * 
 * @author Luca Serafini
 * @date Dicembre 2025
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "structs/enums.h"
#include <stdio.h>


/**
 * @brief funzione che inizializza la coda del timer
 * 
 * @param q riferimento alla coda dircolare
 */
void Queue_Init(Timer_Queue *q);

int Queue_IsFull(Timer_Queue *q);

int Queue_IsEmpty(Timer_Queue *q);

int Queue_Push(Timer_Queue *q, Timer_Event event);

int Queue_Pop(Timer_Queue *q, Timer_Event *event_out);


#endif