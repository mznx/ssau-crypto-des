#include <stdio.h>
#include "des.h"


#define PLAINTEXT_FILENAME	"source.txt"
#define CIPHERTEXT_FILENAME "encrypted.des"
#define KEY_FILENAME		"key.txt"


int main() {
	char menu[64] = { 0 };
	printf("Menu:\n[1] Encrypt file\n[2] Decrypt file\n\n>: ");
	gets(menu, 64);

	switch (menu[0]) {
	case '1':
		printf("\nSelect mode:\n[1] ECB - Electronic Codebook\n[2] CBC - Cipher Block Chaining\n[3] CFB - Cipher Feedback\n[4] OFB - Output Feedback\n\n>: ");
		gets(menu, 64);
		encrypt(PLAINTEXT_FILENAME, KEY_FILENAME, menu[0]);
		break;
	case '2':
		printf("\nSelect mode:\n[1] ECB - Electronic Codebook\n[2] CBC - Cipher Block Chaining\n[3] CFB - Cipher Feedback\n[4] OFB - Output Feedback\n\n>: ");
		gets(menu, 64);
		decrypt(CIPHERTEXT_FILENAME, KEY_FILENAME, menu[0]);
		break;
	default:
		printf("Wrong value!\n");
		break;
	}

	printf("\nPress any button...");
	getch();

	return 0;
}