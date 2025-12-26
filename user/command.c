#include "user/command.h"
#include "user/print.h"
#include "user/peer.h"

/**
 * @brief implementazione della send_command
 */
void send_command(char* command){

    printf("PROVA\n");
    int user_socket = user_data._board_socket;
    send(user_socket, command, strlen(command), 0);
    printf("Comando %s inviato!\n", command);

}

/**
 * @brief implementazione della show_lavagna
 */
void show_lavagna(){

    // Ottengo il socket dell'utente 
    int user_socket = user_data._board_socket;
    
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
    printf("%s\n", lavagna);

}

/**
 * @brief implementazione della HANDLE_CARD
 */
void handle_card(int user_socket){

    // Voglio ricevere l'id della card
    int card_id;
    printf("PRIMA DI LEGGERE LA CARD\n");
    recv(user_socket, &card_id, sizeof(int), MSG_WAITALL);
    card_id = ntohl(card_id); // La serializzo
    printf("RICEVUTO DAL SERVER: %d\n", card_id);

    // Assegnazione della card
    user_handle_card(&user_data, card_id);

}

/**
 * @brief Implementazione della create_card
 */
void create_card(int user_socket){

    char task_id_str[32];
    int task_id;
    char task[1024];

    // Gestione task id
    printf("Inserisci l'id del task da inserire:\n");
    fgets(task_id_str, sizeof(task_id_str), stdin);
    task_id = atoi(task_id_str);

    // Inserimento corpo
    printf("Inserisci il corpo della card:\n");
    fgets(task, 1024, stdin);
    task[strcspn(task, "\n")] = '\0'; // sanificazione

    // Invio ora il comando (per evitare che ci siano blocchi nel server)
    send_command("CREATE_CARD\0");

    // Invio il numero del task
    task_id = htonl(task_id);
    send(user_socket, &task_id, sizeof(int), 0);

    // Invio la dimensione del corpo del testo
    int task_len = strlen(task);
    int net_task_len = htonl(task_len);
    send(user_socket, &net_task_len, sizeof(int), 0);

    // Invio il testo del task
    send(user_socket, task, task_len, 0);

    // Controllo il successo dell'operazione
    int result;
    recv(user_socket, &result, sizeof(int), 0);
    result = ntohl(result);

    if (result == -1) printf("Il task non è stato aggiunto, esiste già un task con lo stesso id\n");
    else printf("Il task è stato inserito correttamente in lavagna\n");

}

/**
 * @brief implementazione della QUIT
 */
void quit(int user_socket){

    user_close(&user_data);
    exit(0);

}

/**
 * @brief implementazione della CARD_DONE
 */
void user_card_done(){
    
    user_data._status = CONN;
    user_data._card_id = -1;

}

void user_request_user_list(int user_socket){

    // Ottengo il numero di utenti
    int n_users;
    recv(user_socket, &n_users, sizeof(int), 0);
    n_users = ntohl(n_users);
    

    // Ottengo l'array di utenti
    if (n_users != 0){
        User_t users[n_users];
        recv(user_socket, &users, n_users*sizeof(User_t), 0);
        other_users(&user_data, n_users, users);
    }

}

void review_card(int board_sock, int user_sock){
    
    handle_command("REQUEST_USER_LIST\0", board_sock, user_data._status);
        
    // Salvo gli utenti attuali
    refresh_review_users(&review, &user_data);

    // Invio i messaggi di REVIEW
    send_all_users_notification(&review, user_sock, user_data._card_id);

}

/**
 * @brief implementazione della handle_board_request
 */
void handle_board_request(char* command, int user_socket){
    

    printf("SONO DENTRO\n");

    // Controllo le richieste provenienti dalla lavagna
    if (strcmp(command, "HANDLE_CARD") == 0) {
        
        printf("GESTIONE CARD\n");
        handle_card(user_socket);
    
    }else if (strcmp(command, "PING_USER") == 0){

        // Mi pongo in stato PING_USER
        user_data._status = PING_USER; 

    }else{
        printf("Il comando %s inviato dalla lavagna non esiste\n", command);
    }

}   


void review_ok(int user_sock){

    send_user_ok(&review, user_sock, user_data._users_need_review[0]);
    pop_user_review(&user_data);

}

/**
 * @brief implementazione della handle_command
 */
void handle_command(char* command, int board_sock, User_Status status){

    // Controllo i comandi
    if (strcmp(command, "QUIT") == 0) {

        // Quit può essere sempre eseguito
        send_command(command);
        quit(board_sock);

    }else if (strcmp(command, "SHOW_LAVAGNA") == 0){
    
        // show_lavagna può essere sempre eseguita
        send_command(command);
        show_lavagna();

    }else if (strcmp(command, "ACK_CARD") == 0 && status == CONN){

        // L'ACK si può effettuare solo durante lo stato "CONN"
        send_command(command);
        user_data._status = CARD;

    }else if (strcmp(command, "PONG_LAVAGNA") == 0 && status == PING_USER){

        // pong_lavagna si può inviare solo durante lo stato di PING
        send_command(command);
        user_data._status = CARD;

    }else if (strcmp(command, "CARD_DONE") == 0 && (status == CARD || status == PING_USER) && review.req == 1 && review._remaning_users_number == 0){

        // card_done si può inviare solo durante card/ping
        user_card_done();
        send_command(command);
        review.req = 0;
    
    }else if (strcmp(command, "CREATE_CARD") == 0 && status != PING_USER){

        create_card(board_sock);

    }else if (strcmp(command, "REQUEST_USER_LIST") == 0 && (status == CARD || status == CONN)){

        send_command(command);
        user_request_user_list(board_sock);

    }else if (strcmp(command, "REVIEW_CARD") == 0 && status == CARD){
        
        review_card(board_sock, user_data._user_socket);
    
    }else if(strcmp(command, "REVIEW") == 0 && ( status == CARD || status == CONN) && user_data._users_need_review_number > 0) {

        review_ok(user_data._user_socket);
    
    }else{
        printf("Il comando %s non può essere inviato in questo momento, perchè non esiste o perchè non ti trovi nello stato corretto, riprova!\n", command);
    }

}

/**
 * @brief Funzione che attende che si verifichi un evento dal server
 * 
*/ 
void listen_to_server(){
    
    // Ottengo il socket dell'utente
    int board_socket = user_data._board_socket;
    int user_socket = user_data._user_socket;

    // Dichiarazione buffer
    char command[COMMAND_LEN];
    char input[COMMAND_LEN];
    char user_buffer;

    // Indirizzo dell'utente
    struct sockaddr_in sender_addr;
    socklen_t sender_len = sizeof(sender_addr);

    // Stampo i comandi per la prima volta
    handle_print(user_data._status, user_data._card_id, user_data._users_need_review, user_data._users_need_review_number);

    for(;;){

        fd_set readfds;
        FD_ZERO(&readfds);

        FD_SET(board_socket, &readfds); // socket TCP
        FD_SET(user_socket, &readfds); // socket UDP
        FD_SET(STDIN_FILENO, &readfds); // stdin

        int maxfd = board_socket;
        if (user_socket > maxfd) maxfd = user_socket;
        if (STDIN_FILENO > maxfd) maxfd = STDIN_FILENO;
        
        int activity = select(maxfd + 1, &readfds, NULL, NULL, NULL);

        if (activity < 0) {
            perror("Errore nella select");
            continue; 
        }
        
        /**
         * GESTIONE SERVER
         */
        if (FD_ISSET(board_socket, &readfds)) {
            printf("OLEEEE\n");
            memset(command, 0, COMMAND_LEN);
            int i = 0;
            while (i < COMMAND_LEN - 1) {
                char c;
                int n = recv(board_socket, &c, 1, 0);
                if (n <= 0) {
                    printf("Connessione chiusa\n");
                    exit(EXIT_FAILURE);
                }
                if (c == '\n') break;
                command[i++] = c;
            }
            
            // Gestione output server
            printf("Ricevuto comando %s dal server\n", command);
            handle_board_request(command, board_socket);
            handle_print(user_data._status, user_data._card_id, user_data._users_need_review, user_data._users_need_review_number);
            
        }
        
        /**
         * GESTIONE UTENTI
         */
        if (FD_ISSET(user_socket, &readfds)) {
            
            // Nota: recvfrom è necessario per UDP se vuoi sapere chi ti ha scritto
            user_buffer = 0;
            int n = recvfrom(user_socket, &user_buffer, sizeof(int), 0, 
                             (struct sockaddr*)&sender_addr, &sender_len);
            
            if (n > 0) {
            
                int review_port = ntohs(sender_addr.sin_port);
                int review_data = ntohl(user_buffer);

                printf("Messaggio UDP ricevuto: %d con porta: %d e prima %d\n", review_data, review_port, sender_addr.sin_port);

                if(review_data != -1) push_user_review(&user_data, review_port); // Inserisco la porta dell'utente in quelle che richiedono revisione
                else review_complete(&user_data, review_port);
                
                handle_print(user_data._status, user_data._card_id, user_data._users_need_review, user_data._users_need_review_number);
                
            }
        }


        /**
         * GESTIONE STDIN
         */
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            memset(input, 0, COMMAND_LEN);
            if (fgets(input, COMMAND_LEN, stdin) != NULL) {

                // Sanificazione input manuale
                input[strcspn(input, "\n")] = 0; // Sanificazione dell'input
                
                // Gestione input utente
                printf("Comando richiesto: %s\n", input);
                handle_command(input, board_socket, user_data._status);
                handle_print(user_data._status, user_data._card_id, user_data._users_need_review, user_data._users_need_review_number);

            }
        }   
        
    }

}