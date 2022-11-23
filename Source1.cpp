#include <stdio.h>
#include <iomanip>
#include <string.h>

struct shop {
	int code; // штрих-код
	char name[20] = { "NoName" }; // наименование
	int cost; // цена
	int discount; // скидка (в %)
};

struct barcode {
	int code;
	char name[20] = { "NoName" };
	int cost;
	int discount;
	int quantity; // кол-во товара
};

int main() {
	setlocale(0, "");

	int flag = -1, ans_user = -1;
	int total_cost = 0, cost;
	
	barcode arr[5]; // массив для чека
	int p_a = -1; // указатель для arr
	for (int i = 0; i < 5; ++i) {
		arr[i].code = 0;
		arr[i].cost = 0;
		arr[i].discount = -1;
		arr[i].quantity = -1;
	}

	// Создание базы данных и её заполнение:
	shop product[5];
	int p = -1; // указатель для product
	for (int i = 0; i < 5; ++i) {
		product[i].code = 0;
		product[i].cost = 0;
		product[i].discount = -1;
	}

	printf("Операции кассового аппарата: \n"
		"	1. Добавить товар в базу данных (штрих-код товара, наименование, цена, скидка);\n"
		"	2. Вывести описание отсканированного товара;\n" // пользователь вводит штрих-код товара, а программа выводит информацию
		"	3. Добавить данные о товаре в чек;\n" // пользователь вводит штрих-код товара
		"	4. Сформировать чек за покупку, рассчитать итоговую сумму к оплате;\n"
		"	5. Начать формирование нового чека;\n"
		"	6. Завершить программу.\n");

	while (flag != 6) {

		printf("\nВведите операцию:\n");
		scanf_s("%i", &flag);

		switch (flag) {
		case 1:
			if (p != 5) {
			++p;
			printf("Введите штрих-код товара:\n");
			scanf_s("%i", &product[p].code);
			printf("Введите наименование товара (английскими буквами):\n");
			getchar();
			gets_s(product[p].name);
			printf("Введите стоимость товара (в рублях за единицу продукции):\n");
			scanf_s("%i", &product[p].cost);
			// Проверка введённых данных.
			while (!(0 <= product[p].cost)) {
				printf("Повторите попытку.\n");
				scanf_s("%i", &product[p].cost);
			}
			printf("Введите скидку на товар (от 0 до 50 включительно, в процентах):\n");
			scanf_s("%i", &product[p].discount);
			// Проверка введённых данных.
			while (!((0 <= product[p].discount) and (product[p].discount <= 50))) {
				printf("Повторите попытку.\n");
				scanf_s("%i", &product[p].discount);}
			} else {
				printf("База данных переполнена!\n");
			}
			
			break;
		case 2:
			if (p == -1) {
				printf("База данных не заполнена!\n");
			}
			else {
				printf("Введите штрих-код товара:\n");
				scanf_s("%i", &ans_user);
				for (int i = 0; i <= p; ++i) {
					if (product[i].code == ans_user) {
						if (product[i].discount != 0) {
							printf("Найден товар: %s. Цена - %i рублей. Скидка на товар: %i процентов.\n", product[i].name, product[i].cost, product[i].discount);
						}
						else {
							printf("Найден товар: %s. Цена - %i рублей. Скидки на товар нету.\n", product[i].name, product[i].cost);
						}
						flag = -1;
						break;
					}
				}
				if (flag != -1) 
					printf("Товара с таким штрих-кодом нет в базе данных.\n");
			}
			break;
		case 3:
			if (p == -1) {
				printf("База данных не заполнена!\n");
			} else if (p_a == 5) {
				printf("Чек переполнен!\n");
			}
			else {
				printf("Введите штрих-код товара:\n");
				scanf_s("%i", &ans_user);
				// Проверям, есть ли товар с таким штрих-кодом в базе данных?
				for (int i = 0; i <= p; ++i) {
					if (ans_user == product[i].code) {
						flag = 0;
						// Проверям, есть ли товар с таким штрих-кодом в текущем чеке?
						for (int j = 0; j <= p_a; ++j) {
							if (ans_user == arr[j].code) {
								flag = -1;
								printf("Товар %s уже есть в чеке. Текущее кол-во: %i. Вы хотите изменить его кол-во? (да - 1, нет - 0)\n", product[i].name, arr[j].quantity);
								scanf_s("%i", &ans_user);
								if (ans_user == 1) {
									printf("Введите кол-во:\n");
									scanf_s("%i", &ans_user);
									arr[j].quantity = ans_user;
								}
								break;
							}
						}
						// Если товара с таким штрих-кодом нет в текущем чеке
						if (flag != -1) {
							++p_a;
							arr[p_a].code = ans_user;
							printf("Товар: %s. Введите кол-во:\n", product[i].name);
							scanf_s("%i", &ans_user);
							strcpy(arr[p_a].name, product[i].name);
							arr[p_a].cost = product[i].cost;
							arr[p_a].discount = product[i].discount;
							arr[p_a].quantity = ans_user;
							printf("Товар добавлен в чек.\n");
							break;
						} else {
							break;
						}
					} else {
						flag = -2;
					}
				}
				if (flag == -2) printf("Товара с таким штрих-кодом нет в базе данных.\n");
			}
			break;
		case 4:
			if (p == -1) {
				printf("База данных не заполнена!\n");
			} else if (p_a == 0) {
				printf("Чек пустой.\n");
			} else {
				printf("===========================================================================\n");
				for (int i = 0; i <= p_a; ++i) {
					if (arr[i].discount != 0) {
						cost = (arr[i].cost * arr[i].discount / 100) * arr[i].quantity;
					} else {
						cost = arr[i].cost * arr[i].quantity;
					}
					total_cost += cost;
					if (arr[i].discount != 0) {
						printf("%i. %s. Цена за единицу продукцию = %i. Кол-во: %i ед. Скидка за единицу: %i. Сумма: (%i - %i) * %i = %i рублей.\n", i+1, arr[i].name, arr[i].cost, arr[i].quantity, arr[i].discount, arr[i].cost, arr[i].cost * arr[i].discount / 100, arr[i].quantity, cost);
					} else {
						printf("%i. %s. Цена за единицу продукцию = %i. Кол-во: %i ед. Сумма: %i * %i = %i рублей.\n", i + 1, arr[i].name, arr[i].cost, arr[i].quantity, arr[i].cost, arr[i].quantity, cost);
					}
				}
				printf("\nИтого: %i рублей.\n", total_cost);
				total_cost = 0;
				printf("===========================================================================\n");
			}
			break;
		case 5:
			p_a = -1;
			printf("Началось формирование нового чека.\n");
			break;
		}
	}

	return 0;
}