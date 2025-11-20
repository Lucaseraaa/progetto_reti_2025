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

#define COLUMN_NUMBER 3
#define COLUMN_NAMES ["TO_DO", "DOING", "DONE"]
#define MAX_CARD_LEN 30


/**
 * Struttura dati che definisce una Lavagna
 */
typedef struct Board_s{
    int _id;
    Column_s _colonne[COLUMN_NUMBER]; // Utilizzo un array perche nel caso di aggiunta di altri stati
                            // di una colonna la soluzione è più scalabile
} Board_s;


Board_s Board_init(int id);

void print_Board(Board_s* board);

#endif