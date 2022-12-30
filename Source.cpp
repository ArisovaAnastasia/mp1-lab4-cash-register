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
	char menu[] = "1.������������ ������\n"
				  "2.�������� ������\n"
				  "3.�������� � ���\n"
			   	  "4.������������ ���\n"
				  "5.����� ���\n"
				  "6.�����\n\n";
	char menuname[] = "��������";
	char menucost[] = "����";
	char menucount[] = "����������";
	char menusumcost[] = "�������� ����";
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
		printf("\n/////////////////////////\n�������� ��������:\n%s", menu);
		printf("��� �����: ");
		scanf_s("%i", &befn);
		printf("/////////////////////////\n");
		printf("\n");
		if (befn != 1 && befn != 2 && befn != 3 && befn != 4 && befn != 5 && befn != 6)
		{
			printf("�������� ����. �������� �������� �� ������.\n");
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
			// ������������� ��������� �����
			number = id - 1;
			++id;
			productmem = (pproduct*)realloc(productmem, id * sizeof(pproduct));
			do
			{
				chflag = false;
				numchflag = false;
				printf("������� �����-��� > ");
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
						printf("�����-��� ��� ���� � ���� ������\n");
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
						printf("�������� �����-���. �����-��� ������ �������� �� 4 ���� � �� ���������� �� 0 �� 9.\n");
					}
				}
			} while (numchflag == true);
			if (chflag == true)
			{
				break;
			}

			printf("������� �������� > ");
			std::cin >> productmem[number].name;
			printf("������� ���� > ");
			scanf_s("%i", &productmem[number].cost);
			productmem[number].count = 1;
			productmem[number].discount = disc;
			break;
		case 2:
			// ������� �������� ���������������� ������
			number = id - 2;
			if (id == 1)
			{
				printf("��� ������\n");
				break;
			}
			printf("�������� ������ �����: %i \n\n", number + 1);
			printf("�����-��� > ");
			for (int i = 0; i < 4; ++i)
			{
				printf("%c", productmem[number].code[i]);
			}
			printf("\n�������� > %s", productmem[number].name);
			printf("\n���� > %i", productmem[number].cost);
			printf("\n���������� > %i", productmem[number].count);
			productmem[number].sumcost = (productmem[number].cost * productmem[number].count) * (100 - productmem[number].discount) / 100;
			printf("\n������ > %i", productmem[number].discount);
			printf("\n��������� ���� > %i\n", productmem[number].sumcost);
			
			break;
		case 3:
			// �������� ������ � ������ � ���
			printf("��������������� ������\n");
			for (int i = 0; i < id - 1; i++)
			{
				printf("\n�  �����-���\n");
				printf("%i  ", i + 1);
				for (int j = 0; j < 4; ++j)
				{
					printf("%c", productmem[i].code[j]);
				}
				printf("\n   ��������\n");
				printf("   %s\n", productmem[i].name);
				printf("   ����\n");
				printf("   %i\n", productmem[i].cost);
				printf("   ����������\n");
				printf("   %i\n", productmem[i].count);
				printf("   ������\n");
				printf("   %i\n", productmem[i].discount);
				productmem[i].sumcost = (productmem[i].cost * productmem[i].count) * (100 - productmem[i].discount) / 100;
				printf("   ��������� ����\n");
				printf("   %i\n", productmem[i].sumcost);
			}
			
			do
			{
				++No;
				check = (pproduct*)realloc(check, No * sizeof(pproduct));

				printf("\n���� ������ �������� ����� � ���, ������� ����� ������. ��� ������ ������� 0 > ");
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
				printf("������� ���������� > ");
				scanf_s("%i", &check[input - 1].count);
				check[input - 1].discount = productmem[input - 1].discount;
				check[input - 1].sumcost = productmem[input - 1].sumcost * check[input - 1].count;
			} while (1);
			break;
		case 4:
			// ������������ ��� �� �������, ���������� �������� ����� � ������
			printf("���\n");
			for (int i = 0; i < No - 2; i++)
			{
				printf("\n� /�����-���\n");
				printf("%i  ", i + 1);
				for (int j = 0; j < 4; ++j)
				{
					printf("%c", check[i].code[j]);
				}
				printf("\n  /��������\n");
				printf("   %s\n", check[i].name);
				printf("  /����\n");
				printf("   %i\n", check[i].cost);
				printf("  /����������\n");
				printf("   %i\n", check[i].count);
				printf("  /������\n");
				printf("   %i\n", check[i].discount);
				printf("  /��������� ����\n");
				printf("   %i\n", check[i].sumcost);
			}
			finsum = 0;
			for (int i = 0; i < No - 2; ++i)
			{
				finsum += check[i].sumcost;
			}
			printf("\n�������� ����: %i\n", finsum);
			break;
		case 5:
			// ������ ������������ ������ ����
			No = 1;
			free(check);
			check = NULL;
			printf("����� ��� �����������\n");
			break;
		}
	}

	free(productmem);
	free(check);
	printf("\n��������� ���������\n");
	return 0;
}

/*��������� ������ ����������� ������ ��������� �������� �� ������������ ������� � ������������ ���� 
�� �������.������ ����� ���������������� ����� - �����.����� - ��� �������� � ���� ������� �� ������� 
��������.������ ������ ��������� �������� �� �0� �� �9�.���� � ��� �� ����� ����� ������������� ��������� 
���, �� � ��� ���������� � ������ ������ ������ � ���� :
������������� � ��������� �� �������(��� ��������� � ������ ��� ������) � ���������� � 
����� ��������� �� �����.

��� ������� �� ����� ��� �� ����� ������ ���������� ����.��� ������������� �������� ����� ��������� 
������� � �������, ��������� ������ � �������� ����� � ������(��� � ������).
������ ����� ����������� ����� - �����, �������������, ���������� �� ������� ������, 
������� � ��������� �� ���������.������ ��������������� �� ������ ����� ����������(� ��������� �� 1 �� 50 %). (������� �������������)

��������� ������ ������������� ��������� �������� :

1.������������� ��������� ����� :
	+++1)���� ����� - ����+++
	2)���� ���������� � ������(���� ����� ����� - ��� ��� ����, ��������� � ����� ����������)
	+++3)���� ���������� ������+++
2.+++������� �������� ���������������� ������,+++
3.�������� ������ � ������ � ���,
4.������������ ��� �� �������, ���������� �������� ����� � ������,
+++5.������ ������������ ������ ����,+++
6.��������� ���������
*/
