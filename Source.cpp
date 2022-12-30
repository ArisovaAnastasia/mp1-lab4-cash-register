#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <random>
#include <time.h>

int main()
{
	setlocale(LC_ALL, "rus");

	srand(time(NULL));

	bool numchflag, chflag, nflag;
	char menu[] = "1.Сканирование товара\n"
				  "2.Описание товара\n"
				  "3.Добавить в чек\n"
			   	  "4.Сформировать чек\n"
				  "5.Новый чек\n"
				  "6.Выйти\n\n";
	char menuname[] = "Название";
	char menucost[] = "Цена";
	char menucount[] = "Количество";
	char menusumcost[] = "Итоговая цена";
	typedef struct product
	{
		char code[4];
		char name[50];
		int cost;
		int count;
		int discount;
		int sumcost;
	}pproduct;
	int id = 1;
	int number, finsum, disc, input;
	pproduct* productmem = (pproduct*)malloc(id * (sizeof(pproduct)));
	int No = 1;
	pproduct* check = (pproduct*)malloc(No * (sizeof(pproduct)));

	
	int n = 0;
	int befn = 0;
	while (n != 6)
	{
		disc = rand() % 50 + 1;
		nflag = false;
		printf("\n/////////////////////////\nВыберите операцию:\n%s", menu);
		printf("Ваш выбор: ");
		scanf_s("%i", &befn);
		printf("/////////////////////////\n");
		printf("\n");
		if (befn != 1 && befn != 2 && befn != 3 && befn != 4 && befn != 5 && befn != 6)
		{
			printf("Неверный ввод. Выберите операцию из списка.\n");
			n = 0;
			befn = 0;
		}
		else
		{
			n = befn;
		}

		switch (n)
		{
		case 1:
			// «сканировать» очередной товар
			number = id - 1;
			++id;
			productmem = (pproduct*)realloc(productmem, id * sizeof(pproduct));
			do
			{
				chflag = false;
				numchflag = false;
				printf("Введите штрих-код > ");
				for (int i = -1; i < 4; ++i)
				{
					scanf_s("%c", &productmem[number].code[i], 2);
				}

				for (int i = 0; i < number; ++i)
				{
					if (productmem[i].code[0] == productmem[number].code[0] &&
						productmem[i].code[1] == productmem[number].code[1] &&
						productmem[i].code[2] == productmem[number].code[2] &&
						productmem[i].code[3] == productmem[number].code[3])
					{
						printf("Штрих-код уже есть в базе данных\n");
						chflag = true;
						id -= 1;
						break;
					}
				}
				if (chflag == false)
				{
					for (int i = 0; i < 4; ++i)
					{
						if (productmem[number].code[i] != '1' &&
							productmem[number].code[i] != '2' &&
							productmem[number].code[i] != '3' &&
							productmem[number].code[i] != '4' &&
							productmem[number].code[i] != '5' &&
							productmem[number].code[i] != '6' &&
							productmem[number].code[i] != '7' &&
							productmem[number].code[i] != '8' &&
							productmem[number].code[i] != '9' &&
							productmem[number].code[i] != '0')
						{
							numchflag = true;
						}
					}
					if (numchflag == true)
					{
						printf("Неверный штрих-код. Штрих-код должен состоять из 4 цифр и со значениями от 0 до 9.\n");
					}
				}
			} while (numchflag == true);
			if (chflag == true)
			{
				break;
			}

			printf("Введите название > ");
			std::cin >> productmem[number].name;
			printf("Введите цену > ");
			scanf_s("%i", &productmem[number].cost);
			productmem[number].count = 1;
			productmem[number].discount = disc;
			break;
		case 2:
			// вывести описание отсканированного товара
			number = id - 2;
			if (id == 1)
			{
				printf("Нет товара\n");
				break;
			}
			printf("Описание товара номер: %i \n\n", number + 1);
			printf("Штрих-код > ");
			for (int i = 0; i < 4; ++i)
			{
				printf("%c", productmem[number].code[i]);
			}
			printf("\nНазвание > %s", productmem[number].name);
			printf("\nЦена > %i", productmem[number].cost);
			printf("\nКоличество > %i", productmem[number].count);
			productmem[number].sumcost = (productmem[number].cost * productmem[number].count) * (100 - productmem[number].discount) / 100;
			printf("\nСкидка > %i", productmem[number].discount);
			printf("\nСуммарная цена > %i\n", productmem[number].sumcost);
			
			break;
		case 3:
			// добавить данные о товаре в чек
			printf("Отсканированные товары\n");
			for (int i = 0; i < id - 1; i++)
			{
				printf("\n№  Штрих-код\n");
				printf("%i  ", i + 1);
				for (int j = 0; j < 4; ++j)
				{
					printf("%c", productmem[i].code[j]);
				}
				printf("\n   Название\n");
				printf("   %s\n", productmem[i].name);
				printf("   Цена\n");
				printf("   %i\n", productmem[i].cost);
				printf("   Количество\n");
				printf("   %i\n", productmem[i].count);
				printf("   Скидка\n");
				printf("   %i\n", productmem[i].discount);
				productmem[i].sumcost = (productmem[i].cost * productmem[i].count) * (100 - productmem[i].discount) / 100;
				printf("   Суммарная цена\n");
				printf("   %i\n", productmem[i].sumcost);
			}
			
			do
			{
				++No;
				check = (pproduct*)realloc(check, No * sizeof(pproduct));

				printf("\nЕсли хотите добавить товар в чек, введите номер товара. Для выхода нажмите 0 > ");
				scanf_s("%i", &input);
				if (input == 0)
				{
					break;
				}

				for (int j = 0; j < 4; ++j)
				{
					check[input - 1].code[j] = productmem[input - 1].code[j];
				}

				for (int j = 0; j < 50; ++j)
				{
					check[input - 1].name[j] = productmem[input - 1].name[j];
				}
				check[input - 1].cost = productmem[input - 1].cost;
				printf("Введите количество > ");
				scanf_s("%i", &check[input - 1].count);
				check[input - 1].discount = productmem[input - 1].discount;
				check[input - 1].sumcost = productmem[input - 1].sumcost * check[input - 1].count;
			} while (1);
			break;
		case 4:
			// сформировать чек за покупку, рассчитать итоговую сумму к оплате
			printf("Чек\n");
			for (int i = 0; i < No - 2; i++)
			{
				printf("\n№ /Штрих-код\n");
				printf("%i  ", i + 1);
				for (int j = 0; j < 4; ++j)
				{
					printf("%c", check[i].code[j]);
				}
				printf("\n  /Название\n");
				printf("   %s\n", check[i].name);
				printf("  /Цена\n");
				printf("   %i\n", check[i].cost);
				printf("  /Количество\n");
				printf("   %i\n", check[i].count);
				printf("  /Скидка\n");
				printf("   %i\n", check[i].discount);
				printf("  /Суммарная цена\n");
				printf("   %i\n", check[i].sumcost);
			}
			finsum = 0;
			for (int i = 0; i < No - 2; ++i)
			{
				finsum += check[i].sumcost;
			}
			printf("\nИтоговая цена: %i\n", finsum);
			break;
		case 5:
			// начать формирование нового чека
			No = 1;
			free(check);
			check = NULL;
			printf("Новый чек сформирован\n");
			break;
		}
	}

	free(productmem);
	free(check);
	printf("\nПрограмма завершена\n");
	return 0;
}

/*Программа должна имитировать работу кассового аппарата по сканированию товаров и формированию чека 
за покупку.Каждый товар идентифицируется штрих - кодом.Штрих - код хранится в виде массива из четырех 
символов.Каждый символ принимает значение от ‘0’ до ‘9’.Один и тот же товар может сканироваться несколько 
раз, но в чек информация о каждом товаре входит в виде :
«наименование – стоимость за единицу(для упрощения в рублях без копеек) – количество – 
общая стоимость за товар».

Чек состоит не менее чем из одной записи указанного вида.Чек дополнительно включает общую стоимость 
товаров в покупке, суммарную скидку и итоговую сумму к оплате(все в рублях).
Каждый товар описывается штрих - кодом, наименованием, стоимостью за единицу товара, 
скидкой в процентах от стоимости.Скидки устанавливаются на каждый товар независимо(в диапазоне от 1 до 50 %). (Копейки отбрасываются)

Программа должна предоставлять следующие операции :

1.«сканировать» очередной товар :
	+++1)Ввод штрих - кода+++
	2)Ввод информации о товаре(если такой штрих - код уже есть, переходим к вводу количества)
	+++3)Ввод количества товара+++
2.+++вывести описание отсканированного товара,+++
3.добавить данные о товаре в чек,
4.сформировать чек за покупку, рассчитать итоговую сумму к оплате,
+++5.начать формирование нового чека,+++
6.завершить программу
*/
