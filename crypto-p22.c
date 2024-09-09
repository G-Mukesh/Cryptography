#include <stdio.h>
#include <string.h>

// XOR two blocks of binary data
void xorBlocks(unsigned char *a, unsigned char *b, unsigned char *result, int length) {
	int i;
    for ( i = 0; i < length; i++) {
        result[i] = a[i] ^ b[i];
    }
}

// Simplified DES (S-DES) Encryption function
void sdesEncrypt(unsigned char plaintext[8], unsigned char key[10], unsigned char ciphertext[8]) {
	int i;
    // S-DES encryption logic (simplified version for 8-bit block size)
    // You need to implement or call an S-DES function here
    // This is a placeholder
    for ( i = 0; i < 8; i++) {
        ciphertext[i] = plaintext[i] ^ key[i % 10];  // Example XOR operation (not actual S-DES)
    }
}

// Simplified DES (S-DES) Decryption function
void sdesDecrypt(unsigned char ciphertext[8], unsigned char key[10], unsigned char plaintext[8]) {
	int i;
    // S-DES decryption logic (simplified version for 8-bit block size)
    // You need to implement or call an S-DES function here
    // This is a placeholder
    for ( i = 0; i < 8; i++) {
        plaintext[i] = ciphertext[i] ^ key[i % 10];  // Example XOR operation (not actual S-DES)
    }
}

// CBC mode encryption
void cbcEncrypt(unsigned char plaintext[16], unsigned char key[10], unsigned char iv[8], unsigned char ciphertext[16]) {
	int i;
    unsigned char previousBlock[8], currentBlock[8];
    memcpy(previousBlock, iv, 8);  // Initialization Vector (IV)

    for ( i = 0; i < 16; i += 8) {
        xorBlocks(&plaintext[i], previousBlock, currentBlock, 8); // XOR with the previous ciphertext or IV
        sdesEncrypt(currentBlock, key, &ciphertext[i]);           // Encrypt the XORed result
        memcpy(previousBlock, &ciphertext[i], 8);                 // Store current ciphertext for next XOR
    }
}

// CBC mode decryption
void cbcDecrypt(unsigned char ciphertext[16], unsigned char key[10], unsigned char iv[8], unsigned char decryptedtext[16]) {
	int i;
    unsigned char previousBlock[8], decryptedBlock[8];
    memcpy(previousBlock, iv, 8);  // Initialization Vector (IV)

    for ( i = 0; i < 16; i += 8) {
        sdesDecrypt(&ciphertext[i], key, decryptedBlock);         // Decrypt the ciphertext block
        xorBlocks(decryptedBlock, previousBlock, &decryptedtext[i], 8); // XOR with previous ciphertext or IV
        memcpy(previousBlock, &ciphertext[i], 8);                 // Store current ciphertext for next XOR
    }
}

// Helper function to print binary data
void printBinary(unsigned char *data, int length) {
	int i;
    for ( i = 0; i < length; i++) {
        printf("%02X", data[i]);
    }
    printf("\n");
}

int main() {
    // Given test data
    unsigned char plaintext[16] = {0x00, 0x01, 0x02, 0x03};  // Binary plaintext: 0000 0001 0010 0011
    unsigned char key[10] = {0x0F, 0xFD};                    // Binary key: 01111 11101
    unsigned char iv[8] = {0xAA};                            // Binary IV: 1010 1010
    unsigned char ciphertext[16], decryptedtext[16];

    // Encryption using CBC mode
    printf("Original plaintext: ");
    printBinary(plaintext, 4);

    cbcEncrypt(plaintext, key, iv, ciphertext);
    printf("Ciphertext: ");
    printBinary(ciphertext, 4);

    // Decryption using CBC mode
    cbcDecrypt(ciphertext, key, iv, decryptedtext);
    printf("Decrypted plaintext: ");
    printBinary(decryptedtext, 4);

    return 0;
}

