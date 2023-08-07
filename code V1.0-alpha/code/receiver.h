#ifndef RECEIVER_H
#define RECEIVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

/* Les communications se feront via un protocole TCP */

/*
 * Fonction qui reçoit une commande depuis un socket spécifié.
 *
 * @Input :
 * sockid : id du socket
 * command : tableau pour stocker la commande reçue
 * bufferSize : taille du buffer de réception
 *
 * @Output :
 * return : nombre d'octets reçus si la commande a été reçue avec succès
 *          -1 si une erreur s'est produite
 */
int receive_command(int sockid, char* command, int bufferSize);

/*
 * Fonction qui reçoit une réponse depuis un socket spécifié.
 *
 * @Input :
 * sockid : id du socket
 * response : tableau pour stocker la réponse reçue
 * bufferSize : taille du buffer de réception
 *
 * @Output :
 * return : nombre d'octets reçus si la réponse a été reçue avec succès
 *          -1 si une erreur s'est produite
 */
int receive_response(int sockid, char* response, int bufferSize);

#endif