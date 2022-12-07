#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>


struct Product_database
{
    char name[128];
    char barcode[5];
    int discount;
    int price;
};

struct Product_receipt
{
    int id_database;
    int count;
};

int main(){
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int id_menu, count_receipt = 0, count_database = 0, true = 1;
    int id_database = -1;
    struct Product_database Database[100];
    struct Product_receipt Receipt[50];

    while(true){
        printf("\n"
               "1. «Сканировать» очередной товар\n"
               "2. Вывести описание отсканированного товара\n"
               "3. Добавить данные о товаре в чек\n"
               "4. Формировать чек за покупку, рассчитать итоговую сумму к оплате\n"
               "5. Начать формирование нового чека\n"
               "6. Завершить программу\n");
        scanf("%i", &id_menu);

        switch (id_menu) {
            case 1:{
                char barcode[5] = "";
                printf("\nВведите штрих код: ");
                getchar();
                fgets(barcode, 5, stdin);
                id_database = -1;
                for(int i = 0; i < count_database; ++i){
                    if(strcmp(Database[i].barcode, barcode) == 0){
                        id_database = i;
                        break;
                    }
                }
                if(id_database == -1){
                    strcpy(Database[count_database].barcode, barcode);
                    printf("Введите наименование товара: ");
                    getchar();
                    fgets(Database[count_database].name, 128, stdin);
                    Database[count_database].discount = 1 + rand() % (50);
                    Database[count_database].price = (4 + rand() % (6))*10;
                    Receipt[count_receipt].id_database = count_database;
                    printf("Введите количество товара: ");
                    scanf("%i", &Receipt[count_receipt].count);
                    ++count_database;
                    ++count_receipt;
                }
                else{

                    for(int i = 0; i < count_receipt; ++i) {
                        if(id_database == Receipt[i].id_database) {
                            ++Receipt[i].count;
                            break;
                        }
                        if(count_receipt-1 == i){
                            Receipt[count_receipt].count = 1;
                            Receipt[count_receipt].id_database = id_database;
                            ++count_receipt;
                            break;
                        }
                    }
                }
                break;
            }
            case 2:{
                if(count_receipt == 0)
                    printf("Товар не был отсканирован\n");
                else if(id_database == -1) {
                    printf("\nНазвание: %s", Database[Receipt[count_receipt - 1].id_database].name);
                    printf("Штрихкод: ");
                    puts(Database[Receipt[count_receipt-1].id_database].barcode);
                    printf("Скидка: %i процентов\n", Database[Receipt[count_receipt-1].id_database].discount);
                    printf("Цена: %i рублей\n", Database[Receipt[count_receipt - 1].id_database].price);
                } else {
                    printf("Название: %s", Database[id_database].name);
                    printf("Штрихкод: %s \n", Database[id_database].barcode);
                    printf("Скидка: %i процентов\n", Database[id_database].discount);
                    printf("Цена: %i рублей\n", Database[id_database].price);
                }
                break;
            }
            case 3:{
                char barcode[5] = "";
                printf("\nВведите штрих код: ");
                getchar();
                fgets(barcode, 5, stdin);
                for(int i = 0; i < count_database; ++i){
                    if(strcmp(Database[i].barcode, barcode) == 0){
                        id_database = i;
                        break;
                    }
                }
                for(int i = 0; i < count_receipt; ++i) {
                    if(id_database == Receipt[i].id_database) {
                        printf("Введите количество товара: ");
                        int num;
                        scanf("%i", &num);
                        Receipt[i].count +=num;
                        break;
                    }
                }
                break;
            }
            case 4: {
                int total_sum = 0;
                int sum;
                for (int i = 0; i < count_receipt; ++i){
                    if (Receipt[i].count != 0) {
                        printf("\nНазвание: %s", Database[Receipt[i].id_database].name);
                        printf("Штрихкод: %s \n", Database[Receipt[i].id_database].barcode);
                        printf("Количество товара: %i\n", Receipt[i].count);
                        printf("Цена: %i рублей\n", Database[Receipt[i].id_database].price);
                        printf("Скидка: %i процентов\n", Database[Receipt[i].id_database].discount);
                        sum = Receipt[i].count * Database[Receipt[i].id_database].price *
                              (100 - Database[Receipt[i].id_database].discount) / 100;
                        printf("Сумма: %i рублей\n", sum);
                        total_sum += sum;
                    }
                }
                printf("\nОбщая сумма: %i рублей\n", total_sum);
                break;
            }
            case 5:{
                for(int i = 0; i<count_receipt; ++i) {
                    Receipt[i].count = 0;
                    Receipt[i].id_database = 0;
                }
                count_receipt = 0;
                break;
            }
            case 6: {
                true = 0;
                break;
            }
        }
    }
}