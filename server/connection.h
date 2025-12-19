/**
 * @file connection.h
 * 
 * Modulo che contiene funzioni e strutture dati relative al server.
 * 
 * @author Luca Serafini
 * @date Dicembre 2025
 */

#ifndef CONNECTION_H
#define CONNECTION_H

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/select.h>
#include "structs/enums.h"
#include "classes/board.h"
#include "server/command.h"

#define PORT_BUFFER_LENGTH 5

typedef struct Board_Connection_s{

    struct sockaddr_in _user_addr;
    
    User_t port;

} Board_Connection_s;

void select_main();
#endif