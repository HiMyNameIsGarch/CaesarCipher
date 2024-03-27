#ifndef FILE_H
#define FILE_H

void readFreq(char *filename, int *freq);

void readEncrypted(char *filename, char *encrypted[], int *sz);

void writeDecrypted(char *filename, char *decrypted[], int sz);

#endif
