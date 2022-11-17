#include <stdio.h>
#include <string.h>
#define N 10

char* barcodes[N] = { "1234", "2333", "1723", "9673", "5873", "2389", "1239", "2598", "7241", "3692" };
char* products[N] = { "snickers", "milk", "cheeze", "ketchup", "loaf", "beef", "pasta", "rice", "pepper", "salt" };
float price[N] = { 40.0f, 60.0f, 150.0f,  80.0f,  30.0f,  200.0f,  90.0f,  45.0f,  20.0f,  10.0f };
float discount[N] = { 1, 23, 15, 10, 34, 10, 40, 25, 15, 50 };
void printReceipt(int* array) {
	float totalCost = 0;
	printf("Your check: \n");
	for (int i = 0; i < N; i++) {
		if (array[i] == 0)
			continue;
		printf("%s, final price - %.2f, %d units.\n", products[i], (price[i] * (1 - (discount[i] / 100))), array[i]);
		totalCost += (price[i] * (1 - (discount[i] / 100))) * array[i];
	}
	printf("Total cost - %.2f", totalCost);
}
void scan(int* array) {
	char* bc[1];

	printf("Strting scan\nTo complete the scan, enter: Stop\nEnter barcodes\n ");
	while (strcmp(bc, "Stop")) {
		gets(bc);
		if (strcmp(bc, "Stop")) {
			for (int i = 0; i < N; i++) {
				if (strcmp(barcodes[i], bc) == 0) {
					printf("%s, price: %.2f, diccount: %.2f %\n", products[i], price[i], discount[i]);
					array[i] += 1;
				}
			}
		}
	}
}
int main() {
	int counts[N] = { 0 };
	scan(counts);
	printReceipt(counts);
	return 0;
}

