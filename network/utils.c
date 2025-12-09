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
