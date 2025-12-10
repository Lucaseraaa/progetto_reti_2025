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

#endif
