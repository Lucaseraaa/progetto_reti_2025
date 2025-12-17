/**
 * @file user_data.h
 * 
 * Modulo che le strutture dati utili all'utente
 * 
 * @author Luca Serafini
 * @date Dicembre 2025
 */

#ifndef USERDATA_H
#define USERDATA_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "structs/enums.h"

typedef struct User_Data_s{

    User_t _port; // Porta dall'utente
    
    User_Status _status; // Stato dell'utente

    int _card_id; // Id della card eventualmente processata
    
    User_t* _others; // Array dinamico della lista degli altri utenti connessi

    int _connected_users; // Numero di utenti connessi

    int _board_socket; // Socket relativo alla lavagna 

    int _user_socket; // Socket relativo all'utente

} User_Data_s;

/**
 * @brief costruttore della classe User_Data
 * 
 * La funzione inizializza un'istanza di User_Data_s, a partire dallo stato "DIS"
 * con _card_id = -1 
 * 
 * @param ud riferimento all'oggetto User_Data da modificare
 * @param port porta dell'utente indicato
 */
void User_Data_init(User_Data_s* ud, User_t port);

/**
 * @brief distruttore della classe User_Data
 * 
 * La funzione dealloca l'array degli altri utenti connessi
 * 
 * @param ud riferimento all'istanza di User Data
 */
void User_Data_delete(User_Data_s* ud);

void user_close(User_Data_s* ud);

/**
 * @brief funzione che modifica lo stato da DIS a CONN di un User_Data
 * 
 * @param ud riferimento all'User_data
 * @param connected_user numero di utenti connessi
 * @param users array degli utenti
 * @param user_sock descrittore del socket, per lasciarlo così mettere -1
 * 
 * @return 0 se ha successo, -1 viceversa
 */
int user_connect(User_Data_s* ud, int connected_user, User_t users[], int user_sock);

void print_debug(User_Data_s* ud);

#endif