#include "classes/timer.h"

/**
 * @brief implementazione della Timer_init
 */
Timer_s* Timer_init(time_t timestamp, void* function, int param, Timer_Operation_Type type){

    Timer_s* new_timer = malloc(sizeof(Timer_s));
    if(new_timer == NULL) return NULL;

    new_timer->_timestamp = timestamp;
    new_timer->_operation = type;
    new_timer->_function = function;
    new_timer->_param = (User_t)param;
    new_timer->_next = NULL;

    return new_timer;

}

/**
 * @brief implementazione della Timer_delete
 */
void Timer_delete(Timer_s* t){
    free(t);
}

/**
 * @brief implementazione della Timer_extract
 */
Timer_s* Timer_extract(Timer_s** list){
    
    // Lista vuota, non si fa nulla
    if (*list == NULL) return NULL;

    if ((*list)->_next == NULL) {
        Timer_s* ref = *list;
        (*list) = NULL;
        return ref;
    }  

    Timer_s* ref = (*list);
    (*list) = (*list)->_next;
    return ref;

}

/**
 * @brief implementazione della get_next_timer
 */
int get_next_timer(Timer_s* list){

    if (list != NULL){
        time_t first_timestamp = list->_timestamp;
        int r = first_timestamp - time(NULL); 
        return r < 0 ? 0 : r;
    }else{
        return -1;
    }

}

/**
 * @brief implementazione della insert_Timer_in_list
 */
int insert_Timer_in_list(Timer_s** list, time_t timestamp, void* function, User_t param, Timer_Operation_Type type){

    // Creo il nuovo timer
    Timer_s* new_timer = Timer_init(timestamp, function, param, type);
    if (new_timer == NULL) return -1; // FALLISCO
    
    if (*list == NULL || (*list)->_timestamp >= new_timer->_timestamp){
        
        // Caso inserimento in testa
        new_timer->_next = *list;
        *list = new_timer;

        return 1;

    }else{

        Timer_s* current = *list;

        while (current->_next != NULL && current->_next->_timestamp < new_timer->_timestamp) {
            current = current->_next;
        }

        // Inserisci il nodo
        new_timer->_next = current->_next;
        current->_next = new_timer;
        
        return 0;

    }

}

/**
 * @brief implementazione della remove_all_Timer_in_list
 */
int remove_all_Timer_in_list(Timer_s** list, User_t user, Timer_Operation_Type type){
    
    printf("Rimozione degli eventi per l'utente %d\n", user);

    Timer_s *current = *list;
    Timer_s *prev = NULL;

    while (current != NULL) {
        
        if (current->_param == user && (type == NONE || current->_operation == type)) {
            
            if (prev == NULL) {
                    
                // Rimozione in testa
                *list = current->_next;

            } else {

                // Rimozione in altri punti
                prev->_next = current->_next;

            }
            
            Timer_delete(current);
            
            return 0;
            
        }

        // Avanziamo nella lista
        prev = current;
        current = current->_next;
    
    }

    // Elemento non trovato
    return -1;
}

/**
 * @brief implementazione della execute_Timer_head_function
 */
int execute_Timer_head_function(Timer_s** list){

    printf("ESECUZIONE DEL TIMER\n");
    Timer_s* timer = Timer_extract(list);
    
    if(timer == NULL) return -1;

    TimerCallback callback = (TimerCallback) timer->_function;
    callback(timer->_param);

    // Deallocazione del timer
    Timer_delete(timer);

    if (*list == NULL) return 0;
    else return 1;

}

void print_timer_list(Timer_s* list) {
    Timer_s* current = list;
    int index = 0;

    printf("\n========== STATO LISTA TIMER ==========\n");

    if (current == NULL) {
        printf(" [Lista Vuota]\n");
        printf("=======================================\n\n");
        return;
    }

    while (current != NULL) {
        // --- Conversione Timestamp in stringa leggibile ---
        char time_str[30];
        // localtime converte il timestamp raw in struttura data/ora locale
        struct tm* tm_info = localtime(&current->_timestamp);
        // strftime formatta la data come: YYYY-MM-DD HH:MM:SS
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);

        // --- Stampa del nodo ---
        printf("NODO #%d\n", index);
        printf("  Address Memoria : %p\n", (void*)current);
        printf("  Timestamp (Raw) : %ld\n", (long)current->_timestamp);
        printf("  Timestamp (Leg) : %s\n", time_str);
        printf("  Function Ptr    : %p\n", current->_function);
        printf("  Operation Type  : %d\n", current->_operation); // Stampa l'enum come intero
        printf("  Param           : %d\n", current->_param);
        printf("  Next Timer      : %p\n", (void*)current->_next);
        printf("---------------------------------------\n");

        // Passa al prossimo
        current = current->_next;
        index++;
    }
    
    printf("Totale elementi: %d\n", index);
    printf("=======================================\n\n");
}