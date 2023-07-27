#include "receiver.h"

int receive_command(int sockid, char* command, int bufferSize) {
    // Recevoir la commande depuis le socket spécifié
    ssize_t bytesRead = recv(sockid, command, bufferSize - 1, 0);
    if (bytesRead < 0) {
        perror("Erreur lors de la réception des données");
        return -1;
    }
    return bytesRead;
}

int receive_response(int sockid, char* response, int bufferSize) {
    // Recevoir la réponse depuis le socket spécifié
    ssize_t bytesRead = recv(sockid, response, bufferSize - 1, 0);
    if (bytesRead < 0) {
        perror("Erreur lors de la réception des données");
        return -1;
    }
    return bytesRead;
}