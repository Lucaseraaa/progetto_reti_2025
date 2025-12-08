/**
 * @file function_board.h
 * 
 * Modulo che contiene le funzioni utilizzabili dalla lavagna
 * 
 * @author Luca Serafini
 * @date Dicembre 2025
 */

#ifndef FUNCTION_BOARD_H
#define FUNCTION_BOARD_H

#include"classes/board.h"

/**
 * @brief Funzione che registra un'utente
 * 
 * La funzione inserisce l'utente nella lista corrispettiva e incrementa i numero di utenti
 * atttivi
 * 
 * @param kanban kanban dove inserire l'utente
 * @param port porta dell'utente (ID)
 * 
 * @return ritorna 0 se l'operazione ha avuto successo, -1 altrimenti
 */
int user_register(Board_s *kanban, User_t port);


#endif