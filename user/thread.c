#include "user/thread.h"

/**
 * @brief implementazione della thread_simulate_job
 */
void* thread_simulate_job(void* arg){
    
    int duration = *((int*)arg);
    free(arg); // Libera memoria allocata per l'argomento

    printf("INIZIO JOB DA %d secondi\n", duration);
    // sleep(duration);    

    // Sveglio la select che recepisce il termine della sleep
    char msg = 'D';
    write(pipe_fd[1], &msg, 1);
    return NULL;

}