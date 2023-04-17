#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_revenue 100

struct revenue {
    int serial_no;
    int income; // Changed to single variable
    int expense; // Changed to single variable
    int profit; // Changed to single variable
    char reason[50]; // Changed to an array of characters to hold a string
};

struct revenue revenue[MAX_revenue];
int num_revenue = 0;

void load_revenue() {
    FILE *fp;
    fp = fopen("revenue.txt", "r");
    if (fp == NULL) {
        return;
    }

    while ((fscanf(fp, "%d,%d,%d,%d,%[^,]\n", &revenue[num_revenue].serial_no, &revenue[num_revenue].income, &revenue[num_revenue].expense, &revenue[num_revenue].profit, revenue[num_revenue].reason)) == 5) {
        printf("serial no %d\n", revenue[num_revenue].serial_no);
        num_revenue++;
    }

    fclose(fp);
}

void save_revenue() {
    FILE *fp;
    fp = fopen("revenue.txt", "w");
    for (int i = 0; i < num_revenue; i++) {
        fprintf(fp, "%d,%d,%d,%d,%s\n", revenue[i].serial_no, revenue[i].income, revenue[i].expense, revenue[i].profit, revenue[i].reason); // Removed the extra comma
    }
    fclose(fp);
}

void add_revenue() {
  if (num_revenue >= MAX_revenue) {
    printf("Sorry, the database is full.\n");
    return;
  }
  
  struct revenue obj1;
  printf("Is it an income or an expense? (1 for income, 2 for expense)\n");
  int option;
  scanf("%d", &option);
  
  switch(option){
    case 1:
      printf("Enter Serial No:\n");
      scanf("%d", &obj1.serial_no);
      printf("Enter income:\n");
      scanf("%d", &obj1.income);
      printf("Enter from where did we get this money:\n");
      scanf("%s", obj1.reason);
      obj1.expense = 0;
      break;
    case 2:
      printf("Enter Serial No:\n");
      scanf("%d", &obj1.serial_no);
      printf("Enter expense:\n");
      scanf("%d", &obj1.expense);
      printf("Enter reason for this expense:\n");
      scanf("%s", obj1.reason);
      obj1.income = 0;
      break;
    default:
      printf("Invalid option.\n");
      return;
  }
  
  revenue[num_revenue] = obj1;
  num_revenue++;
  printf("revenue information added successfully.\n");
  save_revenue();
}
void delete_revenue() {
    int id;
    printf("Enter revenue serial no to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < num_revenue; i++) {
        if (revenue[i].serial_no == id) {
            for (int j = i; j < num_revenue - 1; j++) {
                revenue[j] = revenue[j + 1];
            }
            num_revenue--;
            save_revenue();
            printf("revenue deleted.\n");
            return;
        }
    }
    printf("No revenue found with ID %d.\n", id);
}

void modify_revenue() {
    int id;
    printf("Enter revenue serial no to modify: ");
    scanf("%d", &id);

    for (int i = 0; i < num_revenue; i++) {
        if (revenue[i].serial_no == id) {
            printf("Which field do you want to modify?\n");
            printf("\n1. serial no \n2. income \n3. expenses \n4. reason\n");
            int option;
            scanf("%d", &option);

            switch (option) {
                case 1:
                    printf("Enter new serial_no ");
                    scanf("%d", &revenue[i].serial_no);
                    break;
                case 2:
                    printf("Enter new income: ");
                    scanf("%d", &revenue[i].income); // Removed the extra semicolon
                    break;
                case 3:
                    printf("Enter new expense: ");
                    scanf("%d", &revenue[i].expense);
                    break;
                case 4:
                    printf("Enter new reason: ");
                    scanf("%s", revenue[i].reason);
                    break;
                default:
                    printf("Invalid option selected.\n");
                    break;
            }

            save_revenue();
            printf("revenue information updated successfully.\n");
            return;
        }
    }
    printf("No revenue found with serial no %d.\n", id);
}

void calculateprofit() {
    int total_income = 0;
    int total_expense = 0;
    for(int i=0; i<num_revenue; i++) {
        total_income += revenue[i].income;
        total_expense += revenue[i].expense;
    }

    int profit = total_income - total_expense;
    printf("%d is the profit earned during this particular year\n", profit);

    if (profit > 0) {
        printf("Great job! Well done.\n");
    } else {
        printf("Work hard, there is need for improvement.\n");
    }
}

void display_revenue() {
    printf("\n\tSerial No\tIncome\tExpense\tReason\n"); // Added column headings
    for (int i = 0; i < num_revenue; i++) { 
        printf("%d\t%d\t%d\t%s\n", revenue[i].serial_no, revenue[i].income, revenue[i].expense, revenue[i].reason);
    }
    printf("\n");
}

void display_menu() {
    printf("revenue Information Module\n");
    printf("---------------------------\n");
    printf("1. Add revenue\n");
    printf("2. Delete revenue\n");
    printf("3. Modify revenue\n");
    printf("4. Calculate profit\n");
    printf("5. Display revenue\n");
    printf("6. Exit\n");

    printf("Enter option number: ");
    int option;
    scanf("%d", &option);

    switch (option) {
        case 1:
            add_revenue();
            break;
        case 2:
            delete_revenue();
            break;
        case 3:
            modify_revenue();
            break;
        case 4:
            calculateprofit();
            break;
        case 5:
            display_revenue();
            break;
        case 6:
            exit(0);
            break;
        default:
            printf("Invalid option.\n");
            break;
    }
}

int main() {
    load_revenue();

    while (1) {
        display_menu();
    }

    return 0;
}
