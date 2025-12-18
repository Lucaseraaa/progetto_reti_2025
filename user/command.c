#include "user/command.h"
#include "user/print.h"

/**
 * @brief implementazione della show_lavagna
 */
void show_lavagna(int request){

    // Ottengo il socket dell'utente 
    int user_socket = user_data._board_socket;

    char* show_lavagna = "SHOW_LAVAGNA\0";
    printf("LUNGHEZZA: %ld\n", strlen(show_lavagna));
    if (request == 1) send(user_socket, show_lavagna, strlen(show_lavagna), 0);
    
    int board_size;
    recv(user_socket, &board_size, sizeof(int), 0);

    // Dimensione corretta della lavagna
    board_size = ntohl(board_size);
    char lavagna[board_size];
    
    // Ricevo la lavagna
    if (recv(user_socket, &lavagna, board_size, 0) < board_size){
        printf("Non sono riuscito a stampare la lavagna, non è arrivata intera!"); 
        return;
    }

    // Stampo la lavagna
    printf("%s", lavagna);

}

void handle_card(int user_socket){

    // Voglio ricevere l'id della card
    int card_id;
    recv(user_socket, &card_id, sizeof(int), 0);
    card_id = ntohl(card_id); // La serializzo

    // Assegnazione della card
    user_handle_card(&user_data, card_id);

    printf("Ti è stata assegnata la card %d\nPuoi confermarla con il comando:\n-ACK\n", card_id);

}

/**
 * @brief implementazione della QUIT
 */
void quit(int user_socket){

    char* quit = "QUIT";
    send(user_socket, &quit, sizeof(quit), 0);
    user_close(&user_data);
    exit(0);

}

/**
 * @brief Funzione che attende che si verifichi un evento dal server
 * 
*/ 
void listen_to_server(){
    
    // Ottengo il socket dell'utente
    int user_socket = user_data._board_socket;
    char command[COMMAND_LEN];
    char input[COMMAND_LEN];

    for(;;){

        fd_set readfds;
        FD_ZERO(&readfds);

        FD_SET(user_socket, &readfds); // socket
        FD_SET(STDIN_FILENO, &readfds); // stdin

        int maxfd = (user_socket > STDIN_FILENO)
                    ? user_socket
                    : STDIN_FILENO;
        
        int activity = select(maxfd + 1, &readfds, NULL, NULL, NULL);

        if (FD_ISSET(user_socket, &readfds)) {
            memset(command, 0, COMMAND_LEN);
            int n = recv(user_socket, command, COMMAND_LEN - 1, 0);
            if (n <= 0) {
                printf("Connessione chiusa dal server\n");
                break;
            }

            command[n] = '\0';
            
            // Gestione output server
            if (strcmp(command, "HANDLE_CARD") == 0) handle_card(user_socket);
            
        }

        /* input utente */
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            memset(input, 0, COMMAND_LEN);
            if (fgets(input, COMMAND_LEN, stdin) != NULL) {

                // Sanificazione input manuale
                input[strcspn(input, "\n")] = 0; // Sanificazione dell'input

                printf("Comando richiesto: %s\n", input);

                if (strcmp(input, "QUIT") == 0) quit(user_socket);
                else if (strcmp(input, "SHOW_LAVAGNA") == 0) show_lavagna(1);

            }
        }   

        // Stampo i comandi che può effettuare l'utente
        handle_print(user_data._status, user_data._card_id);
    
    }

}