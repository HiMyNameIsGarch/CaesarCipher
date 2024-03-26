#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_LOWER 65
#define MAX_LOWER 90

#define MIN_UPPER 97
#define MAX_UPPER 122

#define ALPHABET 26

int getIndexForChar(char l) {
    // Lower case
    if (l >= MIN_UPPER && l <= MAX_UPPER) {
        return l - MIN_UPPER;
    }
    // Upper case
    if (l >= MIN_LOWER && l <= MAX_LOWER) {
        return l - MIN_LOWER;
    }
    // Not a letter
    return -1;
}
char shiftChar(char a, int i) {
    // Lower case letters
    if (a >= MIN_LOWER && a <= MAX_LOWER) {
        a = a + i;
        if (a < MIN_LOWER) {
            a = MAX_LOWER - ((MIN_LOWER - 1) - a);
        } else if (a > MAX_LOWER) {
            a = MIN_LOWER + (a - (MAX_LOWER + 1));
        }

    // Upper case letters
    } else if (a >= MIN_UPPER && a <= MAX_UPPER) {
        a = a + i;
        if (a < MIN_UPPER) {
            a = MAX_UPPER - ((MIN_UPPER - 1) - a);
        } else if (a > MAX_UPPER) {
            a = MIN_UPPER + (a - (MAX_UPPER + 1));
        }
    }
    return a;
}

void next_permutation(char *f, const int l) {
    for(int i = 0; i < l; ++i) {
        f[i] = shiftChar(f[i], -1);
    }
}

void readFreq(float freq[26]) {
    FILE *fptr;
    fptr = fopen("distribution.txt", "r");
    char chars[ALPHABET] = { 0 };

    short unsigned int i = 0;
    while(fgets(chars, ALPHABET, fptr)) {
        freq[i] = atof(chars);
        i++;
    }
    fclose(fptr);
}

void normFreq(const char *txt, float cfreq[ALPHABET]) {
    for(int i = 0; txt[i]; i++) {
        int index = getIndexForChar(txt[i]);

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
        next_permutation(cipher, l);

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
    char code[] = "Uf ime ftq nqef ar fuyqe, uf ime ftq iadef ar fuyqe, uf ime ftq msq ar iuepay, uf ime ftq msq ar raaxuetzqee, uf ime ftq qbaot ar nqxuqr, uf ime ftq qbaot ar uzodqpgxufk, uf ime ftq eqmeaz ar xustf, uf ime ftq eqmeaz ar pmdwzqee, uf ime ftq ebduzs ar tabq, uf ime ftq iuzfqd ar pqebmud.\0";
    int l = 0;
    while (code[l]) {
        l++;
    }
    char decrypted[l];
    int key = 0;
    crackCipher(code, freq, l, &key, decrypted);
    printf("Decrypted: %s\n", decrypted);
    printf("Key: %d\n", key);
    return 0;
}
