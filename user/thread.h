/**
 * @file thread.h
 * 
 * Modulo che contiene le funzioni dei thread.
 * 
 * @author Luca Serafini
 * @date Dicembre 2025
 */

#ifndef USER_THREAD_H
#define USER_THREAD_h

#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

extern int pipe_fd[2];

/**
 * @brief thread che simula un job, ovvero lo svolgimento della card
 * 
 * Il thread chiama una sleep di un tempo casuale e poi, tramite la pipe, lo comunica al thread principale
 * 
 * @param arg argomento passato al thread, inutilizzato
 */
void* thread_simulate_job(void* arg);

#endif