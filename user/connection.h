/**
 * @file timer.h
 * 
 * Modulo che contiene le funzioni relativi al Timer
 * 
 * @author Luca Serafini
 * @date Dicembre 2025
 */

#ifndef USER_CONNECTION
#define USER_CONNECTIOn

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define COMMAND_SIZE 16
#define LOCALHOST "127.0.0.1"
#define SERVER_PORT 5678

#include "user/command.h"

/**
 * @brief funzione main del client user
 * 
 * @param user porta dell'utente
 */
void client_main(int user);

#endif