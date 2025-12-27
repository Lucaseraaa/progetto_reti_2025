#include "classes/queue.h"

/**
 * @brief implementazione della Queue_Init
 */
void Queue_Init(Timer_Queue *q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

int Queue_IsFull(Timer_Queue *q) {
    return (q->count == EVENT_QUEUE_SIZE);
}


int Queue_IsEmpty(Timer_Queue *q) {
    return (q->count == 0);
}

int Queue_Push(Timer_Queue *q, Timer_Event event) {
    if (Queue_IsFull(q)) {
        // Coda piena: non possiamo inserire
        return 0; 
    }

    // Copia l'evento nel buffer alla posizione 'tail'
    q->buffer[q->tail] = event;

    // Avanza 'tail' in modo circolare usando l'operatore modulo (%)
    q->tail = (q->tail + 1) % EVENT_QUEUE_SIZE;
    
    // Incrementa il conteggio elementi
    q->count++;

    return 1;
}

int Queue_Pop(Timer_Queue *q, Timer_Event *event_out) {
    if (Queue_IsEmpty(q)) {
        return 0;
    }

    // Copia l'evento dalla testa al puntatore di output
    *event_out = q->buffer[q->head];

    // Avanza 'head' in modo circolare
    q->head = (q->head + 1) % EVENT_QUEUE_SIZE;

    // Decrementa il conteggio
    q->count--;

    return 1;
}