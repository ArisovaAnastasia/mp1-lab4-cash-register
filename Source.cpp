#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>
struct product
{
	char code[5];
	char name[64];
	int price, count, discount;
};
struct product base[100];
int t;
int check[100]{ 0 };

void info(int l) {
	int price = base[l].price - (base[l].price * (float)base[l].discount / 100);
	int sum = price * base[l].count;
	printf("��������: %s\n", base[l].name);
	printf("���� %i\n", base[l].price);
	printf("����������: %i\n", base[l].count);
	printf("������: %i %\n", base[l].discount);
	printf("����: %i %\n", sum);
	return;
}
int code(int l) {
	printf("������� �����-���\n");
	char checking[5];
	getchar();
	fgets(checking, 5, stdin);
	for (int i = 0; i < l; ++i) {
		if (!strcmp(checking, base[i].code)) {
			printf_s("���� ����� ��� ���������� � ���� .\n������� ���������� ");
			int amount;
			scanf_s("%i", &amount);
			base[i].count += amount;
			t = i;
			return l;
		}
	}
	t = l;
	strcpy_s(base[l].code, checking);
	printf_s("������� ���������� � ��������\n");
	printf_s("���: ");
	getchar();
	fgets(base[l].name, 64, stdin);
	printf_s("\n����: ");
	scanf_s("%i", &base[l].price);
	printf_s("\n����������: ");
	scanf_s("%i", &base[l].count);
	printf_s("\n������: ");
	do {
		scanf_s("%i", &base[l].discount);
	} while (base[l].discount > 50 || base[l].discount < 1);
	return ++l;
}
void check_pr(int l) {
	int t = 0;
	int price;
	int sum;
	for (int i = 0; i < l; ++i) {
		int j = check[i];
		price = base[j].price - (base[j].price * (float)base[j].discount) / 100;
		sum = price * base[j].count;
		t += sum;
		printf("%s\n", base[j].name);
		printf("���� %i\n", base[j].count, base[j].price);
		//printf("����� ����� ��� ������: %i\n", sum);
		printf("\n");
	}
	printf("����� �����: %i\n", t);
	return;
}
int main(){
	setlocale(LC_ALL, "rus");
	printf_s("�������� ����\n");
	printf_s("1 ������������� ��������� �����\n");
	printf_s("2 ������� �������� ���������������� ������,\n");
	printf_s("3 �������� ������ � ������ � ���,\n");
	printf_s("4 ������������ ��� �� �������, ���������� �������� ����� � ������,\n");
	printf_s("5 ������ ������������ ������ ����,\n");
	printf_s("6 ��������� ���������.\n");
	int key;
	int pos = 0;
	int l = 0;
	do {
		printf_s("\n");
		scanf_s("%i", &key);
		if (key <= 0 || key > 6)
			printf("������� ����� ����\n");
		switch (key) {
		case 1:
			l = code(l);
			break;
		case 2:
			if (l == 0)
				printf_s("��� ������:");
			else
				info(l - 1);
			break;
		case 3:
			if (l == 0)
				printf_s("��� ������:\n");
			else if (t == l - 1) {
				check[pos++] = l - 1;
				t = l;
			}

			else
				printf("���� ������ ���� ��� � ����\n");
			break;
		case 4:
			printf("�� ������� ������������ ��� �� �������\n");
			if (check[0] == -1);
			else
				check_pr(pos);
			break;
		case 5:
			printf("�� ������� ������������ ����� ��� ");
			for (int i = 0; i < 100; ++i)
				check[i] = 0;
			break;
		case 6:
			printf("�� ������� ��������� ��������� ");
			return 0;
			break;
		}
	} while (true);
}