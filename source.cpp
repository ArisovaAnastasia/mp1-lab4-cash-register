
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>


struct Stuff
{
    char name[128];
    int cost;
    float discont;
    int count;
};

Stuff database[10000];
int used[10000] = { (0) };

int main()
{
   
    
    while (true)
    {
        printf("Menu\n 1.Scan staff(Add staff in check)\n 2.Show Description\n 3.Form Check\n 4.New check\n 5.Exit program \n");
        int choice;
        do
        {
            scanf("%i", &choice);
        } while (choice > 5 || choice < 1);


        int code;
        char s[4];
        int sum, sum_w_dis;
        switch (choice) {
        case 1:
            do {
                printf("Enter correct code:");

                scanf("%s", &s);
                code = (s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + (s[3] - '0');

            } while (code >= 10000 || code < 0);

            if (!used[code]) {
                printf("Oh,is a new one, enter info\n");
                printf("Enter Name:");
                scanf("%s", &database[code].name);
                printf("\n");

                do {
                    printf("Enter cost:");
                    scanf("%i", &database[code].cost);
                    printf("\n");
                } while (database[code].cost < 0);

                do {
                    printf("Enter discont:");
                    scanf("%f", &database[code].discont);
                    printf("\n");
                } while (database[code].discont < 0 || database[code].discont > 0.5);

                do {
                    printf("Enter count:");
                    scanf("%i", &database[code].count);
                    printf("\n");
                } while (database[code].count < 0);
                used[code] = 1;
            }
            else {
                int c = 0;
                do {
                    printf("Enter count:");
                    scanf("%i", &c);
                    printf("\n");
                } while (c < 0);
                database[code].count += c;
            }
            break;
        case 2:
            do {
                printf("Enter correct code:");

                scanf("%s", &s);
                code = (s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + (s[3] - '0');

            } while (code >= 10000 || code < 0);
            if (!used[code])
            {
                printf("I dont even know these stuff!\n");
            }
            else
            {
                printf("Name:%s\n Cost:%i\n Discont:%f\n", database[code].name, database[code].cost, database[code].discont);
            }
            break;
        case 3:
            sum = 0;
            sum_w_dis = 0;
            printf("This is your check:");
            for (int i = 0; i < 10000; ++i) {
                if (used[i] && database[i].count != 0) {
                    Stuff curstuff = database[i];
                    sum += curstuff.count * curstuff.cost;
                    sum_w_dis += curstuff.count * int(curstuff.cost * (1 - curstuff.discont));
                    printf("Code:%i%i%i%i Name:%s\n Cost:%i\n Count:%i\n Summary:%i\n", i / 1000, (i / 100) % 10,
                        (i / 10) % 10, i % 10, curstuff.name, curstuff.cost, curstuff.count,
                        int(curstuff.cost * (1 - curstuff.discont)) * curstuff.count);
                }
            }
            printf("Sum:%i\n", sum);
            printf("Dicsount Sum:%i\n", sum - sum_w_dis);
            printf("Need to pay:%i\n", sum_w_dis);
            break;
        case 4:
            for (int i = 0; i < 10000; ++i)
            {
                if (used[i])
                {
                    database[i].count = 0;
                }
            }
            break;
        case 5:
            return 0;
        }
    }

}
