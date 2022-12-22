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
struct product base[100]{0};
int t;
int check[100]{ 0 };

void info(int l) {
	int price = base[l].price - (base[l].price * (float)base[l].discount / 100);
	int sum = price * base[l].count;
	printf("Название: %s\n", base[l].name);
	printf("Цена %i\n", base[l].price);
	printf("Количество: %i\n", base[l].count);
	printf("Скидка: %i %\n", base[l].discount);
	printf("Итог: %i %\n", sum);
	return;
}
int code(int l) {
	printf("Введите штрих-код(4 символа)\n");
	char checking[5];
	getchar();
	fgets(checking, 5, stdin);
	for (int i = 0; i < l; ++i) {
		if (!strcmp(checking, base[i].code)) {
			printf_s("Этот товар уже существует в базе .\nВведите количество ");
			int amount;
			scanf_s("%i", &amount);
			base[i].count += amount;
			t = i;
			return l;
		}
	}
	t = l;
	strcpy_s(base[l].code, checking);
	printf_s("Введите информацию о продукте\n");
	printf_s("Имя: ");
	getchar();
	fgets(base[l].name, 64, stdin);
	printf_s("\nЦена: ");
	scanf_s("%i", &base[l].price);
	printf_s("\nКоличество: ");
	scanf_s("%i", &base[l].count);
	printf_s("\nСкидка: ");
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
		price = base[i].price - (base[i].price * (float)base[i].discount) / 100;
		sum = price * base[i].count;
		t += sum;
		printf("Название %s\n", base[j].name);
		printf("||Kоличество %i||\n ||Цена %i||\n", base[j].count, base[j].price);
		//printf("Общая сумма без скидки: %i\n", sum);
		printf("\n");
		base[i].count = 0;
		strcpy_s(base[i].name, "");
		base[i].price = 0;
		break;
	}
	printf("Общая сумма: %i\n", t);
	return;
}
int main() {
	setlocale(LC_ALL, "rus");
	printf_s("Выберите меню\n");
	printf_s("1 «сканировать» очередной товар\n");
	printf_s("2 вывести описание отсканированного товара,\n");
	printf_s("3 добавить данные о товаре в чек,\n");
	printf_s("4 сформировать чек за покупку, рассчитать итоговую сумму к оплате,\n");
	printf_s("5 начать формирование нового чека,\n");
	printf_s("6 завершить программу.\n");
	int key;
	int p = 0;
	int l = 0;
	do {
		printf_s("\n");
		scanf_s("%i", &key);
		if (key <= 0 || key > 6)
			printf("Введите номер меню\n");
		switch (key) {
		case 1:
			l = code(l);
			break;
		case 2:
			if (l == 0)
				printf_s("Чек пустой:");
			else
				info(l - 1);
			break;
		case 3:
			if (l == 0)
				printf_s("Чек пустой:\n");
			else if (t == l - 1) {
				check[p++] = l - 1;
				t = l;
			}

			else
				printf("Этот продук есть уже в чеке\n");
			break;
		case 4:
			printf("Вы выбрали сформировать чек за покупку\n");
			
			if (check[0] == -1);
			else {
				check_pr(p);
				t = 0;
			}
			break;
		case 5:
			printf("Вы выбрали сформировать новый чек ");
			for (int i = 0; i < 100; ++i) {
				check[i] = 0;
				l = 0;
			}
			break;
		case 6:
			printf("Вы выбрали завершить программу ");
			return 0;
			break;
		}
	} while (true);
}