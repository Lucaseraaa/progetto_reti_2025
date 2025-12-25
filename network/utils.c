#include "utils.h"

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

/**
 * @brief implementazione della create_socket
 */
int create_socket(const char* address, int port, enum __socket_type type, struct sockaddr_in *server_address){

    int socket_dscp = socket(AF_INET, type, 0);
    if (socket_dscp == -1) {
        perror("Errore nella creazione del socket");
        return -1;
    }

    memset(server_address, 0, sizeof(*server_address));
    server_address->sin_family = AF_INET;
    server_address->sin_port = htons(port);

    if (inet_pton(AF_INET, address, &server_address->sin_addr) <= 0) {
        perror("Errore in inet_pton");
        return -1;
    }

    return socket_dscp;
}

/**
 * @brief implementazione della generate_listener
 */
int generate_listener(struct sockaddr_in* sv_addr, int* listener){

    // Creazione del socket
    *listener = socket(AF_INET, SOCK_STREAM|SOCK_NONBLOCK, 0);
    if(*listener == -1){
        perror("Errore nella creazione del socket");
        return -1;
    }

    // Bind
    sv_addr->sin_family = AF_INET;
    sv_addr->sin_addr.s_addr = INADDR_ANY;
    sv_addr->sin_port = htons(5678);
    
    if (bind(*listener, (struct sockaddr*) sv_addr, sizeof(*sv_addr)) == -1) {
        perror("Errore nella bind");
        return -1;
    }

    if(listen(*listener, 10)){
        perror("Errore nella listen");
        return -1;
    }

    return 0;

}

/**
 * @brief implementazione della create_udp_socket
 */
int creare_udp_socket(int* udp_socket, struct sockaddr_in* my_addr, int port){

    if((*udp_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        printf("Errore nella creazione del socket\n");
        return -1;
    }

    memset(my_addr, 0, sizeof(*my_addr));
    my_addr->sin_family = AF_INET;
    my_addr->sin_addr.s_addr = htonl(INADDR_ANY);
    my_addr->sin_port = htons(port);

    if (bind(*udp_socket, (struct sockaddr *)my_addr, sizeof(*my_addr)) < 0) {
        perror("Errore nella bind");
        return -1;
    }

    return 0;
}