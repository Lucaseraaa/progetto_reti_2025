#include "server/thread.h"

// Utilizzo della kanban dichiarata in connection.c
// @note dev'essere acceduta tramite il suo semaforo, per non causare inconsistenze
extern Board_s kanban;

void stampa(){
    print_Board(&kanban);
}