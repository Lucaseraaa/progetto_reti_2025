/**
 * @file user_data.h
 * 
 * Modulo che contiene le print da inviare all'utente
 * 
 * @author Luca Serafini
 * @date Dicembre 2025
 */

#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <unistd.h>
#include "structs/enums.h"

/**
 * @brief funzione per stampare i comandi nello stato di CONN
 * 
 * La funzione stampa i comandi che possono essere effettuati in questo stato, prende card_id,
 * nel caso in cui sia diveso da 0 stampa anche il comando di ACK
 * 
 * @param card_id id della card presa in carico dall'utente
 */
void print_in_conn(int card_id);

/**
 * @brief funzione per stampare i comandi nello stato CARD
 * 
 * @param card_id id della card che stà venendo gestita
 */
void print_in_card(int card_id);

/**
 * @brief funzione per stampare i comandi nello stato PING_USER
 * 
 * @param card_id id della card che ha ricevuto il PING dalla lavagna
 */
void print_in_ping(int card_id);

/**
 * @brief funzione utilizzata per stampare i comandi a seconda dello status dell'utente
 * 
 * La funzione prende in considerazione i parametri della firma per chiamare la funzione corretta
 * 
 * @param status stato in cui si trova l'utente
 * @param card_id id della card
 * 
 */
void handle_print(User_Status status, int card_id);

#endif