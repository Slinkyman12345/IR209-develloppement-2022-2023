#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUFFER_SIZE 1024

void executeCommand(const char *command, char *response) {
    FILE *fp;
    char path[BUFFER_SIZE];
    int status;

    // Exécution de la commande et récupération de la sortie
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Erreur lors de l'exécution de la commande");
        exit(1);
    }

    // Lecture du résultat de la commande
    while (fgets(path, sizeof(path), fp) != NULL) {
        strcat(response, path);
    }

    // Fermeture du flux
    status = pclose(fp);
    if (status == -1) {
        perror("Erreur lors de la fermeture du flux");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    char command[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    // Créer une socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Erreur lors de la création de la socket");
        exit(1);
    }

    // Spécifier l'adresse IP et le port du serveur
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(atoi(argv[1]));

    // Lier la socket à l'adresse IP et au port
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Erreur lors du bind");
        exit(1);
    }

    // Mettre la socket en mode écoute
    if (listen(serverSocket, 1) < 0) {
        perror("Erreur lors de la mise en écoute");
        exit(1);
    }

    printf("Attente de connexion...\n");

    // Accepter une connexion entrante
    socklen_t clientAddressLength = sizeof(clientAddress);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
    if (clientSocket < 0) {
        perror("Erreur lors de l'acceptation de la connexion");
        exit(1);
    }

    printf("Connexion établie avec le client %s:%d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));

    while (1) {
        // Réinitialiser les buffers
        memset(command, 0, sizeof(command));
        memset(response, 0, sizeof(response));

        // Recevoir la commande du client
        ssize_t bytesRead = recv(clientSocket, command, BUFFER_SIZE - 1, 0);
        if (bytesRead < 0) {
            perror("Erreur lors de la réception des données");
            exit(1);
        }

        // Exécuter la commande
        executeCommand(command, response);

        // Envoyer la réponse au client
        ssize_t bytesSent = send(clientSocket, response, strlen(response), 0);
        if (bytesSent < 0) {
            perror("Erreur lors de l'envoi des données");
            exit(1);
        }
    }

    // Fermer les sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}
