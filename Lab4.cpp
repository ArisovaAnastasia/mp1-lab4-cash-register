#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <random>
#include <string.h>
#include <time.h>

struct article {
	char code[5] = {'0'};
	char name[20] = {'0'};
	int price = 0;
	int amount = 0;
	float discount = 0;
};

int main() {
	srand(time(NULL));
	article chek[50];
	int art, i, j, is, num;
	float payment;
	int article_amount = 0;
	char name[20], code[5];
	int choice = 0;
	int price, amount;
	while (choice != 5) {
		printf("\nMenu\n1)Scan an article\n2)Check the article in list\n3)Show total price\n4)Create new list\n5)Leave the program\n");
		scanf_s("%i", &choice);
		switch (choice) {


		case 1:
			printf("Input a code\n");
			getchar();
			gets_s(code);
			is = 0;
			art = 0;
			for (i = 0; i < article_amount; ++i) {
				if (!strcmp(code, chek[i].code)) {
					is = 1;
					art = i;
				}
			}
			if (is == 0) {
				article_amount += 1;
				strcpy(chek[article_amount - 1].code, code);
				printf("New code. Input a name\n");
				gets_s(name);
				strcpy(chek[article_amount - 1].name, name);
				printf("Input a price\n");
				scanf_s("%i", &price);
				chek[article_amount-1].price = price;
				printf("Input an amount\n");
				scanf_s("%i", &amount);
				chek[article_amount-1].amount += amount;
				chek[article_amount-1].discount = 1 + rand() % 50;
			}
			else {
				printf("Existing code. Input an amount\n");
				scanf_s("%i", &amount);
				chek[art].amount += amount;
			}
			break;


		case 2:
			scanf_s("%i", &num);
			printf("Name: ");
			puts(chek[num-1].name);
			printf("Price:");
			printf("%i", chek[num-1].price);
			printf("\nAmount: ");
			printf("%i", chek[num-1].amount);
			printf("\nDiscount: ");
			printf("%f %", chek[num-1].discount);
			printf("\nPrice for all amount: ");
			printf("%f", chek[num-1].amount * chek[num - 1].price * (100 - chek[num - 1].discount) / 100);
			break;


		case 3:
			payment = 0;
			printf("\n");
			for (i = 0; i < article_amount; ++i) {
				printf("%i)", i + 1);
				puts(chek[i].name);
				printf("   x%i", chek[i].amount);
				printf(" - %f\n", chek[i].amount * chek[i].price * (100 - chek[i].discount) / 100);
				payment += chek[i].amount * chek[i].price * (100 - chek[i].discount) / 100;
			}
			printf("Total - %f\n", payment);
			break;


		case 4:
			article_amount = 0;
			break;


		case 5:
			break;
		}
	}
	return 0;
}