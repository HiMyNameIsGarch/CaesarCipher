#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/char_op.h"

void readFreq(float freq[26]) {
    FILE *fptr;
    fptr = fopen("tomb/distribution.txt", "r");
    if(!fptr) {
        return;
    }
    char chars[ALPHABET] = { 0 };

    short unsigned int i = 0;
    while(fgets(chars, ALPHABET, fptr)) {
        freq[i] = atof(chars);
        i++;
    }
    fclose(fptr);
}

char * readEncrypted() {
    FILE *fptr;
    fptr = fopen("tomb/encrypted.txt", "r");
    if(!fptr) {
        return NULL;
    }

    fseek(fptr, 0, SEEK_END);
    long lSize = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    char *txt = (char *)malloc(lSize * sizeof(char));

    if(txt == NULL) {
        return NULL;
    }

    short unsigned int i = 0;
    char ch;
    while (fscanf(fptr, "%c", &ch) != EOF) {
        txt[i] = ch;
        i++;
    }
    fclose(fptr);

    return txt;
}

void normFreq(const char *txt, float cfreq[ALPHABET]) {
    for(int i = 0; txt[i]; i++) {
        int index = getIndexOfChar(txt[i]);

        if (index == -1) {
            continue;
        }

        cfreq[index] += 1;
    }
}

// Current h and expected h
float chiSquareDist(float *ch, float *eh) {
    float dist = 0;

    // Calculate the chi square distance
    // between the observed and expected frequencies
    for(int i = 0; i < ALPHABET; i++) {
        float diff = ch[i] - eh[i];
        dist += (diff * diff) / eh[i];
    }

    return dist;
}

// Pretty straight forward
void clean_arr(float *arr, const int l) {
    for(int i = 0; i < l; i++)
        arr[i] = 0;
}

void crackCipher(char *cipher, float freq[ALPHABET], const int l, int *key, char *decrypted) {
    float cfreq[ALPHABET] = { 0 };

    // Compute inital chi square distance
    normFreq(cipher, cfreq);
    float chi = chiSquareDist(cfreq, freq);

    // Iterate through all possible permutations
    // ( basically shift all the letters by -1)
    // We only need to do this 25 times as those are all the possible shifts
    for (int i = 0; i < ALPHABET; i++) {
        permuteChars(cipher, l);

        // Reset the frequency array
        clean_arr(cfreq, ALPHABET);

        normFreq(cipher, cfreq);

        float new_chi = chiSquareDist(cfreq, freq);
        if(new_chi < chi) {
            chi = new_chi;
            memcpy(decrypted, cipher, l);
            *key = i;
        }
    }
}

int main() {
    float freq[ALPHABET];
    readFreq(freq);

    char *code = NULL;
    code = readEncrypted();
    printf("%s\n", code);
    int l = 0;
    while (code[l]) {
        l++;
    }
    char decrypted[l];
    int key = 0;
    crackCipher(code, freq, l, &key, decrypted);
    free(code);
    printf("Decrypted: %s\n", decrypted);
    printf("Key: %d\n", key);
    return 0;
}
