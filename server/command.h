/**
 * @file command.h
 * 
 * Modulo che contiene i comandi che può chiamare il server.
 * 
 * @author Luca Serafini
 * @date Dicembre 2025
 */

#ifndef COMMAND_H
#define COMMAND_h

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/select.h>
#include "functions/functions_board.h" 

// Variabili globali
// Utilizzate per gestire la select
extern fd_set master;
extern fd_set read_fds;

/**
 * @brief Funzione che mostra la lavagna
 * 
 * La funzione scrive a schermo l'attuale configurazione della lavagna
 * 
 */
void show_lavagna();

/**
 * @brief funzione che restituisce all'utente la lavagna in formato stringa
 */
int get_lavagna(User_s* user);

/**
 * @brief Funzione che sposta una card da una colonna all'altra di una lavagna
 * 
 * @param board lavagna di esecuzione
 * @param card_id id della card da spostare
 * @param from indice della colonna dalla quale viene una card
 * @param to indice della colonna dalla quale la card dev'essere inserita
 * 
 * @return 0 se ha avuto successo, -1 viceversa
 */
int move_card(Board_s* board, int card_id, Column_type from, Column_type to);

/**
 * @brief Funzione che elimina l'utente dalla lavagna, riassegnando tutte le sue strutture dati
 * 
 * @param user utente da eliminare
 * 
 * @return 0 se ha successo, -1 viceversa
 */
int quit(User_s* user);

/**
 * @brief Funzione handler per la ACK mancata
 * 
 * La funzione elimina l'utente se non risponde all'ACK entro il tempo prestabilito
 * 
 * @param user utente da eliminare
 */
void *ack_alert(User_t user);

/**
 * @brief funzione che permette di assegnare ad ogni utente che non ne ha una attualmente, una card
 * 
 * La funzione scorre la lista di utenti attivi e gli assegna una card, nel caso non ne stiano gestendo altre
 */
void handle_card();

/**
 * @brief funzione che permette di fare ACK alla card presa in consegna dall'utente
 * 
 * @param user utente a cui confermare la card
 * 
 * @return 0 se ha avuto successo, -1 viceversa
 */
int ack_card(User_s* user);

/**
 * @brief funzione che permette di spostare la card di un utente dal doing al done
 * 
 * @param user utente a cui spostare la card
 * 
 * @return 0 se la funzione ha successo, -1 altrimenti
 *  
 */
int card_done(User_s* user);

/**
 * @brief la funzione permette di fare il pong alla lavagna
 * 
 * Nel caso in cui ci l'utente abbia una card in DOING fa il pong per resettare il ping ed evitare problemi
 * 
 * @param user utente
 * 
 * @return 0 se ha successo, -1 viceversa
 */
int pong_lavagna(User_s* user);

/**
 * @brief la funzione permette di inserire una card nella lavagna
 * 
 * @param user id della card da inserire
 * 
 * @return ritorna 0 se è riuscito ad inserirla, -1 viceversa
 */
int create_card(User_s* user);

/**
 * @brief funzione che ritorna all'utente la lista degli utenti attualmente connessi
 * 
 * La funzione ritorna solamente gli altri, escludendo l'utente stesso
 * 
 * @param user utente 
 */
void request_user_list(User_s* user);

/**
 * @brief funzione utilizzata per gestire i comandi
 * 
 * La funzione riceve un comando da un utente e lo gestisce 
 * 
 * @param command comando ricevuto dall'utente
 * @param sock socket dell'utente 
 * 
 * @return 0 se la funzione ha avuto successo, 1 se l'utente ha chiamato la QUIT, -1 viceversa
 */
int handle_command(Board_to_User_command command, int sock);

void *pong_user(User_t user);

void *ping_user(User_t user);


#endif
