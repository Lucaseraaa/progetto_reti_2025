/**
 * @file command.h
 * 
 * Modulo che contiene i comandi che può chiamare il client.
 * 
 * @author Luca Serafini
 * @date Dicembre 2025
 */

#ifndef USER_COMMAND_H
#define USER_COMMAND_h

#include <string.h>
#include <sys/select.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "classes/user_data.h"
#include "structs/enums.h"

#define COMMAND_LEN 50

extern User_Data_s user_data;

/**
 * @brief funzione utilizzato per inviare comandi sulla lavagna
 * 
 * La funzione verifica solamente se il comando può essere inviato in un particolare stato
 * 
 * @param command comando da inviare
 * 
 * @note il comando dev'essere precedentemente controllato prima di essere inviato
 */
void send_command(User_to_Board_command command);

/**
 * @brief funzione che permette di ricevere la lavagna e stamparla
 */
void show_lavagna();

/**
 * @brief funzione che assegna ad un utente una card
 * 
 * L'utente dovrà poi confermarla per poterla successivamente svolgere
 * 
 * @param user_socket socket dell'utente al quale assrgnare la card
 */
void handle_card(int user_socket);

/**
 * @brief funzione utilizzata creare una nuova card nella lavagna
 * 
 * La funzione può fallire se esiste già un'altra card con lo stesso ID
 * 
 * @param user_socket socket dell'utente
 * @param id id della card
 * @param body body della card
 */
void create_card(int user_socket, int id, char* body);

void handle_command(char* command, int board_sock, User_Status status);

/**
 * @brief funzione utilizzata per richiedere ed aggiornare la lista degli utenti connessi alla lavagna
 * 
 * @param user_socket socket dell'utente
 */
void user_request_user_list(int user_socket);

/**
 * @brief funzione che gestisce gli output da parte del server
 * 
 * @param command comando inviato dal server
 * @param user_socket socket di comunicazione
 */
void handle_board_request(Board_to_User_command command, int user_socket);

void listen_to_server();

#endif