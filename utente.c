#include "user/connection.h"

int main(int argc, char* argv[]){

    if (argc != 2){
        printf("È necessario inserire un parametro per identificare la porta dell'utente\n");
        exit(EXIT_FAILURE);
    }
    client_main(atoi(argv[1]));
    
}