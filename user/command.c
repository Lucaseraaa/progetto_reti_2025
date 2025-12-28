#include "user/command.h"
#include "user/print.h"
#include "user/peer.h"
#include "network/utils.h"

#define USER_REVIEW_TIMER 30

// Variabile per azionare il timer
int timer_scaduto = 0;

// Variabile per comunicare fra thread
int pipe_fd[2];

/**
 * @brief implementazione della send_command
 */
void send_command(User_to_Board_command command){

    // Ottengo il socket a cui inviare il comando
    int board_socket = user_data._board_socket;

    // Invio il comando
    send_message_to_board(board_socket, command);
    printf("Comando %d inviato al server!\n", command);

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
    recv(user_socket, &card_id, sizeof(int), MSG_WAITALL);
    card_id = ntohl(card_id); // La serializzo

    // Assegnazione della card
    user_handle_card(&user_data, card_id);

}

/**
 * @brief Implementazione della create_card
 */
void create_card(int user_socket, int id, char* body){

    // Invio ora il comando (per evitare che ci siano blocchi nel server)
    printf("INVIO IL COMANDO CREA\n");
    send_message_to_board(user_socket, UB_CREATE_CARD);

    // Invio il numero del task
    int task_id = htonl(id);
    send(user_socket, &task_id, sizeof(int), 0);

    // Invio la dimensione del corpo del testo
    int task_len = strlen(body);
    int net_task_len = htonl(task_len);
    send(user_socket, &net_task_len, sizeof(int), 0);

    // Invio il testo del task
    send(user_socket, body, task_len, 0);

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
    
    // Richiedo la lista degli utenti
    handle_command("REQUEST_USER_LIST\0", board_sock, user_data._status);
        
    // Salvo gli utenti attuali
    refresh_review_users(&review, &user_data);

    // Invio i messaggi di REVIEW
    send_all_users_notification(&review, user_sock, user_data._card_id);

}

/**
 * @brief implementazione della handle_board_request
 */
void handle_board_request(Board_to_User_command command, int user_socket){
    

    printf("SONO DENTRO\n");

    // Controllo le richieste provenienti dalla lavagna
    if (command == BU_HANLDE_CARD) {
        
        handle_card(user_socket);
    
    }else if (command == BU_PING_USER){

        // Mi pongo in stato PING_USER
        user_data._status = PING_USER; 

    }else{
        printf("Il comando inviato dalla lavagna non esiste\n");
    }

}   


void review_ok(int user_sock){

    printf("L'utente che deve essere revisionato è %d\n", user_data._users_need_review[0]);
    send_user_ok(&review, user_sock, user_data._users_need_review[0]);
    pop_user_review(&user_data);

}

void resend_review_to_users(int p){

    if (review._remaning_users != 0) timer_scaduto = 1; 
    else timer_scaduto = 0;

}

/**
 * @brief implementazione della handle_command
 */
void handle_command(char* command, int board_sock, User_Status status){

    // Controllo i comandi
    if (strcmp(command, "QUIT") == 0) {

        // Quit può essere sempre eseguito
        send_command(UB_QUIT);
        quit(board_sock);

    }else if (strcmp(command, "SHOW_LAVAGNA") == 0 && status != PING_USER){
    
        // show_lavagna può essere sempre eseguita
        send_command(UB_SHOW_LAVAGNA);
        show_lavagna();

    }else if (strcmp(command, "ACK_CARD") == 0 && status == CONN){

        // L'ACK si può effettuare solo durante lo stato "CONN"
        printf("Inizio a svolgere la card con id %d\n", user_data._card_id);
        send_command(UB_ACK_CARD);
        
        // Avvio del thread
        pthread_t tid;
        int n = (rand() % 21) + 10; // Genero un numero da 20 a 30
        int *duration = malloc(sizeof(int));
        *duration = n;
        pthread_create(&tid, NULL, thread_simulate_job, duration);
        pthread_detach(tid);
        
        user_data._status = SLEEP_CARD;

    }else if (strcmp(command, "PONG_LAVAGNA") == 0 && status == PING_USER){

        // pong_lavagna si può inviare solo durante lo stato di PING
        send_command(UB_PONG_LAVAGNA);
        user_data._status = CARD;

    }else if (strcmp(command, "CARD_DONE") == 0 && status == CARD && review.req == 1 && review._remaning_users_number == 0){

        // card_done si può inviare solo durante card/ping
        user_card_done();
        send_command(UB_CARD_DONE);
        review.req = 0;
        printf("ULTIMO CARD DONE\n");
    
    }else if (strncmp(command, "CREATE_CARD", 11) == 0 && (status != PING_USER && status != SLEEP_CARD)){

        int id;
        char body[1024];
    
        if (sscanf(command, "CREATE_CARD %d %[^\n]", &id, body) == 2) {
            // Se sscanf restituisce 2, ha letto correttamente sia ID che Body
            create_card(board_sock, id, body);
        }else {
            printf("Formato errato! Usa: CREATE_CARD <id> <descrizione del task>\n");
        }

    }else if (strcmp(command, "REQUEST_USER_LIST") == 0 && ( status >= CARD && status <= PING_USER)){

        send_command(UB_REQUEST_USER_LIST);
        user_request_user_list(board_sock);

    }else if (strcmp(command, "REVIEW_CARD") == 0 && status == CARD){
        
        review_card(board_sock, user_data._user_socket);
        if (review._remaning_users_number != 0) alarm(USER_REVIEW_TIMER);
    
    }else if(strcmp(command, "REVIEW") == 0 && ( status == CARD || status == CONN || status == SLEEP_CARD) && user_data._users_need_review_number > 0) {

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

    // Setto l'alarm dell'utente alla funzione resend_review_to_users
    signal(SIGALRM, resend_review_to_users);
    
    // Ottengo il socket dell'utente
    int board_socket = user_data._board_socket;
    int user_socket = user_data._user_socket;

    // Dichiarazione buffer
    u_int32_t command;
    char input[COMMAND_LEN];
    User_to_User_message user_buffer;

    // Inizializzo il seed
    srand(time(NULL));

    // Apro la PIPE
    if (pipe(pipe_fd) == -1){
        printf("La pipe non è stata creata correttamente\n");
        close(user_socket);
        close(board_socket);
        exit(EXIT_FAILURE);
    }

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
        FD_SET(pipe_fd[0], &readfds); // Pipe

        int maxfd = board_socket;
        if (user_socket > maxfd) maxfd = user_socket;
        if (STDIN_FILENO > maxfd) maxfd = STDIN_FILENO;
        if (pipe_fd[0] > maxfd) maxfd = pipe_fd[0];
        
        int activity = select(maxfd + 1, &readfds, NULL, NULL, NULL);
        
        if (timer_scaduto == 1){
            
            handle_command("REQUEST_USER_LIST\0", user_data._board_socket, user_data._status);
            filter_disconnected_users(&review, user_data._others, user_data._connected_users);
            send_all_users_notification(&review, user_data._user_socket, user_data._card_id);
            timer_scaduto = 0;
            
            if (review._remaning_users_number == 0) handle_print(user_data._status, user_data._card_id, review._remaning_users, review._remaning_users_number);
            else alarm(USER_REVIEW_TIMER);

        }

        if (activity < 0) continue; 
        
        
        /**
         * GESTIONE PIPE
         */
        if (FD_ISSET(pipe_fd[0], &readfds)) {
            
            char buffer;
            read(pipe_fd[0], &buffer, 1); // Pulisce la pipe    

            user_data._status = CARD;
            handle_print(user_data._status, user_data._card_id, user_data._users_need_review, user_data._users_need_review_number);

        }


        /**
         * GESTIONE SERVER
         */
        if (FD_ISSET(board_socket, &readfds)) {
            
            if (recv(board_socket, &command, sizeof(command), MSG_WAITALL) > 0){
                Board_to_User_command com = recv_message_from_board(command);
            
                // Gestione output server
                printf("Ricevuto comando %d dal server\n", com);
                handle_board_request(com, board_socket);
                handle_print(user_data._status, user_data._card_id, user_data._users_need_review, user_data._users_need_review_number);
            }else{
                
                printf("Mi disconnetto a seguito di un'errore\n");
                exit(EXIT_FAILURE);

            }
            
            
        }
        
        /**
         * GESTIONE UTENTI
         */
        if (FD_ISSET(user_socket, &readfds)) {
            
            // Ricezione messaggio UDP
            int n = recvfrom(user_socket, &user_buffer, sizeof(User_to_User_message), MSG_WAITALL, 
                             (struct sockaddr*)&sender_addr, &sender_len);
            
            if (n > 0) {
                
                // Conversione porta utente e comando
                uint16_t review_port = (uint16_t) ntohs(user_buffer._sender_port);
                int16_t review_command = (int16_t) ntohs(user_buffer._command);

                printf("Messaggio UDP ricevuto: %d con porta: %d e prima %d\n", review_command, review_port, sender_addr.sin_port);
                
                // Nel caso in cui il comando sia -1, ho ricevuto risposta al mio REVIEW_CARD
                // In caso contrario devo verificare il task dell'utente
                if(review_command != -1) push_user_review(&user_data, review_port);
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