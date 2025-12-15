#include "classes/timer.h"
#include <stdlib.h>

/**
 * @brief implementazione della Timer_init
 */
Timer_s* Timer_init(time_t timestamp, void* function, int param, Timer_Operation_Type type){

    Timer_s* new_timer = malloc(sizeof(Timer_s));
    if(new_timer == NULL) return NULL;

    new_timer->_timestamp = timestamp;
    new_timer->operation = type;
    new_timer->_function = function;
    new_timer->_param = param;
    new_timer->_next = NULL;

    return new_timer;

}

/**
 * @brief implementazione della insert_Timer_in_list
 */
int insert_Timer_in_list(Timer_s* list, time_t timestamp, void* function, int param, Timer_Operation_Type type){

    // Creo il nuovo timer
    Timer_s* new_timer = Timer_init(timestamp, function, param, type);
    if (new_timer == NULL) return -1; // FALLISCO

    Timer_s* tim;
    Timer_s* prec_tim;
    
    if (list == NULL || list->_timestamp >= new_timer->_timestamp){
        
        // Caso inserimento in testa
        new_timer->_next = list;
        list = new_timer;

        return 1;

    }else{

        Timer_s* current = list;

        while (current->_next != NULL && current->_next->_timestamp < new_timer->_timestamp) {
            current = current->_next;
        }

        // Inserisci il nodo
        new_timer->_next = current->_next;
        current->_next = new_timer;
        
        return 0;
        
    }

}