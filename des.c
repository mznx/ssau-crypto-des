#include "des.h"

// таблица начальной перестановки IP
const char IP[] = {
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17,  9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

// таблица расширения E
const char E[] = {
	32,  1,  2,  3,  4,  5,
	 4,  5,  6,  7,  8,  9,
	 8,  9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17,	18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32,  1
};

// таблица преобразований S
const char S[] = {
	// S1
	14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
	 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
	 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
	15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,
	// S2
	15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
	// S3
	10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,
	// S4
	 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
	 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,
	// S5
	 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,
	// S6
	12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,
	// S7
	 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
	 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
	 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
	// S8
	13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
	 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
	 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
	 2, 1,  14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};

// таблица перестановок P
const char P[] = {
	16,  7, 20, 21, 29, 12, 28, 17,
	 1, 15, 23, 26,  5, 18, 31, 10,
	 2,  8, 24, 14, 32, 27,  3,  9,
	19, 13, 30,  6, 22, 11,  4, 25
};

// таблица конечной перестановки FP
const char FP[] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41,  9, 49, 17, 57, 25
};

// таблица перевода 64-битного ключа в 56-битный
const char K_1[] = {
	57, 49, 41, 33, 25, 17,  9,
	 1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27,
	19, 11,  3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	 7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29,
	21, 13,  5, 28, 20, 12,  4
};

// таблица перевода 56-битного ключа в 48-битный
const char K_2[] = {
	14, 17, 11, 24,  1,  5,
	 3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8,
	16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

// таблица сдвигов
const char K_S[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };


/*---  FUNCTIONS  ---*/

void encrypt(const char* plaintext_filename, const char* key_filename, const char mode) {
	void (*cipher)(char*, const char*, char*, char*) = desECB;
	char* iv = NULL;																		// initial vector
	switch (mode) {
	case '1':	// ECB
		break;
	case '2':	// CBC
		cipher = desCBC;
		iv = generateIV();
		break;
	case '3':	// CFB
		cipher = desCFB;
		iv = generateIV();
		break;
	case '4':	// OFB
		cipher = desOFB;
		iv = generateIV();
		break;
	default:
		printf("Wrong value!\n");
		return;
	}

	// сохраняем initial vector или выходим, если не удалось
	if (iv != NULL && !saveIVToFile(iv)) return;


	struct file plaintext = readFile(plaintext_filename);									// открытый текст
	if (plaintext.data == NULL) return;
	const char* key_56bit = getKeyAsBitArr(key_filename);									// 56 битный ключ как 56 байтовый массив
	if (key_56bit == NULL) return;
	const char* keys = generateRoundKeys(key_56bit);										// раундовые ключи как массив 16 x 48 байт

	char* encrypted_text = (char*)malloc(plaintext.size * sizeof(char));
	memset(encrypted_text, 0, plaintext.size * sizeof(char));

	// поблочное шифрование
	for (unsigned long block_num = 0; block_num < plaintext.size * CHAR_SIZE_BIT / BLOCK_SIZE_BIT; block_num++) {
		char* block_64bit = textToBitBlock(plaintext.data, block_num);						// T (64 битный блок как 64 байтовый массив)
		cipher(block_64bit, keys, iv, "enc");												// шифруем
		bitBlockToText(encrypted_text, block_64bit, block_num);								// записываем зашифрованный блок
		free(block_64bit);
	}

	createEncryptedFile(encrypted_text, plaintext.size);

	free(encrypted_text);
	free(plaintext.data);
	free(key_56bit);
	free(keys);
}


void decrypt(const char* ciphertext_filename, const char* key_filename, const char mode) {
	void (*cipher)(char*, const char*, char*, char*) = desECB;
	char* iv = NULL;
	switch (mode) {
	case '1':	// ECB
		break;
	case '2':	// CBC
		cipher = desCBC;
		iv = readIVFromFile();
		break;
	case '3':	// CFB
		cipher = desCFB;
		iv = readIVFromFile();
		break;
	case '4':	// OFB
		cipher = desOFB;
		iv = readIVFromFile();
		break;
	default:
		printf("Wrong value!\n");
		return;
	}

	// выходим, если не удалось получить initial vector
	if (mode != '1' && iv == NULL) return;

	struct file ciphertext = readFile(ciphertext_filename);									// шифротекст
	if (ciphertext.data == NULL) return;
	const char* key_56bit = getKeyAsBitArr(key_filename);									// 56 битный ключ как 56 байтовый массив
	if (key_56bit == NULL) return;
	char* keys = generateRoundKeys(key_56bit);												// раундовые ключи как массив 16 x 48 байт
	if (mode == '1' || mode == '2') flipKeys(keys);											// если ECB или CBC - разворачиваем список ключей

	char* decrypted_text = (char*)malloc(ciphertext.size * sizeof(char));
	memset(decrypted_text, 0, ciphertext.size * sizeof(char));

	// поблочное дешифрование
	for (unsigned long block_num = 0; block_num < ciphertext.size * CHAR_SIZE_BIT / BLOCK_SIZE_BIT; block_num++) {
		char* block_64bit = textToBitBlock(ciphertext.data, block_num);						// T (64 битный блок как 64 байтовый массив)
		cipher(block_64bit, keys, iv, "dec");												// шифруем
		bitBlockToText(decrypted_text, block_64bit, block_num);								// записываем расшифрованный блок
		free(block_64bit);
	}

	createDecryptedFile(decrypted_text, ciphertext.size);

	free(decrypted_text);
	free(ciphertext.data);
	free(key_56bit);
	free(keys);
}


void DES(char* block_64bit, const char* keys) {
	permutationIP(block_64bit);																// IP(T)

	// раунды шифрования блока
	for (unsigned int round = 0; round < ROUNDS_NUM; round++) {
		char* k_i = keys + round * ROUND_KEY_SIZE;											// k_i (указатель на 48 битный раундовый ключ как 48 байтовый массив)
		char* L_j = copyBitArr(block_64bit, BLOCK_SIZE_BIT / 2);							// L_(i-1) при шифровании, L_(i+1) при дешифровании
		char* R_j = copyBitArr(block_64bit + BLOCK_SIZE_BIT / 2, BLOCK_SIZE_BIT / 2);		// R_(i-1) при шифровании, R_(i+1) при дешифровании

		char* L_i = R_j;																	// L_i
		char* R_i = xor (L_j, f(R_j, k_i), 32);												// R_i = L_j XOR f(R_j, k_i)

		setBlockBitArr(block_64bit, L_i, R_i);												// T_i = L_iR_i

		// free
		free(L_j);
		free(R_j);
		free(R_i);
	}

	// последняя перестановка
	char* L_n = copyBitArr(block_64bit, BLOCK_SIZE_BIT / 2);								// L_16 при шифровании
	char* R_n = copyBitArr(block_64bit + BLOCK_SIZE_BIT / 2, BLOCK_SIZE_BIT / 2);			// R_16 при Шифровании
	setBlockBitArr(block_64bit, R_n, L_n);													// T = R_nL_n
	permutationFP(block_64bit);																// FP(T)

	// free
	free(L_n);
	free(R_n);
}


char* getKeyAsBitArr(const char* filename) {
	FILE* fp;
	errno_t err;
	char* key_56bit = calloc(56, sizeof(char));
	memset(key_56bit, 0, 56 * sizeof(char));

	if ((err = fopen_s(&fp, filename, "rb")) != 0) {
		printf("File \"%s\" was not opened.\n", *filename);
		free(key_56bit);
		key_56bit = NULL;
	}
	else {
		// читаем из файла 64 бита (8 байт)
		char key[8] = { 0 };
		fread(key, sizeof(char), 8, fp);
		fclose(fp);

		// переводим в битовое представление
		char key_64bit[64] = { 0 };
		unsigned int bit_num = 0;
		for (int i = 0; i < 8; i++)
			for (int j = 7; j >= 0; j--) {
				if (key[i] & (1 << j)) key_64bit[bit_num] = 1;
				++bit_num;
			}

		// перестановка 64 битного ключа в 56 битный
		for (int i = 0; i < 56; i++)
			key_56bit[i] = key_64bit[K_1[i] - 1];
	}

	return key_56bit;
}


char* generateRoundKeys(const char* key_56bit) {
	char* keys = (char*)calloc(16, 48 * sizeof(char));
	memset(keys, 0, 16 * 48 * sizeof(char));

	for (int i = 0; i < 16; i++) {
		const int l_shift = K_S[i];
		char* C_i = key_56bit;
		char* D_i = key_56bit + 28;

		const char C_num1 = C_i[0];		// первое значение из матрицы C
		const char C_num2 = C_i[1];		// второе значение из матрицы C
		const char D_num1 = D_i[0];		// первое значение из матрицы D
		const char D_num2 = D_i[1];		// второе значение из матрицы D

		// сдвиг матриц влево значение для данного раунда
		for (int i = 0; i < 28 - l_shift; i++) {
			C_i[i] = C_i[i + l_shift];
			D_i[i] = D_i[i + l_shift];
		}

		// вставка в конец значений из начала
		if (l_shift == 1) {
			C_i[27] = C_num1;
			D_i[27] = D_num1;
		}
		else {
			C_i[26] = C_num1;
			C_i[27] = C_num2;
			D_i[26] = D_num1;
			D_i[27] = D_num2;
		}

		// вывод C_i, D_i
		/*
		printf("C%d: ", i + 1);
		for (int i = 0; i < 28; i++) printf("%d", C_i[i]);
		printf("\nD%d: ", i + 1);
		for (int i = 0; i < 28; i++) printf("%d", D_i[i]);
		printf("\n\n");
		*/

		// выборка
		for (int j = 0; j < 48; j++)
			keys[i * 48 + j] = key_56bit[K_2[j] - 1];
	}

	// вывод ключей
	/*
	for (int i = 0; i < 16; i++) {
		printf("K%d: ", i+1);
		for (int k = 0; k < 8; k++) {
			for (int j = 0; j < 6; j++)
				printf("%d", keys[i * 48 + k * 6 + j]);
			printf(" ");
		}
		printf("\n");
	}
	*/

	return keys;
}


char* textToBitBlock(const char* text, const unsigned long num) {
	char* block_64bit = (char*)calloc(BLOCK_SIZE_BIT, sizeof(char));
	memset(block_64bit, 0, BLOCK_SIZE_BIT * sizeof(char));
	unsigned int bit_num = 0;

	// проходим по байтам
	for (int i = 0; i < 8; i++) {
		// проходим по битам
		for (int j = 7; j >= 0; j--) {
			if (text[num * 8 + i] & (1 << j)) block_64bit[bit_num] = 1;
			++bit_num;
		}
	}

	return block_64bit;
}


void permutationIP(char* block_64bit) {
	char* block_64bit_copy = (char*)calloc(BLOCK_SIZE_BIT, sizeof(char));
	memcpy(block_64bit_copy, block_64bit, BLOCK_SIZE_BIT * sizeof(char));

	for (int i = 0; i < BLOCK_SIZE_BIT; i++)
		block_64bit[i] = block_64bit_copy[IP[i] - 1];

	free(block_64bit_copy);
}


char* f(const char* block_32bit, const char* k_i) {
	char* E_i = (char*)malloc(48 * sizeof(char));
	memset(E_i, 0, 48 * sizeof(char));

	// расширение до 48-битного вектора
	for (int i = 0; i < 48; i++)
		E_i[i] = block_32bit[E[i] - 1];

	// сложение 48 битного вектора с ключем
	char* B = xor (E_i, k_i, 48);

	// преобразуем 6-битные блоки в 4-битные
	char* B_2 = (char*)malloc(32 * sizeof(char));
	for (int i = 0; i < 8; i++) {
		int offset = i * 6;
		int a = binToDec(B[offset] * 10 + B[offset + 5]);
		int b = binToDec(B[offset + 1] * 1000 + B[offset + 2] * 100 + B[offset + 3] * 10 + B[offset + 4]);

		int dec_num = S[i * 64 + a * 16 + b];
		char* B_i = decToBin(dec_num);
		for (int j = 0; j < 4; j++) B_2[i * 4 + j] = B_i[j];

		free(B_i);
	}

	// перестановка P
	char* P_i = (char*)malloc(32 * sizeof(char));
	memset(P_i, 0, 32 * sizeof(char));
	for (int i = 0; i < 32; i++) P_i[i] = B_2[P[i] - 1];

	free(E_i);
	free(B);
	free(B_2);

	return P_i;
}


void setBlockBitArr(char* block_64bit, const char* L_i, const char* R_i) {
	for (unsigned int i = 0; i < BLOCK_SIZE_BIT / 2; i++) {
		block_64bit[i] = L_i[i];
		block_64bit[BLOCK_SIZE_BIT / 2 + i] = R_i[i];
	}
}


void permutationFP(char* block_64bit) {
	char* block_64bit_copy = (char*)calloc(BLOCK_SIZE_BIT, sizeof(char));
	memcpy(block_64bit_copy, block_64bit, BLOCK_SIZE_BIT * sizeof(char));

	for (int i = 0; i < BLOCK_SIZE_BIT; i++) {
		block_64bit[i] = block_64bit_copy[FP[i] - 1];
	}

	free(block_64bit_copy);
}


void bitBlockToText(char* encrypted_text, const char* block_64bit, const unsigned long block_num) {
	// проходим по байтам
	for (int i = 0; i < 8; i++) {
		char symbol = 0;
		// проходим по битам
		for (int j = 0; j < 8; j++) {
			if (block_64bit[i * 8 + j] == 1)
				symbol |= (1 << 7 - j);
		}

		encrypted_text[block_num * 8 + i] = symbol;
	}
}


char* generateIV() {
	char* iv = (char*)malloc(BLOCK_SIZE_BIT * sizeof(char));

	srand(time(NULL));
	for (unsigned int i = 0; i < BLOCK_SIZE_BIT; i++) {
		iv[i] = rand() % 2;
	}

	return iv;
}


void flipKeys(char* keys) {
	char* keys_copy = (char*)calloc(ROUNDS_NUM, ROUND_KEY_SIZE * sizeof(char));
	memcpy(keys_copy, keys, ROUNDS_NUM * ROUND_KEY_SIZE * sizeof(char));
	unsigned int key_num = 0;

	for (unsigned int i = 0; i < ROUNDS_NUM; i++) {
		memcpy(keys + i * 48, keys_copy + (ROUNDS_NUM - 1) * ROUND_KEY_SIZE - i * ROUND_KEY_SIZE, ROUND_KEY_SIZE);
	}

	free(keys_copy);
}


/*---  DES MODES  ---*/

void desECB(char* block_64bit, const char* keys, char* iv, char* mode) {
	DES(block_64bit, keys);
}


void desCBC(char* block_64bit, const char* keys, char* iv, char* mode) {
	char* iv_next = NULL;

	if (mode == "dec") {
		iv_next = (char*)malloc(BLOCK_SIZE_BIT * sizeof(char));
		memcpy(iv_next, block_64bit, BLOCK_SIZE_BIT * sizeof(char));
	}
	else {
		char* block_xor = xor (block_64bit, iv, BLOCK_SIZE_BIT);
		memcpy(block_64bit, block_xor, BLOCK_SIZE_BIT);
	}

	DES(block_64bit, keys);

	if (mode == "dec") {
		char* block_xor = xor (block_64bit, iv, BLOCK_SIZE_BIT);
		memcpy(block_64bit, block_xor, BLOCK_SIZE_BIT);
		memcpy(iv, iv_next, BLOCK_SIZE_BIT * sizeof(char));
		free(iv_next);
	}
	else {
		memcpy(iv, block_64bit, BLOCK_SIZE_BIT);
	}
}


void desCFB(char* block_64bit, const char* keys, char* iv, char* mode) {
	char* block_64bit_copy = (char*)malloc(BLOCK_SIZE_BIT * sizeof(char));
	memcpy(block_64bit_copy, block_64bit, BLOCK_SIZE_BIT * sizeof(char));
	memcpy(block_64bit, iv, BLOCK_SIZE_BIT * sizeof(char));

	DES(block_64bit, keys);

	char* block_xor = xor (block_64bit, block_64bit_copy, BLOCK_SIZE_BIT);
	memcpy(block_64bit, block_xor, BLOCK_SIZE_BIT * sizeof(char));
	if (mode == "dec") {
		memcpy(iv, block_64bit_copy, BLOCK_SIZE_BIT * sizeof(char));
	}
	else {
		memcpy(iv, block_64bit, BLOCK_SIZE_BIT * sizeof(char));
	}
	free(block_xor);
	free(block_64bit_copy);
}


void desOFB(char* block_64bit, const char* keys, char* iv, char* mode) {
	char* block_64bit_copy = (char*)malloc(BLOCK_SIZE_BIT * sizeof(char));
	memcpy(block_64bit_copy, block_64bit, BLOCK_SIZE_BIT * sizeof(char));
	memcpy(block_64bit, iv, BLOCK_SIZE_BIT * sizeof(char));

	DES(block_64bit, keys);

	memcpy(iv, block_64bit, BLOCK_SIZE_BIT * sizeof(char));

	char* block_xor = xor (block_64bit, block_64bit_copy, BLOCK_SIZE_BIT);
	memcpy(block_64bit, block_xor, BLOCK_SIZE_BIT * sizeof(char));

	free(block_xor);
	free(block_64bit_copy);
}


/*---  HELP FUNCTIONS  ---*/

struct file readFile(const char* filename) {
	FILE* fp;
	errno_t err;
	struct file input_file = { NULL, 0L };

	if ((err = fopen_s(&fp, filename, "rb")) != 0) {
		printf("File \"%s\" was not opened.\n", *filename);
	}
	else {
		// получаем размер файла в байтах
		fseek(fp, 0L, SEEK_END);
		const unsigned long file_size = ftell(fp);
		fseek(fp, 0L, SEEK_SET);

		// вычисляем необходимое число байт
		// для дополнения до 64 бит последнего блока
		unsigned long additional_size = (BLOCK_SIZE_BIT - ((file_size * CHAR_SIZE_BIT) % BLOCK_SIZE_BIT)) / CHAR_SIZE_BIT;
		if (additional_size == CHAR_SIZE_BIT) additional_size = 0;

		// пишем файл в память, дополняя нулями, если необходимо
		input_file.size = file_size + additional_size;
		input_file.data = (char*)malloc(input_file.size * sizeof(char));
		memset(input_file.data, 0, input_file.size);
		fread(input_file.data, sizeof(char), file_size, fp);

		fclose(fp);
	}

	return input_file;
}


char* copyBitArr(const char* address, const unsigned int size) {
	char* data = (char*)malloc(size * sizeof(char));
	memset(data, 0, size);

	for (int i = 0; i < size; i++)
		data[i] = address[i];

	return data;
}


char* xor(const char* vec1, const char* vec2, const unsigned int size) {
	char* result = (char*)malloc(size * sizeof(char));

	for (unsigned int i = 0; i < size; i++) {
		if (vec1[i] == 0 && vec2[i] == 0) {
			result[i] = 0;
		}
		else if (vec1[i] == 0 && vec2[i] == 1) {
			result[i] = 1;
		}
		else if (vec1[i] == 1 && vec2[i] == 0) {
			result[i] = 1;
		}
		else if (vec1[i] == 1 && vec2[i] == 1) {
			result[i] = 0;
		}
	}

	return result;
}


int binToDec(int bin_num) {
	int dec_num = 0;
	int digit;
	int base = 1;

	while (bin_num > 0) {
		digit = bin_num % 10;
		dec_num += digit * base;
		bin_num /= 10;
		base *= 2;
	}

	return dec_num;
}


char* decToBin(int dec_num) {
	char* bin_num = (char*)malloc(4 * sizeof(char));
	memset(bin_num, 0, 4 * sizeof(char));

	for (int i = 3; dec_num > 0; i--) {
		bin_num[i] = dec_num % 2;
		dec_num /= 2;
	}

	return bin_num;
}


void createEncryptedFile(const char* encrypted_text, const unsigned long size) {
	FILE* fp = NULL;
	errno_t err;

	if ((err = fopen_s(&fp, ENC_FILENAME, "wb")) != 0) {
		printf("Failed to save encrypted file.\n");
	}
	else {
		fwrite(encrypted_text, sizeof(char), size, fp);
		fclose(fp);
		printf("Encrypted file \"%s\" was created.\n", ENC_FILENAME);
	}
}


void createDecryptedFile(const char* decrypted_text, const unsigned long size) {
	FILE* fp = NULL;
	errno_t err;

	if ((err = fopen_s(&fp, DEC_FILENAME, "wb")) != 0) {
		printf("Failed to save decrypted file.\n");
	}
	else {
		fwrite(decrypted_text, sizeof(char), size, fp);
		fclose(fp);
		printf("Decrypted file \"%s\" was created.\n", DEC_FILENAME);
	}
}


char saveIVToFile(const char* iv) {
	char* iv_8byte = (char*)malloc(8 * sizeof(char));

	// проходим по байтам
	for (int i = 0; i < 8; i++) {
		char symbol = 0;
		// проходим по битам
		for (int j = 0; j < 8; j++) {
			if (iv[i * 8 + j] == 1)
				symbol |= (1 << 7 - j);
		}

		iv_8byte[i] = symbol;
	}

	FILE* fp;
	errno_t err;

	if ((err = fopen_s(&fp, IV_FILENAME, "wb")) != 0) {
		printf("Failed to save Initial vector file.\n");
		return 0;
	}
	else {
		fwrite(iv_8byte, sizeof(char), 8, fp);
		fclose(fp);
		printf("Initial vector file \"%s\" was created. SAVE THIS FILE!\n", IV_FILENAME);
	}

	return 1;
}


char* readIVFromFile() {
	FILE* fp;
	errno_t err;
	char* iv = (char*)malloc(BLOCK_SIZE_BIT * sizeof(char));
	memset(iv, 0, BLOCK_SIZE_BIT * sizeof(char));

	if ((err = fopen_s(&fp, IV_FILENAME, "rb")) != 0) {
		printf("Could not open Initial vector file.\n");
		free(iv);
		iv = NULL;
	}
	else {
		// читаем из файла 64 бита (8 байт)
		char iv0[8] = { 0 };
		fread(iv0, sizeof(char), 8, fp);
		fclose(fp);

		// переводим в битовое представление
		unsigned int bit_num = 0;
		// проходим по байтам
		for (int i = 0; i < 8; i++) {
			// проходим по битам
			for (int j = 7; j >= 0; j--) {
				if (iv0[i] & (1 << j)) iv[bit_num] = 1;
				++bit_num;
			}
		}
	}

	return iv;
}