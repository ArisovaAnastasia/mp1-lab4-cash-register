#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<stdlib.h>


int Enter;//���������� ��� ������ � ���������� ������ 
int prices[100]{}, count[100]{}, discounts[100]; //������� ��� �� ������� ������, �����-�����,���������� ������� � ������
int check[100]{-1}; // ������ � ����
char codes[100][5]; // �����-����
char names[100][64]; // ������������ �������

//������� �������� ������� ���������

int barcode(int n) {
	printf("������� �����-��� �� 4 �������� �� 0 �� 9\n");
	char checking[5];
	getchar();
	fgets(checking, 5, stdin);//fflush �� �������� ����� scanf
	for (int i = 0; i < n; ++i) {
		if (!strcmp(checking, codes[i])){
			printf_s("���� ����� ��� ��� ���� � �������.\n������� ���������� ������: ");
			int buf; // ���������� ������ 
			scanf_s("%i", &buf);
			count[i] += buf;
			Enter = i;
			return n;
		}
	}
	Enter = n;
	strcpy_s(codes[n], checking);
	printf_s("������� ������ � ������\n");	
	printf_s("\n������� ������������ ������: ");
	getchar();
	fgets(names[n], 64 ,stdin);
	printf_s("\n������� ���� ������: ");
	scanf_s("%i", &prices[n]);
	printf_s("\n������� ���������� ������: ");
	scanf_s("%i", &count[n]);
	printf_s("\n������� ������ �� �����: ");
	do {
		scanf_s("%i", &discounts[n]);
	} while (discounts[n] > 50 || discounts[n] < 1);
	return ++n;
}

void info(int n) {
	int price = prices[n] - (prices[n] * (float)discounts[n]/100);
	int sum = price * count[n];
	printf("�������������� ������: %s\n", names[n]);
	printf("���� �� ������� ������: %i\n", prices[n]);
	printf("����������: %i\n", count[n]);
	printf("������: %i %\n", discounts[n]);
	printf("����: %i %\n", sum);
	return;
}

void checkMaker(int pos) {
	int total = 0;
	int price, sum;
	for (int i = 0; i < pos; ++i) {
		int ch = check[i];
		price = prices[ch] - (prices[ch] * (float)discounts[ch])/100;
		sum = price * count[ch];
		total += sum;
		printf("%s\n", names[ch]);
		printf("%i ��. x %i\n", count[ch], prices[ch]);
		printf("����� ��������� � ������ ������: %i\n", sum);
		printf("\n");
	}
	printf("�����: %i\n", total);
	return;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	printf_s("�������� ��������\n");
	printf_s("������� 1, ����� ����������� �����\n");
	printf_s("������� 2, ����� ������� �������� ���������������� ������\n");
	printf_s("������� 3, �������� ������ � ������ � ���\n");
	printf_s("������� 4, ����� ������������ ��� �� �������, ���������� �������� ����� � ������\n");
	printf_s("������� 5, ����� ������ ������������ ������ ����\n");
	printf_s("������� 6, ����� ��������� ���������\n");
	int operation;
	int pos = 0, n = 0; //������� ��� ���� � ���������� �����-����� � ����
	do{
		printf_s("�������� ����� ��������\n");
		scanf_s("%i", &operation);
		scanf_s("%*[^\n]");
		if (operation <= 0 || operation > 6)
			printf("������������ ����� ��������\n");
		switch (operation) {
		case 1:
			n = barcode(n);
			break;
		case 2:
			if (n == 0)
				printf_s("�� �� ������������� �� ������ ����\n");
			else if(Enter==n-1) {
				info(n-1);
			}
			else {
				info(Enter);
			}
			break;
		case 3:
			if (n == 0)
				printf_s("�� �� ������������� �� ������ ����\n");
			else if (Enter == n - 1)
				check[pos++] = n - 1;
			else 
				printf("����� ��� ���� � ����\n");
			break;
		case 4:
			if (check[0] == -1)
				printf("��� ������\n");
			else
				checkMaker(pos);
			break;
		case 5:
			printf("������� ����� ���\n");
			for (int i = 0; i < 100; ++i)
				check[i] = -1;
			break;
		case 6:
			printf("��������� ���������");
			return 0;
			break;
		}
	} while (true);	
}