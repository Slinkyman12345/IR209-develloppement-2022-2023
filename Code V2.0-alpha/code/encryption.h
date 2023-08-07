#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>

#define KEY_SIZE 32
#define IV_SIZE 16

/* Le code des fichiers encryption.c et encryption.h provient essentiellement
 * des diapositives du cours théorique ainsi que de
 * https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption */

void handleErrors(void);

//Create key and IV : RAND_bytes(key, sizeof(key));

int generate_key(unsigned char *key);

int generate_IV(unsigned char *iv);

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext);

int decrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext);

#endif