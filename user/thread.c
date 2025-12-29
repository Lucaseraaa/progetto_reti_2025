#include "user/thread.h"

/**
 * @brief implementazione della thread_simulate_job
 */
void* thread_simulate_job(void* arg){
    
    int duration = *((int*)arg);
    free(arg); // Libera memoria allocata per l'argomento

    printf("Simulazione del job! Attendere %d secondi prima di inviare la card\n", duration);
    sleep(duration);    

    // Sveglio la select che recepisce il termine della sleep
    char msg = 'D';
    write(pipe_fd[1], &msg, 1);
    return NULL;

}