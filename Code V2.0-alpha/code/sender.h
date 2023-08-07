#ifndef SENDER_H
#define SENDER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

/* Les communications se feront via un protocole TCP */

/*
 * Fonction qui envoie une commande donnée à un socket spécifié.
 *
 * @Input :
 * sockid : id du socket
 * command : la commande à envoyer
 *
 * @Output :
 * return : 0 si la commande a bien été envoyée
 *          -1 si ce n'est pas le cas
 */
int send_command(int sockid, char* command);

/*
 * Fonction qui envoie une réponse donnée à un socket spécifié.
 *
 * @Input :
 * sockid : id du socket
 * response : la réponse à envoyer
 *
 * @Output :
 * return : 0 si la réponse a bien été envoyée
 *          -1 si ce n'est pas le cas
 */
int send_response(int sockid, const char* response);

#endif
