/**
 * @file board.h
 * 
 * Modulo che contiene le funzioni per interagire con le struct Board_s
 * 
 * @author Luca Serafini
 * @date Novembre 2025
*/

#ifndef BOARD_H
#define BOARD_H

#include "classes/column.h"
#include "structs/enums.h"
#include "classes/user.h"

#define COLUMN_NUMBER 3
#define COLUMN_NAMES {"TO_DO", "DOING", "DONE"}
#define MAX_CARD_LEN 30


/**
 * Struttura dati che definisce una Lavagna
 */
typedef struct Board_s{
    int _id;
    int _connected_user;
    User_s* _usr;
    Column_s _colonne[COLUMN_NUMBER]; // Utilizzo un array perche nel caso di aggiunta di altri stati
                            // di una colonna la soluzione è più scalabile
    
} Board_s;

/**
 * @brief funzione che inizializza una lavagna
 * 
 * La funzione crea una kanban con id specificato
 * 
 * @param id id della kanban
 * 
 * @return kanban creata
 */
Board_s Board_init(int id);

/**
 * @brief funzione che crea una card e la inserisce nella colonna "TO_DO"
 * 
 * La funzione inizializza la card, la assegna a se stessa (per convenzione user = 0) e la inserisce nella colonna
 * del TO_DO
 * 
 * @param board kanban dove inserire la card
 * @param card_id id della card da creare
 * @param descrizione descrizione della card da creare
 * 
 * @return ritorna 0 se ha successo, -1 se da errore
 */
int append_card(Board_s *board, int card_id, char* descrizione);

/**
 * @brief funzione che assegna una card ad un utente
 * 
 * La funzione cerca se esiste una card libera, se esiste la assegna all'utente selezionato
 * ma la lascia in doing
 * 
 * @param board kanban di riferimento
 * @param usr_id utente a cui assegnare la card
 * @param card_id parametro utilizzato per ritornare l'id della card selezionata
 * 
 * @return ritorna 0 se l'operazione ha successo, -1 se non esiste nessuna card
 */
int assign_card_to_User(Board_s *board, User_t usr_id, int* card_id);

/**
 * @brief funzione che conferma la card ad un utente, spostandola in DOING
 * 
 * La funzione sposta la card identificata da card_id dalla lista TO_DO a DOING
 * 
 * @param board board di riferimento
 * @param card_id id della card di riferimento
 * 
 * @return ritorna 0 se la funzione ha avuto successo, -1 altrimenti
 */
int confirm_card_to_User(Board_s *board, int card_id);

/** 
 * @brief funzione che toglie ad un utente la gestione della card
 * 
 * La funzione permette di rimuovere da una card il suo campo utente, riassegnandola alla
 * lavagna
 * 
 * @param board board di riferimento
 * @param card_id id della card da modificare
*/
void unassign_card_to_user(Board_s* board, int card_id);

/**
 * @brief funzione che ritorna la stringa da stampare come "kanban"
 * 
 * La funzione ritorna una stringa che contiene la lavagna, per essere condivisa con i client
 * 
 * @param board lavagna da stampare
 * 
 * @return stringa contenente la lavagna
 * 
 * @note Una volta utilizzata la stringa, chiamare la free() su di essa per evitare
 *       memory leak
 */
char* board_to_string(Board_s* board);

void print_Board(Board_s* board);

/**
 * @brief Funzione di inizializzazione della connessione della lavagna
 * 
 * Viene inizializzata la lavagna e gli vengono assegnate le 10 card iniziali
 * 
 * @param board lavagna da modificare
 * @param id id della lavagna
 * @param cards array delle cards con cui inizializzare la lavagna
 */
void Board_Connection_init(Board_s *board, int id,  char* cards[]);

#endif