#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5


char playfairMatrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};


void findPosition(char letter, int *row, int *col) {
	int i,j;
    if (letter == 'J') letter = 'I';  
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (playfairMatrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}


void encryptDigraph(char a, char b, char *encryptedA, char *encryptedB) {
    int row1, col1, row2, col2;
    findPosition(a, &row1, &col1);
    findPosition(b, &row2, &col2);

    if (row1 == row2) {
        
        *encryptedA = playfairMatrix[row1][(col1 + 1) % SIZE];
        *encryptedB = playfairMatrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        
        *encryptedA = playfairMatrix[(row1 + 1) % SIZE][col1];
        *encryptedB = playfairMatrix[(row2 + 1) % SIZE][col2];
    } else {
        
        *encryptedA = playfairMatrix[row1][col2];
        *encryptedB = playfairMatrix[row2][col1];
    }
}


void prepareMessage(char *message, char *prepared) {
	int i,j;
    int len = 0;
    for (i = 0; message[i] != '\0'; i++) {
        if (isalpha(message[i])) {
            prepared[len++] = toupper(message[i]);
        }
    }
    prepared[len] = '\0';
}


void insertXBetweenRepeats(char *message) {
	int i;
    int len = strlen(message);
    for (i = 0; i < len - 1; i += 2) {
        if (message[i] == message[i + 1]) {
            memmove(&message[i + 2], &message[i + 1], len - i);
            message[i + 1] = 'X';  
            len++;
        }
    }
}


void encryptMessage(char *message) {
	int i;
    char preparedMessage[100];
    prepareMessage(message, preparedMessage);
    insertXBetweenRepeats(preparedMessage);
    int len = strlen(preparedMessage);

    
    if (len % 2 != 0) {
        preparedMessage[len++] = 'X';
        preparedMessage[len] = '\0';
    }

    printf("Encrypted message: ");
    for (i = 0; i < len; i += 2) {
        char encryptedA, encryptedB;
        encryptDigraph(preparedMessage[i], preparedMessage[i + 1], &encryptedA, &encryptedB);
        printf("%c%c", encryptedA, encryptedB);
    }
    printf("\n");
}

int main() {
    char message[] = "Must see you over Cadogan West. Coming at once.";

    encryptMessage(message);

    return 0;
}

