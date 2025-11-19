#include <stdio.h>
#include "classes/card.h"
#include "classes/colonna.h"
#include "structs/enums.h"

/**
 * @brief Implementazione della funzione Colonna_init
 */
Colonna_s Colonna_init(Column column){

    Colonna_s colonna;

    colonna._column = column;
    colonna._card = NULL;
    colonna._card_number = 0;

    return colonna;

}
