#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<stdlib.h>


int Enter;//переменная для работы с повторными чеками 
int prices[100]{}, count[100]{}, discounts[100]; //массивы цен за еденицу товара, штрих-кодов,количества товаров и скидок
int check[100]{-1}; // товары в чеке
char codes[100][5]; // штрих-коды
char names[100][64]; // наименования товаров

//Вводите названия товаров латиницей

int barcode(int n) {
	printf("Введите штрих-код из 4 символов от 0 до 9\n");
	char checking[5];
	getchar();
	fgets(checking, 5, stdin);//fflush не работает после scanf
	for (int i = 0; i < n; ++i) {
		if (!strcmp(checking, codes[i])){
			printf_s("Этот штрих код уже есть в системе.\nВведите количество товара: ");
			int buf; // количество товара 
			scanf_s("%i", &buf);
			count[i] += buf;
			Enter = i;
			return n;
		}
	}
	Enter = n;
	strcpy_s(codes[n], checking);
	printf_s("Введите данные о товаре\n");	
	printf_s("\nВведите наименование товара: ");
	getchar();
	fgets(names[n], 64 ,stdin);
	printf_s("\nВведите цену товара: ");
	scanf_s("%i", &prices[n]);
	printf_s("\nВведите количество товара: ");
	scanf_s("%i", &count[n]);
	printf_s("\nВведите скидку на товар: ");
	do {
		scanf_s("%i", &discounts[n]);
	} while (discounts[n] > 50 || discounts[n] < 1);
	return ++n;
}

void info(int n) {
	int price = prices[n] - (prices[n] * (float)discounts[n]/100);
	int sum = price * count[n];
	printf("наименонование товара: %s\n", names[n]);
	printf("цена за еденицу товара: %i\n", prices[n]);
	printf("количество: %i\n", count[n]);
	printf("Скидка: %i %\n", discounts[n]);
	printf("Итог: %i %\n", sum);
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
		printf("%i шт. x %i\n", count[ch], prices[ch]);
		printf("общая стоимость с учётом скидок: %i\n", sum);
		printf("\n");
	}
	printf("Итого: %i\n", total);
	return;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	printf_s("Выберите операцию\n");
	printf_s("Нажмите 1, чтобы сканировать товар\n");
	printf_s("Нажмите 2, чтобы вывести описание отсканированного товара\n");
	printf_s("Нажмите 3, добавить данные о товаре в чек\n");
	printf_s("Нажмите 4, чтобы сформировать чек за покупку, рассчитать итоговую сумму к оплате\n");
	printf_s("Нажмите 5, чтобы начать формирование нового чека\n");
	printf_s("Нажмите 6, чтобы завершить программу\n");
	int operation;
	int pos = 0, n = 0; //счётчик для чека и количество штрих-кодов в базе
	do{
		printf_s("Выберите новую операцию\n");
		scanf_s("%i", &operation);
		scanf_s("%*[^\n]");
		if (operation <= 0 || operation > 6)
			printf("Некорректный номер операции\n");
		switch (operation) {
		case 1:
			n = barcode(n);
			break;
		case 2:
			if (n == 0)
				printf_s("Вы не отсканировали ни одного чека\n");
			else if(Enter==n-1) {
				info(n-1);
			}
			else {
				info(Enter);
			}
			break;
		case 3:
			if (n == 0)
				printf_s("Вы не отсканировали ни одного чека\n");
			else if (Enter == n - 1)
				check[pos++] = n - 1;
			else 
				printf("Товар уже есть в чеке\n");
			break;
		case 4:
			if (check[0] == -1)
				printf("Чек пустой\n");
			else
				checkMaker(pos);
			break;
		case 5:
			printf("Начните новый чек\n");
			for (int i = 0; i < 100; ++i)
				check[i] = -1;
			break;
		case 6:
			printf("Программа завершена");
			return 0;
			break;
		}
	} while (true);	
}