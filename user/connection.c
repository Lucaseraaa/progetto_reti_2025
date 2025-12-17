#include "user/connection.h"
#include "network/utils.h"

// Compila
// gcc -W -I. -Inetwork -Iuser testu.c network/*.c user/*.c -o testu 

void client_main(int user){

    // Buffer per inserire i comandi
    char comando[COMMAND_SIZE];
    memset(comando, 0, COMMAND_SIZE);

    // Strutture necessarie per il socket
    struct sockaddr_in server_addr;
    int user_socket;

    // Inizializzazione dell'utente
    printf("Benvenuto utente %d\nSono disponibili i seguenti comandi:\n- HELLO\n", user);

    do {
        
        fgets(comando, COMMAND_SIZE, stdin);
        comando[strcspn(comando, "\n")] = 0; // Sanificazione dell'input
        if (strcmp(comando, "HELLO") != 0) printf("Il comando non è validon");

    }while(strcmp(comando, "HELLO") != 0);

    // Ottengo il descrittore del socket
    user_socket = create_socket(LOCALHOST, SERVER_PORT, SOCK_STREAM, &server_addr);
    if (user_socket == -1) exit(EXIT_FAILURE);

    // Connetto il socket
    if (connect(user_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Errore nella connect");
        close(user_socket);
        exit(EXIT_FAILURE);
    }

    char string_port[5];
    sprintf(string_port, "%d", user);

    // Pubblico nel server il mio numero di porta
    send(user_socket, string_port, strlen(string_port), 0);


}