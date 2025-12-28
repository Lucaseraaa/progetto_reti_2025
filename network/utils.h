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
#include "structs/enums.h"

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

/**
 * @brief funzione utilizzata per creare un socket per la lavagna e metterlo in listen
 * 
 * @param sv_addr riferimento al descrittore dell sockaddr del server
 * @param listerner riferimento al listener
 * 
 * @return 0 se la funzione ha successo, -1 viceversa
 */
int generate_listener(struct sockaddr_in* sv_addr, int* listener);

/**
 * @brief funzione che genera un socket UDP in ascolto su tutte le porta
 * 
 * @param udp_socket puntatore al socket da creare
 * @param my_addr puntatore alla struttura dati del mio indirizzo
 * @param port porta a cui esporre il socket
 * 
 * @return 1 se ha successo, 0 altrimenti
 */
int creare_udp_socket(int* udp_socket, struct sockaddr_in* my_addr, int port);

/**
 * @brief funzione che invia un messaggio dalla board all'utente tramite il socket specificato
 * 
 * La funzione ritorna il risultato della send
 * 
 * @param sock socket su cui inviare il messaggio
 * @param commadn comando da inviare
 * 
 * @return stato si uscita della socket
 */
int send_message_to_user(int sock, Board_to_User_command command);


/**
 * @brief funzione che converte nel tipo Board_to_User_command il messaggio ricevuto dal server
 * 
 * @param net_cmd ritorno della funzione
 */
Board_to_User_command recv_message_from_board(uint32_t net_cmd);

/**
 * @brief funzione che invia un messaggio dall'utente alla board
 * 
 * La funzione ritorna il risultato della send
 * 
 * @param sock socket su cui inviare il messaggio
 * @param commadn comando da inviare
 * 
 * @return stato si uscita della socket
 */
int send_message_to_board(int sock, User_to_Board_command command);

/**
 * @brief funzione che converte nel tipo User_to_User_command il messaggio ricevuto dal server
 * 
 * @param net_cmd ritorno della funzione
 */
User_to_Board_command recv_message_from_user(uint32_t net_cmd);

#endif