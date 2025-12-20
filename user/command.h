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

#include  <string.h>
#include "classes/user_data.h"

#define COMMAND_LEN 15

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
void send_command(char* command);

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
 */
void create_card(int user_socket);

/**
 * @brief funzione che gestisce gli output da parte del server
 * 
 * @param command comando inviato dal server
 * @param user_socket socket di comunicazione
 */
void handle_board_request(char* command, int user_socket);

void listen_to_server();

#endif