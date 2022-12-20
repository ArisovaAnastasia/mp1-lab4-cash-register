#include <stdio.h>
#include <string.h>
#include<locale.h>
#include<stdlib.h>
int price[100]{};char name[1000][40];char code[100][5] = { 0 };int disc[100];int colv[1000];int y;char num;
int j = 0;int dann[100] = {-1};
int barcode(int k) {
	printf("enter a 4-character barcode\n");
	char chek[5];
	getchar();
	fgets(chek, 5, stdin);
	for (int i = 0; i < k; ++i) {
		if (!strcmp(chek, code[i])) {
			printf_s("the barcode is already in the database.");
			printf_s("enter the quantity of the product\n");
			int buf;
			scanf_s("%i", &buf);
			colv[i] += buf;
			y = i;
			return k;
		}
	}
	y = k;
	strcpy_s(code[k], chek);
	printf_s("enter the product name\n");
	getchar();
	fgets(name[k], 40, stdin);
	printf_s("enter the price for 1 item\n");
	scanf_s("%i", &price[k]);
	do { printf_s("enter  discount on the product\n");scanf_s("%i", &disc[k]); } while (disc[k] == 0);
	printf_s("enter the number of products\n");
	scanf_s("%i", &colv[k]);
	return ++k;
}
void description(int k) {
	int prc = price[k] - (price[k] * (float)disc[k] / 100);
	printf("product name:");printf("%s", name[k]);
	printf("\nprice for 1 item:");printf("%i", price[k]);
	printf("\ndiscount on the product:");printf("%i", disc[k]);
	printf("\ntotal amount for the product");printf("%i\n", colv[k] * prc);
}

void chekk(int f) {
	int prs = 0;int i = 0;int a = 0;
	do {

		i = dann[a];
		prs = prs + colv[i] * (price[i] - (price[i] * (float)disc[i] / 100));
		printf("\nproduct name:");printf("%s", name[i]);
		printf("\nprice for 1 item:");printf("%i", price[i]);
		printf("\ndiscount on the product:");printf("%i", disc[i]);
		printf("\nnumber of products");printf("%i\n", colv[i]);
		a++;
	} while (a<f);
	printf("price=");printf("%i\n", prs);
}

int main() {
	printf("press 1 to scan the product\n");
	printf("press 2 to display a description of the scanned product\n");
	printf("press 3 to add product details to the receipt\n");
	printf("press 4 to generate a receipt and record the total amount\n");
	printf("press 5 to generate a new receipt\n");
	printf("press 6 to finish\n");
	int k = 0;int f = 0;
	while (j == 0) {
		printf("enter the operation number\n");
		scanf_s("%c", &num);
		switch (num) {
		case'1':
			k = barcode(k);
			break;
		case'2':
			if (k == 0) {
				printf("you didn't enter any barcodes");
			}
			else { description(y); }
			break;
		case '3':
			if (k == 0) {
				printf("you have not entered any code");
			}
			else {
				printf("the product was added to the receipt\n");
				dann[f] = k - 1;
				f++;
			}break;
		case '4':
			chekk(f);
			break;
		case '5':
			printf("a new receipt has been started");
			code[100][5] = {0};colv[1000] = { 0 };y = 0;k = 0;
			break;
		case '6':
			printf("end of the program");
			j++;
			break;}}}