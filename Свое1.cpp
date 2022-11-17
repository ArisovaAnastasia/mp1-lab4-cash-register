#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 16
void quickSort(int *a,int f1, int f2)
{
	if (f1 < f2) {
		int left = f1;
		int right = f2;
		int m = a[(left + right) / 2];
		do {
			while (a[left] < m)
				left++;
			while (a[right] > m)
				right--;
			if (left <= right) {
				int temp = a[left];
				a[left] = a[right];
				a[right] = temp;
				left++;
				right--;
			}
		} while (left < right);
		quickSort(a, f1, right);
		quickSort(a, left, f2);
	}
}
int main() {
	srand(time(NULL));
	int a[SIZE];
	for (int i = 0; i < SIZE; i++) {
		a[i] = (rand() % 100);
		printf(" %d ", a[i]);
	}
	quickSort(a, 0, SIZE - 1);
	printf("\n");
	for (int i = 0; i < SIZE; i++)
		printf(" %d ", a[i]);
	getchar();
	return 0;
}
