/**
 * @file card.h
 * 
 * Modulo che contiene le funzioni relativi agli User
 * 
 * @author Luca Serafini
 * @date Novembre 2025
 */

#ifndef USER_H
#define USER_H

#include "structs/enums.h"

typedef struct User_s{

    User_t _user; // Id dell'utente (numero di porta)

    struct User_t* next; // Lista degli utenti

}User_s;

#endif