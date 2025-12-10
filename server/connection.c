
#include "server/connection.h"
#include "network/utils.h"
#include "functions/functions_board.h"
#include "classes/user.h"

// Variabile condivisa: lavagna
// Va acceduta tramite un semaforo durante le funzioni della sezione critica
// @note La kanban va inizializzata 
Board_s kabnan;

// Le 10 cards da inivare alla lavagna appena partita
// I progetti verranno inizializzati con ID crescenti da 0 a 9
char* cards[10] = {
    "Inizio del progetto",
    "Divisione dei ruoli",
    "Creazione del gruppo Whatsapp",
    "Creazione della mailing list",
    "Scelta del nome del progetto",
    "Schedulazione del calendario",
    "Creazione del progetto sulla piattaforma",
    "Divisione dei gruppi di lavoro",
    "Acquisto dei computer",
    "Creazione di un mockup"
};

void board_main(){

    struct sockaddr_in server_addr, client_addr;
    
    // Inizializzazione della kanban
    board_init(&kabnan, SERVER_PORT, cards);

    // (Primo comando secondo specifiche) mostro la lavagna appena creata
    show_lavagna(&kabnan);

    // Test
    move_card(&kabnan, 1, TO_DO, DOING);
    move_card(&kabnan, 2, TO_DO, DOING);
    move_card(&kabnan, 1, DOING, DONE);
    move_card(&kabnan, 1, TO_DO, DONE);

    show_lavagna(&kabnan);

    // Creazione del socket per la lavagna (server)
    int server_socket = create_socket(SERVER_ADDRESS, SERVER_PORT, SOCK_STREAM, &server_addr);
    if(server_socket == -1) exit(EXIT_FAILURE);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        perror("Errore nel bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 10) < 0){
        perror("Errore nella listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Lavagna in ascolto all'indirizzo %s e sulla porta %d\n", SERVER_ADDRESS, SERVER_PORT);

    // Ciclo infinito del server
    while(1){
        
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);

        // Non riesco a collegare il client
        if(client_socket < 0){
            perror("Il socket dell'utente ha dato errore");
            continue;
        }

        printf("Client connesso\n");

        Board_Connection_s* connection = malloc(sizeof(Board_Connection_s));
        char port_str[PORT_BUFFER_LENGTH];

        int port_read = read(client_socket, port_str, PORT_BUFFER_LENGTH);
        
        if(port_read < 0){
            perror("Non riesco a connettere il client");
            continue;
        }

        User_t port = (User_t)atoi(port_str);
        
        user_register(&kabnan, port);
        prova_print(kabnan._usr);
        
        printf("Connetto client con id %d\n", port);
        
        close(client_socket);

    }
}   