#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MOD 26


int key[2][2] = {
    {9, 4},
    {5, 7}
};


int charToNum(char c) {
    return toupper(c) - 'A';
}


char numToChar(int n) {
    return n + 'A';
}


void encryptPair(int x1, int x2, int *y1, int *y2) {
    *y1 = (key[0][0] * x1 + key[0][1] * x2) % MOD;
    *y2 = (key[1][0] * x1 + key[1][1] * x2) % MOD;
}


void prepareMessage(char *message, char *prepared) {
    int len = 0;
    for (int i = 0; message[i] != '\0'; i++) {
        if (isalpha(message[i])) {
            prepared[len++] = toupper(message[i]);
        }
    }
    
    if (len % 2 != 0) {
        prepared[len++] = 'X';
    }
    prepared[len] = '\0';
}

void encryptMessage(char *message) {
    char prepared[100];
    prepareMessage(message, prepared);
    int len = strlen(prepared);

    printf("Encrypted message: ");
    for (int i = 0; i < len; i += 2) {
        int x1 = charToNum(prepared[i]);
        int x2 = charToNum(prepared[i + 1]);
        int y1, y2;
        encryptPair(x1, x2, &y1, &y2);
        printf("%c%c", numToChar(y1), numToChar(y2));
    }
    printf("\n");
}

int main() {
    char message[] = "meet me at the usual place at ten rather than eight oclock";
    
    encryptMessage(message);
    
    return 0;
}

