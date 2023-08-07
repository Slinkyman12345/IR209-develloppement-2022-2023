#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "sender.h"
#include "receiver.h"

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    // Vérifier si le programme est exécuté avec les privilèges de root
    if (getuid() != 0) {
        printf("Ce programme doit être exécuté avec les privilèges de root.\n");
        exit(1);
    }

    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    char response[BUFFER_SIZE];

    // Créer une socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        printf("Erreur lors de la création de la socket : %s\n", strerror(errno));
        exit(1);
    }

    // Spécifier l'adresse IP et le port du serveur
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(atoi(argv[1]));

    // Réutiliser l'adresse et le port même en cas de déconnexion brutale
    int option = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option)) < 0) {
        printf("Erreur lors de la configuration de la socket : %s\n", strerror(errno));
        exit(1);
    }

    // Lier le socket à l'adresse IP et au port
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        printf("Erreur lors du bind : %s\n", strerror(errno));
        exit(1);
    }

    // Mettre la socket en mode écoute
    if (listen(serverSocket, 1) < 0) {
        printf("Erreur lors de la mise en écoute : %s\n", strerror(errno));
        exit(1);
    }

    printf("Attente de connexion...\n");

    // Accepter une connexion entrante
    socklen_t clientAddressLength = sizeof(clientAddress);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
    if (clientSocket < 0) {
        printf("Erreur lors de l'acceptation de la connexion : %s\n", strerror(errno));
        exit(1);
    }

    printf("Connexion établie avec le client %s:%d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));

    int stopReceived = 0;

    while (!stopReceived) {
        // Recevoir la commande du client en utilisant la fonction du receiver
        char command[BUFFER_SIZE];
        int bytesReceived = receive_command(clientSocket, command, BUFFER_SIZE);
        if (bytesReceived < 0) {
            perror("Erreur lors de la réception de la commande");
            exit(1);
        }

        // Vérifier si la commande est "stop"
		if (strcmp(command, "stop") == 0) {
			stopReceived = 1;

			// Envoyer une réponse au client indiquant que le serveur a reçu "stop"
			const char *stopResponse = "Commande 'stop' reçue. Déconnexion...\n";
			int result = send_response(clientSocket, stopResponse);
			if (result != 0) {
				perror("Erreur lors de l'envoi de la réponse");
				exit(1);
			}
        } else {
            //https://c-for-dummies.com/blog/?p=1418
            // Exécuter la commande (en tant que root)
            FILE *p;
            int output;
            p = popen(command,"r"); /* Unix */
            if( p == NULL)
            {
                puts("Impossible d'ouvrir le processus");
                return(1);
            }
            while( (output=fgetc(p)) != EOF)
                putchar(output);
            pclose(p);

            // Envoyer la réponse au client en utilisant la fonction du sender
            int result = send_response(clientSocket, response);
            if (result != 0) {
                perror("Erreur lors de l'envoi de la réponse");
                exit(1);
            }
        }
    }

    // Fermer la connexion client
    if (close(clientSocket) < 0) {
        printf("Erreur lors de la fermeture de la connexion client : %s\n", strerror(errno));
    }

    // Fermer la socket du serveur
    if (close(serverSocket) < 0) {
        printf("Erreur lors de la fermeture de la socket du serveur : %s\n", strerror(errno));
    }

    return 0;
}
