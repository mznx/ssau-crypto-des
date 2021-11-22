#ifndef DES_H
#define DES_H

#include <stdio.h>

#define BLOCK_SIZE_BIT	64	// размер блока в битах
#define CHAR_SIZE_BIT	8	// размер символа в битах
#define ROUNDS_NUM		16	// число раундов шифрования
#define ROUND_KEY_SIZE	48  // размер раундового ключа в битах
#define ENC_FILENAME	"encrypted.des"
#define DEC_FILENAME	"decrypted.txt"
#define IV_FILENAME		"initial_vector.iv"

struct file {
	char* data;
	unsigned long size;
};

/*---  FUNCTIONS  ---*/
void encrypt(const char* plaintext_filename, const char* key_filename, const char mode);
void decrypt(const char* ciphertext_filename, const char* key_filename, const char mode);
void DES(char* block_64bit, const char* keys);
char* getKeyAsBitArr(const char* filename);
char* generateRoundKeys(const char* key_bit);
char* textToBitBlock(const char* text, const unsigned long num);
void permutationIP(char* block_64bit);
char* f(const char* block_32bit, const char* k_i);
void setBlockBitArr(char* block_64bit, const char* L_i, const char* R_i);
void permutationFP(char* block_64bit);
void bitBlockToText(char* encrypted_text, const char* block_64bit, const unsigned long block_num);
char* generateIV();
void flipKeys(char* keys);

/*---  DES MODES  ---*/
void desECB(char* block_64bit, const char* keys, char* iv, char* mode);
void desCBC(char* block_64bit, const char* keys, char* iv, char* mode);
void desCFB(char* block_64bit, const char* keys, char* iv, char* mode);
void desOFB(char* block_64bit, const char* keys, char* iv, char* mode);

/*---  HELP FUNCTIONS  ---*/
struct file readFile(const char* filename);
char* copyBitArr(const char* address, const unsigned int size);
char*xor (const char* vec1, const char* vec2, const unsigned int size);
int binToDec(int bin_num);
char* decToBin(int dec_num);
void createEncryptedFile(const char* encrypted_text, const unsigned long size);
void createDecryptedFile(const char* decrypted_text, const unsigned long size);
char saveIVToFile(const char* iv);
char* readIVFromFile();

#endif