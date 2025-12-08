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

/**
 * @brief la funzione gestisce l'exit di un utente
 * 
 * La funzione permette di rimuovere un utente dalla lista nella kanban. Vengono contestualmente riadattate le strutture dati
 * corrispondenti, ed eventualmente riallocate le risorse. 
 * 
 * @param kanban lavagna
 * @param port porta dell'utente
 * 
 * @return la funzione ritorna 0 se la funzione ha successo, -1 viceversa
 */
int user_exit(Board_s *kanban, User_t port);

/**
 * @brief Funzione che assegna ad un utente una card
 * 
 * La funzione assegna ad un'utente una card, che viene lasciata nella lista TO_DO, in attesa di riscontro
 * da parte dell'utente. Viene inoltre aggiornata la struttura dell'utente.
 * 
 * @param kanban lavagna dove trovare la card
 * @param port porta dell'utente richiedente
 * @param card_id variabile utilizzata per salvare l'id della card
 * 
 * @return ritorna 0 nel caso di successo, -1 in caso contrario
 */
int user_assign_card(Board_s* kanban, User_t port, int* card_id);

/**
 * @brief funzione che sposta la card da TO_DO a DOING per un'utente o annulla l'operazione
 * 
 * La funzione permette all'utente di accettare o rifiutare (nel caso si sia disconnesso) una card.
 * 
 * @param kanban lavagna da utilizzare
 * @param port porta dell'utente
 * @param card_id id della card da modificare
 * @param status posto a 0 per confermare l'operazione (TO_DO -> DOING), viceversa qualsiasi altro valore
 */
void user_confirm_card(Board_s* kanban, User_t port, int card_id, int status);

#endif