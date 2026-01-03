#include "classes/board.h"

#define COL_WIDTH 30
#define MAX_LINES 64
#define SEP " | "
#define MAX_LINES 64
#define BUFFER_WRITE_LEN 16384

/**
 * @brief implementazione della Board_init
 */
Board_s Board_init(int id){
    
    // Dichiarazione board
    Board_s kanban;
    
    kanban._id = id;
    kanban._connected_user = 0;
    kanban._usr = NULL;

    // Inizializzo delle column vuote
    for (int i = 0; i < 3; i++) kanban._colonne[i] = Column_init(i);

    return kanban;

}

/**
 * @brief implementazione della check_if_id_exists_in_board
 */
int check_if_id_exists_in_board(Board_s* board, int id){

    for(int i = 0; i < 3; i++){

        for(Card_s* crd = board->_colonne[i]._card; crd != NULL; crd = crd->_next){
            if(crd->_id == id) return 0;
        }

    }

    return -1;

}

/**
 * @brief implementaziione della append_card
 */
int append_card(Board_s *board, int card_id, char* descrizione, Column_type type){
    
    // Prendo la colonna dei TO_DO
    Column_s *column = &board->_colonne[type];

    // Controllo se l'id esiste già
    if (check_if_id_exists_in_board(board, card_id) == 0) return -1;

    Card_s *new_card = Card_init(card_id, TO_DO, descrizione, 0); // Utente 0 è la lavagna 
    
    if (new_card == NULL) return -1;

    if (insert_card_in_Column(column, new_card) != 0){
        Card_delete(new_card);
        return -1;
    }

    return 0;

}

/**
 * @brief implementazione della assign_card_to_User
 */
int assign_card_to_User(Board_s *board, User_t usr_id, int* card_id){
    
    Column_s *column = &board->_colonne[TO_DO];

    // Controllo che esista la card da assegnare
    *card_id = find_free_card(column->_card, usr_id);
    if (*card_id == -1) return -1;

    return 0;

}

/**
 * @brief implementazione della confirm_card_to_User
 */
int confirm_card_to_User(Board_s *board, int card_id){

    return swap_card_between_Column(card_id, &board->_colonne[TO_DO], &board->_colonne[DOING]);

}

/**
 * @brief implementazione della unassign_card_to_user
 */
void unassign_card_to_user(Board_s* board, int card_id){

    Column_s *column = &board->_colonne[TO_DO];

    // Riassegno alla lavagna la card
    edit_Card_user(column->_card, card_id, 0);

}

void print_Board(Board_s* board){

    printf("%s\n", board_to_string(board));
    
}

/**
 * @brief implementazione di wrap_text
 */
int wrap_text(const char* text, char lines[MAX_LINES][COL_WIDTH + 1]) {
    int line = 0, col = 0;
    for (const char* p = text; *p && line < MAX_LINES; p++) {
        if (*p == '\n') {
            lines[line][col] = '\0';
            line++;
            col = 0;
            continue;
        }
        lines[line][col++] = *p;
        if (col == COL_WIDTH) {
            lines[line][col] = '\0';
            line++;
            col = 0;
        }
    }
    if (col > 0 && line < MAX_LINES) {
        lines[line][col] = '\0';
        line++;
    }
    return line;
}

/**
 * @brief implementazione della board_to_string
 */
char* board_to_string(Board_s* board) {

    // Alloco un buffer per scrivere la lavagna
    char* buffer = malloc(BUFFER_WRITE_LEN); 
    if (!buffer) return NULL;
    buffer[0] = '\0';

    char temp[512];

    // Titolo 
    sprintf(temp, "\nLavagna - %d\n\n", board->_id);
    strcat(buffer, temp);

    // Intestazioni colonne
    sprintf(temp,
        "%-*s%s%-*s%s%-*s\n",
        COL_WIDTH, "TO-DO", SEP,
        COL_WIDTH, "DOING", SEP,
        COL_WIDTH, "DONE");
    strcat(buffer, temp);

    // Linea tratteggiata sotto intestazioni
    sprintf(temp,
        "%-*s%s%-*s%s%-*s\n",
        COL_WIDTH, "------------------------------", SEP,
        COL_WIDTH, "------------------------------", SEP,
        COL_WIDTH, "------------------------------");
    strcat(buffer, temp);

    // Puntatori alle liste di card
    Card_s* c[3] = {
        board->_colonne[0]._card,
        board->_colonne[1]._card,
        board->_colonne[2]._card
    };

    while (c[0] || c[1] || c[2]) {
        char lines[3][MAX_LINES][COL_WIDTH + 1];
        int line_count[3] = {0};

        for (int i = 0; i < 3; i++) {
            if (c[i]) {
                char fulltext[1024];
                sprintf(fulltext, "Task %d\n%s", c[i]->_id, c[i]->_testo_attivita);
                line_count[i] = wrap_text(fulltext, lines[i]);
            }
        }

        // Massimo numero di righe per questa riga di task
        int max_lines = line_count[0];
        if (line_count[1] > max_lines) max_lines = line_count[1];
        if (line_count[2] > max_lines) max_lines = line_count[2];

        // Stampa riga per riga allineata
        for (int l = 0; l < max_lines; l++) {
            sprintf(temp,
                "%-*s%s%-*s%s%-*s\n",
                COL_WIDTH, (l < line_count[0]) ? lines[0][l] : "", SEP,
                COL_WIDTH, (l < line_count[1]) ? lines[1][l] : "", SEP,
                COL_WIDTH, (l < line_count[2]) ? lines[2][l] : ""
            );
            strcat(buffer, temp);
        }

        // Linea tratteggiata tra task
        sprintf(temp,
            "%-*s%s%-*s%s%-*s\n",
            COL_WIDTH, "------------------------------", SEP,
            COL_WIDTH, "------------------------------", SEP,
            COL_WIDTH, "------------------------------");
        strcat(buffer, temp);

        // Avanza nelle liste
        for (int i = 0; i < 3; i++) if (c[i]) c[i] = c[i]->_next;
    }

    return buffer;
}

/**
 * @brief implementazione della Board_connection_init
 */
void Board_Connection_init(Board_s *board, int id, char* cards[]){
    
    *board = Board_init(id);
    for (int i = 0; i < INIT_CARD_NUMBER; i++) append_card(board, i, cards[i], TO_DO);

}