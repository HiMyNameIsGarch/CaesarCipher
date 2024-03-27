#ifndef CAESAR_H
#define CAESAR_H

void decrypt(int key, char *encrypted[], char *decrypted[], int sz);

void encrypt(int key, char *decrypted[], char *encrypted[], int sz);

#endif
