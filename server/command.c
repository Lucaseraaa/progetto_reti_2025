#include "command.h"

char* columns_name[] = {"TO-DO", "DOING", "DONE"};

/**
 * @brief implementazione della SHOW_LAVAGNA
 */
void show_lavagna(Board_s* board){

    print_Board(board);

}

/**
 * @brief implementazione della MOVE_CARD
 */
int move_card(Board_s* board, int card_id, Column_type from, Column_type to){
    int r = switch_card_between_columns(board, card_id, from, to);
    if (r == -1) printf("Lo scambio non è stato effettuato\n");
    else printf("Card con id %d spostata con successo da %s a %s\n", card_id, columns_name[from], columns_name[to]);
    return r;
}