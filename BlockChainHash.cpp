#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int key[10] = { 2,3,5,7,11,13,17,19,23,29 };

unsigned int generateHash(char* string, int len)
{

	unsigned int hash = 0;
	for (int i = 0; i < len; ++i)
	{
		hash = 65599 * hash + string[i];
	}

	hash = hash * key[hash % 10];

	return hash ^ (hash >> 16);
}

unsigned int AssortingHash(unsigned int block1, unsigned int block2) {
	unsigned int sum = block1*65599 + block2*65599;
	unsigned int assortedhash = sum ^ (sum >> 16);
	return assortedhash;
}


int main() {
	char bill[101][101];

	puts("장부를 기록하십시오");
	gets_s(bill[0], 100);
	unsigned int block1 = generateHash(bill[0], strlen(bill[0]));
	printf("\n##입력장부 해시:%x", block1);;


	puts("\n\n장부를 기록하십시오");
	puts(bill[0]);
	gets_s(bill[1], 100);
	unsigned int block2 = generateHash(bill[1], strlen(bill[1]));
	printf("\n##입력장부 해시:%x", block2);


	puts("\n\n*합성 해시*");
	unsigned int AH = AssortingHash(block1, block2);
	printf("%x", AH);

	int i = 1;

	while (1) {

		++i;
		block1 = AH;

		puts("\n\n장부를 기록하십시오");
		for (int index = 0;index < i;index++) {
			puts(bill[index]);
		}
		gets_s(bill[i], 100);
		block2 = generateHash(bill[i], strlen(bill[i]));
		printf("\n##입력장부 해시:%x", block2);

		puts("\n\n*합성 해시*");
		AH = AssortingHash(block1, block2);
		printf("%x", AH);

		if (i > 100) return 0;
	}
	return 0;
}