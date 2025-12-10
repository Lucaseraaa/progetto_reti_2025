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
#include "functions/functions_board.h" 


/**
 * @brief Funzione che mostra la lavagna
 * 
 * La funzione scrive a schermo l'attuale configurazione della lavagna
 * 
 * @param board riferimento alla lavagna da stampare
 */
void show_lavagna(Board_s* board);

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

#endif
