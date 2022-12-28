#include <stdio.h>
#include <string.h>

// Creating structure for items
struct item {
	char id[5];
    char name[32];
	int price;
	int discount;
    int quantity;
};

// Implementing some basic functions to make main function more readable
void print_item(int item_id, struct item db[]) {
    printf("ID: %s Name: %s; Price: %d; Discount: %d \n", db[item_id].id, db[item_id].name, db[item_id].price, db[item_id].discount);
}

int enter_item_data(int item_id, struct item db[]) {
    printf("Enter new item's data (id, name, price, discount): ");
    scanf("%s", db[item_id].id);
    if (strcmp(db[item_id].id, "0") == 0) return 0;
    scanf("%s%d%d", db[item_id].name, &db[item_id].price, &db[item_id].discount);
    return 1;
}

int main() {
	int mode, sum, new_item_id = 0;
    char item_id[5];

    struct item db[10];   // For now database is limited

    for (int i = 0; i < 10; i++) db[i].quantity = 0;

    printf("Admin options: \n 1)Enter new item info \n\nUser options: \n 2)Show detailed info about item \n "
           "3)Enter your items \n 4)Generate receipt \n\n 0)Exit the program \n\n");

    // Infinite while-loop to run the program constantly
    while (1){
        do{
            printf("Mode: ");
            scanf("%d",&mode);
        } while (mode < 0 || mode > 4);


        switch(mode){
            case 0: return 0;
            case 1:
                printf("Type 0 to quit\n\n");
                while (1) {
                    if (enter_item_data(new_item_id, db) != 0) new_item_id++;
                    else break;
                }
                break;
            case 2:
                printf("Enter item's id: ");
                scanf("%s",item_id);
                //scanner(item_id, db);
                for (int i = 0; i <= 10; i++) {
                    if (i == 10) {
                        printf("Item not found");
                        break;
                    }
                    if (strcmp(item_id, db[i].id) == 0) {
                        print_item(i,db);
                        break;
                    }
                }
                break;
            case 3:
                printf("Type 0 to quit\n\n");
                while(1) {
                    printf("Add item to the receipt (Enter item's id): ");
                    scanf("%s",item_id);
                    if (strcmp(item_id, "0") == 0) break;
                    for (int i = 0; i <= 10; i++) {
                        if (i == 10) {
                            printf("Item not found\n\n");
                            break;
                        }
                        if (strcmp(item_id, db[i].id) == 0) {
                            db[i].quantity++;
                            break;
                        }
                    }
                }
                break;
            case 4:
                sum = 0;
                printf("Generating receipt............\n");
                for (int i = 0; i < 10; i++) {
                    if (db[i].quantity != 0) {
                        printf("Name: %s; Price: %d; Price (with discount): %d; Quantity: %d\n", db[i].name, db[i].price,
                               db[i].price - db[i].price * db[i].discount / 100, db[i].quantity);
                        sum = sum + (db[i].price - db[i].price * db[i].discount / 100) * db[i].quantity;
                    }
                }
                printf("\n\nTotal price: %d Rubles\n\n", sum);
                break;
            default:
                printf("No mode selected:\n");
                break;
        }
    }
}