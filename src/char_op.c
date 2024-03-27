#include "../include/char_op.h"

int getIndexOfChar(char l) {
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

void permuteChars(char *f, const int l) {
    for(int i = 0; i < l; ++i) {
        f[i] = shiftChar(f[i], -1);
    }
}
