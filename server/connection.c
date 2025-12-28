#include "server/connection.h"
#include "network/utils.h"
#include "functions/functions_board.h"
#include "classes/user.h"
#include "classes/timer.h"
#include <fcntl.h>

// Variabile condivisa: lavagna
// Va acceduta tramite un semaforo durante le funzioni della sezione critica
// @note La kanban va inizializzata 
Board_s kanban;

// Variabile condivisa timer
// Va acceduta tramite un semaforo durante le funzioni della sezione critica
Timer_s *timer;

// Le 10 cards da inivare alla lavagna appena partita
// I progetti verranno inizializzati con ID crescenti da 0 a 9
char* cards[INIT_CARD_NUMBER] = {
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

// Inizializzazione delle strutture dati necessarie
fd_set master;
fd_set read_fds;

// Pipe per la comunicazione con il timer
int timer_pipe[2];


void select_main(){

    /* STEP 1: INIZIALIZZAZIONE DELLA KANBAN */

    // Inizializzazione della kanban
    board_init(&kanban, SERVER_PORT, cards);

    // Inizializzo il timer
    timer = NULL;

    // Sovrascriviamo la funzione dell'alarm
    signal(SIGALRM, timer_handler);

    // (Primo comando secondo specifiche) mostro la lavagna appena creata
    show_lavagna(&kanban);

    // Inizializzo la coda
    if (pipe(timer_pipe) == -1) {
        perror("Errore creazione pipe");
        exit(EXIT_FAILURE);
    }

    /* STEP 2: CREAZIONE DEL SERVER */
    
    // Indirizzi client/server
    struct sockaddr_in server_addr, client_addr;

    // Socket per l'ascolto
    int listener;
    int newfd;
    int fdmax;

    // Buffer
    uint32_t msg;
    socklen_t addrlen;

    // Azzero i set
    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    fcntl(timer_pipe[0], F_SETFL, O_NONBLOCK);
    fcntl(timer_pipe[1], F_SETFL, O_NONBLOCK);

    if (generate_listener(&server_addr, &listener) == -1) {
        perror("Non si è generato il listener");
        exit(EXIT_FAILURE); 
    }

    FD_SET(listener, &master);
    FD_SET(timer_pipe[0], &master); // Aggiungo la lettura pipe al master
    fdmax = (listener > timer_pipe[0]) ? listener : timer_pipe[0];
    
    /* STEP 3: CICLO INFINITO DELLA SELECT */
    for(;;){

        read_fds = master; 
        int ret = select(fdmax+1, &read_fds, NULL, NULL, NULL);
        
        if (ret == -1) {
            if (errno == EINTR) continue;
            else exit(EXIT_FAILURE); // Fallisco in caso di segnale di errore
        }
        
        for(int i = 0; i <= fdmax; i++){

            // Trovato un descrittore pronto
            if(FD_ISSET(i, &read_fds) && FD_ISSET(i, &master)){
                
                if (i == timer_pipe[0]) continue;

                // Sono nel listener, un utente sta cercando di connettersi
                if(i == listener){

                    // Connetto il nuovo client
                    addrlen = sizeof(client_addr);
                    newfd = accept(listener, (struct sockaddr*)&client_addr, &addrlen);

                    // Inserisco il nuovo utente nella lista
                    // Richiedo il numero di porta dal client
                    char port_str[PORT_BUFFER_LENGTH];
                    int port_read = read(newfd, port_str, PORT_BUFFER_LENGTH);

                    if (port_read < 0){

                        // Controllo che la porta sia corretta
                        printf("Il client non è riuscito a connettersi!\n");
                        close(newfd);
                        continue;

                    }
                    
                    // Conversione della porta
                    User_t port = (User_t)atoi(port_str);
                    if (user_register(&kanban, port, newfd) == -1){

                        printf("Il client non può connettersi\n");
                        
                        // Invio all'utente -1, per terminare la comunicazione
                        int term = htonl(-1);
                        send(newfd, &term, sizeof(int), 0);

                        // Chiudo la connessione con l'utente
                        close(newfd);
                        continue;

                    }

                    // Ottengo gli utenti connessi
                    int connected_users = kanban._connected_user;
                    int connected_users_net = htonl(connected_users - 1);

                    // Invio il numero di utenti
                    int suser = send(newfd, &connected_users_net, sizeof(connected_users), 0);
                    
                    if (connected_users != 1){
                        // Genero l'array e ci scrivo gli utenti
                        User_t users[connected_users - 1];
                        get_Users(kanban._usr, users, connected_users - 1, port);

                        // Invio gli utenti
                        suser = send(newfd, users, (connected_users-1)*sizeof(User_t), 0);
                        printf("Array Utenti inviati: con successo %d\n", suser);

                    }

                    // Connetto il client alla select
                    FD_SET(newfd, &master);
                    if(newfd>fdmax) fdmax = newfd;

                    handle_card();

                }
                else 
                {

                    int n = recv(i, &msg, sizeof(msg), 0);

                    if (n == 0) {
                        // Il client ha chiuso la connessione 
                        printf("Client socket %d disconnesso.\n", i);
                        
                        handle_command(UB_QUIT, i);

                        FD_CLR(i, &master); 

                    }
                    else if (n < 0) {
                        // Errore
                        perror("Recv error");
                        close(i);
                        FD_CLR(i, &master);
                    }
                    else {
                        
                        // È arrivato un messaggio, lo converto nel formato corretto
                        User_to_Board_command conv_msg = recv_message_from_user(msg);
                        printf("Richiesto comando dal client: %d con dimensione %d\n ", conv_msg, n);
                        
                        int handle_return = handle_command(conv_msg, i);
                        
                        // Nel caso in cui il ritorno della funzione sia 1, devo eliminare l'utente
                        if (handle_return == 1) {
                            
                            User_s* utente = get_User_by_socket(kanban._usr, i);
                            printf("L'utente %d ha causato un errore nella lettura del socket: verrà disconnesso!\n", get_User_port(utente));
                            quit(utente); 
                            
                        }
                    }

                }
            }
        }
        
        if (FD_ISSET(timer_pipe[0], &read_fds)) {
            
            char buffer[256]; 
            read(timer_pipe[0], buffer, sizeof(buffer));
            
            // Controllo se ci sono altri timer in attesa
            int has_another_timer = execute_Timer_head_function(&timer);
            
            if (has_another_timer == 1){
                
                int next_timer_delay = get_next_timer(timer);

                if (next_timer_delay >= 0) alarm(next_timer_delay == 0 ? 1 : next_timer_delay);

            }
        
        }

        // Nel caso disattivo il timer
        if (timer == NULL) alarm(0);

    }

}
