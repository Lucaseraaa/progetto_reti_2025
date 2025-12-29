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

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/signal.h>

#include "classes/timer.h"
#include "classes/board.h"

// Riferimento esterno al timer
extern Timer_s* timer;

/**
 * @brief Funzione che registra un'utente
 * 
 * La funzione inserisce l'utente nella lista corrispettiva e incrementa i numero di utenti
 * atttivi
 * 
 * @param kanban kanban dove inserire l'utente
 * @param port porta dell'utente (ID)
 * @param descp descrittore del socket del client
 * 
 * @return ritorna 0 se l'operazione ha avuto successo, -1 altrimenti
 */
int user_register(Board_s *kanban, User_t port, int descp);

/**
 * @brief la funzione gestisce l'exit di un utente
 * 
 * La funzione permette di rimuovere un utente dalla lista nella kanban. Vengono contestualmente riadattate le strutture dati
 * corrispondenti, ed eventualmente riallocate le risorse. 
 * 
 * @param kanban lavagna
 * @param user utente da eliminare
 * 
 * @return la funzione ritorna 0 se la funzione ha successo, -1 viceversa
 */
int user_exit(Board_s *kanban, User_s* user);

/**
 * @brief Funzione che assegna ad un utente una card
 * 
 * La funzione assegna ad un'utente una card, che viene lasciata nella lista TO_DO, in attesa di riscontro
 * da parte dell'utente. Viene inoltre aggiornata la struttura dell'utente.
 * 
 * @param kanban lavagna dove trovare la card
 * @param user utente a cui assegnare la card
 * @param card_id variabile utilizzata per salvare l'id della card
 * 
 * @return ritorna 0 nel caso di successo, -1 in caso contrario
 */
int user_assign_card(Board_s* kanban, User_s* user, int* card_id);

/**
 * @brief funzione che sposta la card da TO_DO a DOING per un'utente o annulla l'operazione
 * 
 * La funzione permette all'utente di accettare o rifiutare (nel caso si sia disconnesso) una card.
 * 
 * @param kanban lavagna da utilizzare
 * @param port porta dell'utente
 * @param status posto a 0 per confermare l'operazione (TO_DO -> DOING), viceversa qualsiasi altro valore
 * 
 * @return 0 per successo, -1 viceversa
 */
int user_confirm_card(Board_s* kanban, User_t port, int status);

/**
 * @brief funzione che inizializza la kanban con le prime 10 card
 * 
 * @param board kanban da modificare
 * @param id id della lavagna
 * @param cards array di cards da inserire inizialmente nella lavagna
 */
void board_init(Board_s *board, int id, char* cards[]);

/**
 * @brief funzione che sposta una card da una colonna all'altra di una lavagna
 * 
 * La funzione controlla anche che si scambi una card SOLO tra colonne contigue
 * 
 * @param board lavagna di esecuzione
 * @param card_id id della card da spostare
 * @param from indice della colonna dalla quale viene una card
 * @param to indice della colonna dalla quale la card dev'essere inserita
 * 
 * @return la funzione ritorna 0 se lo spostamento ha avuto successo, viceversa -1
 */
int switch_card_between_columns(Board_s* board, int card_id, Column_type from, Column_type to);

/**
 * @brief funzione che permette di inserire una card in una determinata colonna
 * 
 * L'inserimento avviene in ordine di _id, la card è sempre inizializzata ad utente 0
 * 
 * @param board lavagna di inserimento
 * @param id id della card 
 * @param card_text testo della card
 * @param c colonna dove inserire la card
 * 
 * @return la funzione ritorna 0 in caso di successo, -1 viceversa
 */
int insert_card(Board_s* board, int id, char* card_text, Column_type c);

/**
 * @brief funzione handler per gestire gli alert 
 * 
 * La funzione estrae in testa il timer e chiama la funzione gestita da quell'evento
 * 
 * @param n id del segnale
 */
void timer_handler(int n);

/**
 * @brief Funzione che permette di generare un evento nel timer
 * 
 * La funzione inserisce un evento nel Timer contestualmente ai dati passati. Nel caso in cui sia inserito un evento per primo avvia un timer,
 * se ce ne sono altri lo reimposta
 * 
 * @param timer reference al timer
 * @param port porta dell'utente di riferimento
 * @param operation_type tipo di operazione da svolgere
 * @param oparion_function funzione da eseguire allo scadere del timer
 * @param add_time tempo da aggiungere al timestamp attuale per ottenere quello dell'evento
 * 
 */
void generate_event_in_Timer(Timer_s** timer, User_t port, Timer_Operation_Type operation_type, void* operation_function, int add_time);


#endif