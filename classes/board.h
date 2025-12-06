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
#define COLUMN_NAMES ["TO_DO", "DOING", "DONE"]
#define MAX_CARD_LEN 30


/**
 * Struttura dati che definisce una Lavagna
 */
typedef struct Board_s{
    int _id;
    User_t* usr;
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
 */
void append_card(Board_s *board, int card_id, char* descrizione);

void print_Board(Board_s* board);

#endif