#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <serverIP> <port>\n", argv[0]);
        exit(1);
    }

    int clientSocket;
    struct sockaddr_in serverAddress;
    char command[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    // Créer une socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Erreur lors de la création de la socket");
        exit(1);
    }

    // Spécifier l'adresse IP et le port du serveur
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddress.sin_port = htons(atoi(argv[2]));

    // Se connecter au serveur
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Erreur lors de la connexion au serveur");
        exit(1);
    }

    printf("Connexion établie avec le serveur %s:%d\n", argv[1], atoi(argv[2]));

    while (1) {
        // Réinitialiser les buffers
        memset(command, 0, sizeof(command));
        memset(response, 0, sizeof(response));

        // Lire la commande depuis l'entrée utilisateur
        printf("> ");
        fgets(command, BUFFER_SIZE, stdin);

        // Envoyer la commande au serveur
        ssize_t bytesSent = send(clientSocket, command, strlen(command), 0);
        if (bytesSent < 0) {
            perror("Erreur lors de l'envoi des données");
            exit(1);
        }

        // Recevoir la réponse du serveur
        ssize_t bytesRead = recv(clientSocket, response, BUFFER_SIZE - 1, 0);
        if (bytesRead < 0) {
            perror("Erreur lors de la réception des données");
            exit(1);
        }

        // Afficher la réponse
        printf("%s", response);
    }

    // Fermer la socket
    close(clientSocket);

    return 0;
}
