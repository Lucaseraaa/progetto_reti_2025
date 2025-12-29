#include "user/connection.h"

// Compila
// gcc -W -I. -Inetwork -Iclasses -Iuser testu.c network/*.c classes/*.c user/*.c -o testu 

// Dichiarazione della User_Data_s per mentenere i dati necessari a comunicare con la lavagna
// e con gli altri host
// @note dev'essere inizializzata
User_Data_s user_data;

// Variabile utilizzata per controllare gli utenti che hanno fatto la review della propria carta
// @note la variabile va inizializzata
Review_User_s review;

void client_main(int user){

    // Inizializzazione dell'istanza user_data
    User_Data_init(&user_data, user);

    // Buffer per inserire i comandi
    char comando[COMMAND_SIZE];

    // Strutture necessarie per il socket TCP
    struct sockaddr_in server_addr;
    int user_socket;

    // Strutture necessarie per il socket UDP
    struct sockaddr_in udp_addr;
    int udp_socket;

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
    send(user_socket, string_port, strlen(string_port), MSG_WAITALL);

    // Ricevo il numero di utenti
    int users_number;
    if (recv(user_socket, &users_number, sizeof(users_number), 0) < 0){
        printf("Dati non arrivati correttamente\n");
        exit(EXIT_FAILURE);
    }

    users_number = ntohl(users_number);  // Conversione 

    // Ho inserito un numero scorretto di porta, chiudo la connessione e fallisco
    if(users_number == -1) {
        
        printf("Il numero di porta %d non va bene, termino!\n", user);
        close(user_socket);
        exit(EXIT_FAILURE);

    }

    // Verifico che non sia il primo utente
    if (users_number > 0){
        
        // Dichiarazione array utenti e richiesta
        User_t users[users_number];
    
        if(recv(user_socket, &users, users_number*sizeof(User_t), MSG_WAITALL) < 0){
            printf("Dati non arrivati correttamente\n");
            exit(EXIT_FAILURE);
        }

        user_connect(&user_data, users_number, users, user_socket);

    }else user_connect(&user_data, users_number, NULL, user_socket);

    // Creazione del socket udp
    if (creare_udp_socket(&udp_socket, &udp_addr, user) == -1){
        close(user_socket);
        exit(EXIT_FAILURE);
    }

    // Setto il socket UDP destinato agli utenti
    user_data._user_socket = udp_socket;

    // Ciclo infinito 
    listen_to_server();

}