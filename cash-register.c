#include <stdio.h>
#include <stdbool.h>

// Creating structure for items
struct item {
	int id[4];
    char name[32];
	int price;
	int discount;
    int quantity;
};

// Implementing some basic functions to make main function more readable
void print_item(int item_id, struct item db[]) {
    printf("ID: ");
    for (int j = 0; j < 4; j ++) printf("%d", db[item_id].id[j]);
    printf(" Name: %s; Price: %d; Discount: %d \n", db[item_id].name, db[item_id].price, db[item_id].discount);
}

void enter_item_data(int item_id, struct item db[]) {
    int id_temp;
    printf("Enter new item's data (id, name, price, discount): ");
    scanf("%d%s%d%d", &id_temp, db[item_id].name, &db[item_id].price, &db[item_id].discount);

    for (int j = 3; j >= 0; j--) {
        db[item_id].id[j] = id_temp % 10;
        id_temp /= 10;
    }
}

int main() {
	int mode, new_item_id = 0, item_id = 0, sum = 0;

    struct item db[10];   // For now database is limited
    struct item cart[50]; // Shopping cart (also limited - can use vectors later, to make infinite capacity)
    bool flag  = true;

    for (int i = 0; i < 10; i++) db[i].quantity = 0;

    printf("Admin options: \n 1)Enter new item info \n\nUser options: \n 2)Show detailed info about item \n "
           "3)Enter your items \n 4)Generate receipt \n\n 0)Exit the program \n\n");

    // Infinite while-loop to run the program constantly
    while (true){
        do{
            printf("Mode: ");
            scanf("%d",&mode);
        } while (mode < 0 || mode > 4);


        switch(mode){
            case 0: return 0;
            case 1:
                enter_item_data(new_item_id, db);
                new_item_id++;
                break;
            case 2:
                printf("Enter item's id: ");
                scanf("%d", &item_id);
                //scanner(item_id, db);
                for (int i = 0; i <= 10; i++) {
                    if (i == 10) {
                        printf("Item not found");
                        break;
                    }
                    if (item_id == db[i].id[0] * 1000 + db[i].id[1] * 100 + db[i].id[2] * 10 + db[i].id[3]) {
                        print_item(i,db);
                        break;
                    }
                }
                break;
            case 3:
                printf("Add item to the receipt (Enter item's id): ");
                scanf("%d", &item_id);
                for (int i = 0; i <= 10; i++) {
                    if (i == 10) {
                        printf("Item not found\n\n");
                        break;
                    }
                    if (item_id == db[i].id[0] * 1000 + db[i].id[1] * 100 + db[i].id[2] * 10 + db[i].id[3]) {
                        db[i].quantity++;
                        break;
                    }
                }
                break;
            case 4:
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

	return 0;
}