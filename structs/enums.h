/**
 * @file enums.h
 * @brief File che definisce gli enum necessari al progetto
 */
#ifndef enums_h
#define enums_h

#define MIN_PORT 5679

/**
 * @brief enum che definisce i possibili stati delle colonne
 */
typedef enum {
    TO_DO,
    DOING,
    DONE
} Column_type;

/**
 * @brief enum che definisce i possibili stati di un'utente in una card
 */
typedef enum {
    USR_NOTHING,
    USR_TO_DO,
    USR_DOING
} User_card_status;

typedef unsigned int User_t;

#endif