/**
 * @file structs.h
 * @brief Strutture dati per il progetto
 */
#ifndef STRUCTS_H
#define STRUCTS_H
#include "enums.h"
#include "time.h"

#define COLUMN 3

/**
 * @brief Struttura dati che identifica una Card
 */
typedef struct Card{
    int _id;
    Column _colonna;
    char* _testo_attivita;
    int _utente;
    struct tm* _timestamp;
};

/**
 * @brief Struttura che identifica una colonna
 */
typedef struct Colonna{
    Column _colonna;
    Card *_card;
};

/**
 * @brief Struttura dati che identifica una Lavagna
 */
typedef struct Lavagna
{
    int _id;
    Colonna _colonne[COLUMN]; // Utilizzo un array perche nel caso di aggiunta di altri stati
                            // di una colonna la soluzione è più scalabile
    
};

#endif