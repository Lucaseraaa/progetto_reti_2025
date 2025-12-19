#include "server/connection.h"
#include "network/utils.h"
#include "functions/functions_board.h"
#include "classes/user.h"
#include "server/thread.h"
#include "classes/timer.h"

// Variabile condivisa: lavagna
// Va acceduta tramite un semaforo durante le funzioni della sezione critica
// @note La kanban va inizializzata 
Board_s kanban;

// Variabile condivisa timer
// Va acceduta tramite un semaforo durante le funzioni della sezione critica
Timer_s *timer;

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

    /* STEP 2: CREAZIONE DEL SERVER */

    // Inizializzazione delle strutture dati necessarie
    fd_set master;
    fd_set read_fds;
    
    // Indirizzi client/server
    struct sockaddr_in server_addr, client_addr;

    // Socket per l'ascolto
    int listener;
    int newfd;
    int fdmax;

    // Buffer
    char buf[1024];
    memset(buf, 0, 1024);
    int nbytes;
    int addrlen;
    int i;

    // Azzero i set
    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    if (generate_listener(&server_addr, &listener) == -1) {
        perror("Fallimento del main");
        exit(EXIT_FAILURE); 
    }

    FD_SET(listener, &master);
    fdmax = listener;
    
    /* STEP 3: CICLO INFINITO DELLA SELECT */

    for(;;){
        read_fds = master; 
        select(fdmax+1, &read_fds, NULL, NULL, NULL);
        for(int i = 0; i <= fdmax; i++){
            
            memset(buf, 0, 1024);

            // Trovato un descrittore pronto
            if(FD_ISSET(i, &read_fds)){
                
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
                    printf("Utenti inviati: %d con successo %d\n", connected_users_net, suser);

                    // Genero l'array e ci scrivo gli utenti
                    User_t users[connected_users - 1];
                    get_Users(kanban._usr, users, connected_users - 1, port);

                    // Invio gli utenti
                    suser = send(newfd, users, (connected_users-1)*sizeof(User_t), 0);
                    printf("Array Utenti inviati: con successo %d\n", suser);

                    // Connetto il client alla select
                    FD_SET(newfd, &master);
                    if(newfd>fdmax) fdmax = newfd;
                    
                    // Invio la lavagna all'utente
                    handle_command("SHOW_LAVAGNA", newfd);

                    handle_card();

                }
                else 
                {
                    // Sono in un altro socket
                    // Implica che è necessariamente una richiesta di un utente

                    int n = recv(i, buf, sizeof(buf), 0);

                    if (n == 0) {
                        // Caso 1: Il client ha chiuso la connessione (EOF)
                        printf("Client socket %d disconnesso.\n", i);
                        
                        char* exit = "QUIT";
                        handle_command(exit, i);

                        FD_CLR(i, &master); // Importante: smetti di monitorarlo!
                    }
                    else if (n < 0) {
                        // Caso 2: Errore
                        perror("Recv error");
                        close(i);
                        FD_CLR(i, &master);
                    }
                    else {
                        
                        buf[n] = '\0'; // Terminatore di stringa
                        printf("Richiesto comando dal client: %s con dimensione %ld\n ", buf, sizeof(buf));
                        
                        int handle_return = handle_command(buf, i);
                        if (handle_return == 1) FD_CLR(i, &master); // Elimino l'utente dal pool
                    
                    }

                }
            }
        }

    }

}
