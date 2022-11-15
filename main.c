#include <stdio.h>
#include <stdlib.h>
struct product
        {
               int code;
               int price;
               int discount;
               int amount;
               char name[64];
        };
struct product database[1000];
int id,receipt_id,sum;
int recp_id[100]={0};
int new_product_number=1000;
void scanproduct_id() {
    printf("Write down product id\n");
    int tempid;
    while (1) {
        scanf("%i", &tempid);
        if (tempid < 10000 && tempid > 999 && tempid / 1000 != 0) {
            id = tempid;
            break;
        }
        else { printf("Rewrite the id, please"); }
    }
}
void scanproduct_info()
{
    printf("This is a new product,please write down following information about it#\n ");
    printf("It`s price\n ");
    printf("It`s amount\n ");
    printf("If there`s a discount write it down in percents ,write 0 otherwise\n ");
    scanf("%d %d %d", &database[new_product_number].price,&database[new_product_number].amount, &database[new_product_number].discount);
    getchar();
    printf("It`s Name\n ");
    scanf("%s",&database[new_product_number].name);
    getchar();
}
int main() {
    printf("Welcome, please enter the number of mod you want to use:\n");
    printf("Mode 1:Scan product you`ve chose\n");
    printf("Mode 2:Get info on any product\n");
    printf("Mode 3:Add product to the receipt\n");
    printf("Mode 4:Form final receipt and get final price\n");
    printf("Mode 5:Clean last receipt and get ready for a new one \n");
    printf("Mode 6:End program work \n");
    while (1) {
        int mode;
        printf("Welcome, please enter the number of mod you want to use:\n");
        scanf("%i", &mode);
        switch (mode) {
            case 6:
                _Exit(0);
            case 1:
                scanproduct_id();
                int flag;
                for (int i = 0; i < 1000; ++i) {
                    if (database[i].code == id) {
                        printf("This product already exists in database, so please write down amount of products you want to buy\n");
                        int new_amount;
                        scanf("%i",&new_amount);
                        database[i].amount=new_amount;
                        flag++;
                        break;
                    }

                }
                if (flag == 0) {
                    scanproduct_info();
                    new_product_number++;
                }
                break;
            case 2:
                printf("Please enter id of the product you want to get info about\n ");
                scanproduct_id();
                printf("Here`s info about product\n");
                printf("Price:");
                printf("%i",database[id].price);
                printf("Amount:");
                printf("%i",database[id].amount);
                printf("Discount:");
                printf("%i",database[id].discount);
                printf("Name:");
                printf("%s",database[id].name);
                break;
            case 3:
                scanproduct_id();
                recp_id[receipt_id]=id;
                receipt_id++;
                printf("You`ve added a new product to the receipt!\n");
                break;
            case 4:
                printf("Let`s sum up!\n");
                sum=0;
                for(int i=0;i<100;++i)
                {
                    sum+=database[recp_id[i]].price*database[recp_id[i]].amount-(database[recp_id[i]].price*database[recp_id[i]].amount*(database[recp_id[i]].discount/100));
                }
                printf("Total sum is:");
                printf("%i",sum);
                break;
            case 5:
                printf("Let`s clean last receipt!\n");
                for(int i=0;i<100;++i)
                {
                    recp_id[i]=0;
                }
                printf("You`re ready for a new receipt!\n");
                break;
        }

    }
}
