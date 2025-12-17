/**
 * @file command.h
 * 
 * Modulo che contiene i comandi che può chiamare il client.
 * 
 * @author Luca Serafini
 * @date Dicembre 2025
 */

#ifndef USER_COMMAND_H
#define USER_COMMAND_h

#include "classes/user_data.h"

extern User_Data_s user_data;

/**
 * @brief funzione che permette di ricevere la lavagna e stamparla
 */
void show_lavagna();


#endif