#include "sender.h"

int send_command(int sockid, char* command) {
    // Envoyer la commande au socket spécifié
    ssize_t bytesSent = send(sockid, command, strlen(command), 0);
    if (bytesSent < 0) {
        perror("Erreur lors de l'envoi des données");
        return -1;
    }
    return 0;
}

int send_response(int sockid, char* response) {
    // Envoyer la réponse au socket spécifié
    ssize_t bytesSent = send(sockid, response, strlen(response), 0);
    if (bytesSent < 0) {
        perror("Erreur lors de l'envoi des données");
        return -1;
    }
    return 0;
}