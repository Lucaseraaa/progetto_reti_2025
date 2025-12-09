/**
 * @file utils.h
 * 
 * Modulo che contiene funzioni di utilità relative ai socket/networking.
 * 
 * @author Luca Serafini
 * @date Dicembre 2025
 */
#ifndef NET_UTILS_H
#define NET_UTILS_H

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

/**
 * @brief funzione utilizzata per la creazione di un socket
 * 
 * La funzione prende in ingresso dei dati e restituisce il descrittore del socket del server
 * 
 * @param address indirizzo del server
 * @param port porta del server
 * @param type tipo di socket
 * @param server_address sockaddr_in del server
 * 
 * @return ritorna il descrittore del socket appena creato
 */
int create_socket(const char* address, int port, enum __socket_type type, struct sockaddr_in* server_address);

#endif