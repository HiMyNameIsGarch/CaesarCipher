#include <stdio.h>
#include <stdlib.h>

#define MAX_LETTERS (26);

int getIndexForChar(char l) {
    if (l >= 97 && l <= 122) {
        return l - 97;
    }
    if (l >= 65 && l <= 90) {
        return l - 65;
    }
    return -1;
}

void readFreq(float freq[26]) {
    FILE *fptr;
    fptr = fopen("distribution.txt", "r");
    char chars[26];

    short unsigned int i = 0;
    while(fgets(chars, 26, fptr)) {
        freq[i] = atof(chars);
        i++;
    }
    fclose(fptr);
}

void normFreq(char *txt, float cfreq[26]) {
    for(int i = 0; txt[i] != '\0'; i++) {
        cfreq[getIndexForChar(txt[i])] += 1;
    }
}

char shiftChar(char a, int i) {
    if (a >= 65 && a <= 90) {
        a = a + i;
        if (a < 65) {
            a = 90 - (64 - a);
        } else if (a > 90) {
            a = 65 + (a - 91);
        }
    } else if (a >= 97 && a <= 122) {
        a = a + i;
        if (a < 97) {
            a = 122 - (96 - a);
        } else if (a > 122) {
            a = 97 + (a - 123);
        }
    }
    return a;
}

int chiSquareDist(float *ch, float *eh) {
    float dist = 0;
    for(int i=0; i<= 26; i++) {
        float diff = ch[i] - eh[i];
        dist += (diff * diff) / eh[i];
    }
    return dist;
}

void next_permutation(char *f, int l) {
    for(int i = 0; i< l; ++i) {
        f[i] = shiftChar(f[i], -1);
    }
}


void crackCipher(char *cipher, float freq[26], int l) {
    float cfreq[26];

    normFreq(cipher, cfreq);
    int chi = chiSquareDist(cfreq, freq);

    for (int i = 0; i < 26; i++) {
        next_permutation(cipher, l);

        normFreq(cipher, cfreq);
        int nchi = chiSquareDist(cfreq, freq);
        if (nchi < chi) {
            chi = nchi;
        }
    }
    printf("The lowest value of chi is: %d\n", chi);
}

int main() {
    float freq[26];
    readFreq(freq);
    char code[] = "Uf ime ftq nqef ar fuyqe, uf ime ftq iadef ar fuyqe, uf ime ftq msq ar iuepay, uf ime ftq msq ar raaxuetzqee, uf ime ftq qbaot ar nqxuqr, uf ime ftq qbaot ar uzodqpgxufk, uf ime ftq eqmeaz ar xustf, uf ime ftq eqmeaz ar pmdwzqee, uf ime ftq ebduzs ar tabq, uf ime ftq iuzfqd ar pqebmud.\0";
    int l = 0;
    while (code[l] != '\0') {
        l++;
    }
    crackCipher(code, freq, l);
    return 0;
}
