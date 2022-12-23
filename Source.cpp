#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct product
{
    char codes[5];
    char names[64];
    int prices, count, discounts;
};
struct product database[100];
int tab;
int check[100]{ -1 };
int barcode(int n) {
    printf("Entering a 4-character barcode\n");
    char checking[5];
    getchar();
    fgets(checking, 5, stdin);
    for (int i = 0; i < n; ++i) {
        if (!strcmp(checking, database[i].codes)) {
            printf_s("This barcode is already in the system.\nEnter amount: ");
            int amount;
            scanf_s("%i", &amount);
            database[i].count += amount;
            tab = i;
            return n;
        }
    }
    tab = n;
    strcpy_s(database[n].codes, checking);
    printf_s("Enter product details\n");
    printf_s("\nEnter product name: ");
    getchar();
    fgets(database[n].names, 64, stdin);
    printf_s("\nEnter the price of the item: ");
    scanf_s("%i", &database[n].prices);
    printf_s("\nEnter amount: ");
    scanf_s("%i", &database[n].count);
    printf_s("\nEnter a discount for a product: ");
    do {
        scanf_s("%i", &database[n].discounts);
    } while (database[n].discounts > 50 || database[n].discounts < 1);
    return ++n;
}
void info(int n) {
    int price = database[n].prices - (database[n].prices * (float)database[n].discounts / 100);
    int sum = price * database[n].count;
    printf("product name: %s\n", database[n].names);
    printf("price per item: %i\n", database[n].prices);
    printf("amount: %i\n", database[n].count);
    printf("discount: %i %\n", database[n].discounts);
    printf("Outcome: %i %\n", sum);
    return;
}
void check_maker(int pos) {
    int total = 0;
    int price, sum;
    for (int i = 0; i < pos; ++i) {
        int ch = check[i];
        price = database[ch].prices - (database[ch].prices * (float)database[ch].discounts) / 100;
        sum = price * database[ch].count;
        total += sum;
        printf("%s\n", database[ch].names);
        printf("%i pieces. x %i\n", database[ch].count, database[ch].prices);
        printf("total price including discounts: %i\n", sum);
        printf("\n");
    }
    printf("Total: %i\n", total);
    return;
}
int main()
{
    printf_s("Select menu\n");
    printf_s("Press 1 to scan another item\n");
    printf_s("Press 2 to display the description of the scanned item\n");
    printf_s("Press 3 to add product details to the invoice\n");
    printf_s("Press 4 to print receipt\n");
    printf_s("Press 5 to start generating a new receipt\n");
    printf_s("Press 6 to exit the program\n");
    int choice;
    int position = 0, n = 0;
    do {
        printf_s("Select menu mode\n");
        scanf_s("%i", &choice);
        scanf_s("%*[^\n]");
        if (choice <= 0 || choice > 6)
            printf("Wrong mode selected\n");
        switch (choice) {
        case 1:
            n = barcode(n);
            break;
        case 2:
            if (n == 0)
                printf_s("Checks are missing\n");
            else
                info(n - 1);
            break;
        case 3:
            if (n == 0)
                printf_s("Checks are missing\n");
            else if (tab == n - 1) {
                check[position++] = n - 1;
                tab = n;
                printf_s("Info added\n");
            }

            else
                printf("The product is already in the check\n");
            break;
        case 4:
            if (check[0] == -1)
                printf("The check is empty\n");
            else
                check_maker(position);
            break;
        case 5:
            printf("Start a new check\n");
            for (int i = 0; i < 100; ++i)
                check[i] = -1;
            n = 0;
            break;
        case 6:
            printf("Program completed");
            return 0;
            break;
        }
    } while (true);
}