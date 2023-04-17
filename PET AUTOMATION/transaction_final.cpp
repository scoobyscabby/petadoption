
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_transaction 100

struct transaction {
   int serial_no;
   char type[10];
   char nature[50];
   char from_whom[50];
   int amount;
   char date[20];
   char cvv[5];
   char expiry_date[10];
   char name_card[50];
};

struct transaction transaction[MAX_transaction];
int num_transaction = 0;

void load_transaction() {
    FILE *fp;
    fp = fopen("transaction.txt", "r");
    if (fp == NULL) {
        return;
    }
    
     while ((fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%s\n", & transaction[num_transaction].amount, transaction[num_transaction].cvv, transaction[num_transaction].date,
       transaction[num_transaction].expiry_date,
       transaction[num_transaction].from_whom, transaction[num_transaction].name_card, transaction[num_transaction].nature, &
       transaction[num_transaction].serial_no, transaction[num_transaction].type)) == 9) {
     printf("serial no %d\n", transaction[num_transaction].serial_no);
     num_transaction++;
   }

    fclose(fp);
}

void save_transaction() {
    FILE *fp;
    fp = fopen("transaction.txt", "w");
    for (int i = 0; i < num_transaction; i++) {
       fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%d,%s\n", transaction[i].amount, transaction[i].cvv, transaction[i].date, transaction[i].expiry_date,
           transaction[i].from_whom, transaction[i].name_card, transaction[i].nature, transaction[i].serial_no, transaction[i].type);
    }
    fclose(fp);
}

void add_transaction() {
    if (num_transaction >= MAX_transaction) {
        printf("Sorry, the database is full.\n");
        return;
    }
    struct transaction obj1;
   	printf("Enter Serial No:\n");
    scanf("%d", & obj1.serial_no);
    printf("Enter Type (cash/card):\n");
    scanf("%s", obj1.type);
    printf("Enter Nature of Payment:\n");
    scanf("%s", obj1.nature);
    printf("Enter From Whom or What:\n ");
    scanf("%s", obj1.from_whom);
    printf("Enter Amount:\n");
    scanf("%d", & obj1.amount);
    printf("Enter Date (dd/mm/yyyy):\n");
    scanf("%s", obj1.date);

    if (strcmp(obj1.type, "card") == 0) {
        printf("Enter CVV:\n");
        scanf("%s", obj1.cvv);

        printf("Enter Expiry Date (mm/yy):\n");
        scanf("%s", obj1.expiry_date);

        printf("Enter Name on Card:\n");
        scanf("%s", obj1.name_card);
    } else {
        strcpy(obj1.cvv, "-");
        strcpy(obj1.expiry_date, "-");
        strcpy(obj1.name_card, "-");
    }
    transaction[num_transaction] = obj1;
    num_transaction++;
    printf("transaction information added successfully.\n");
    save_transaction();
}


void delete_transaction() {
    int id;
    printf("Enter transaction serial no to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < num_transaction; i++) {
        if (transaction[i].serial_no == id) {
            for (int j = i; j < num_transaction - 1; j++) {
                transaction[j] = transaction[j + 1];
            }
            num_transaction--;
            save_transaction();
            printf("transaction deleted.\n");
            return;
        }
    }
    printf("No transaction found with ID %d.\n", id);
}

void modify_transaction() {
    int id;
    printf("Enter transaction seral no to modify: ");
    scanf("%d", &id);

    for (int i = 0; i < num_transaction; i++) {
        if (transaction[i].serial_no == id) {
        	
        	if (strcmp(transaction[i].type, "cash") == 0) {
        	 	printf("Which field do you want to modify?\n");
        	 	printf("\n1. Type\n2. Nature of Payment\n3. From Whom\n4. Amount\n5. Date\n");
        	 	int option;
	            scanf("%d", &option);

    	        switch (option) {
        	    	case 1:
            	    	printf("Enter new type: ");
                		scanf("%s", transaction[i].type);
                		break;
            		case 2:
                		printf("Enter new nature of payment: ");
                		scanf("%s", transaction[i].nature);
                		break;
            		case 3:
                		printf("Enter new from whom: ");
                		scanf("%s", transaction[i].from_whom);
                		break;
            		case 4:
                		printf("Enter new amount: ");
                		scanf("%d", &transaction[i].amount);
                		break;
            		case 5:
                		printf("Enter new date: ");
                		scanf("%s", transaction[i].date);
                		break;
            		default:
                		printf("Invalid option selected.\n");
                		break;
            	}

            	save_transaction();
            	printf("transaction information updated successfully.\n");
            	return;
			}

			if (strcmp(transaction[i].type, "card") == 0) {
        	 	printf("Which field do you want to modify?\n");
        	 	printf("\n1. Type\n2. Nature of Payment\n3. From Whom\n4. Amount\n5. Date\n6. CVV\n7. Expiry Date\n8. Name on Card");
        	 	int option;
	            scanf("%d", &option);

    	        switch (option) {
        	    	case 1:
            	    	printf("Enter new type: ");
                		scanf("%s", transaction[i].type);
                		break;
            		case 2:
                		printf("Enter new nature of payment: ");
                		scanf("%s", transaction[i].nature);
                		break;
            		case 3:
                		printf("Enter new from whom: ");
                		scanf("%s", transaction[i].from_whom);
                		break;
            		case 4:
                		printf("Enter new amount: ");
                		scanf("%d", transaction[i].amount);
                		break;
            		case 5:
                		printf("Enter new date: ");
                		scanf("%s", transaction[i].date);
                		break;

					case 6:
                		printf("Enter new cvv: ");
                		scanf("%s", transaction[i].cvv);
                		break;
					case 7:
                		printf("Enter new expiry date: ");
                		scanf("%s", transaction[i].expiry_date);
                		break;            		
					case 8:
                		printf("Enter new name of card holder: ");
                		scanf("%s", transaction[i].name_card);
                		break; 
					default:
                		printf("Invalid option selected.\n");
                		break;
            	}

            	save_transaction();
            	printf("transaction information updated successfully.\n");
            	return;
			}            
        }
    }
    printf("No transaction found with serial no %d.\n", id);
}

void search_transaction() {
    int name;
    printf("Enter transaction serial no to search: ");
    scanf("%d", &name);
    printf("\n");

    int count = 0;

    for (int i = 0; i < num_transaction; i++) {
    	printf("check1");
        if (transaction[i].serial_no == name) {
        	printf("check1");
            if (count == 0) {
                printf("Matching transaction found:\n");
            }
            count++;

            printf("\nType - %s\nSerail No - %d\nNature - %s\nFrom Whome- %s\nAmount - %d\n Date - %s\n CVV- %s\nExpiry Date - %s\nName Of Card - %s",
             transaction[i].type,
             transaction[i].serial_no,
             transaction[i].nature,
             transaction[i].from_whom,
             transaction[i].amount,
             transaction[i].date,
             transaction[i].cvv,
             transaction[i].expiry_date,
             transaction[i].name_card);
                   
        }
    }

    if (count == 0) {
        printf("No transaction found with serial no %s.\n", name);
    }
}

void display_transaction() {
    printf("\n\nCash Payments: \n");
    printf("\nType\tSerial No\tNature of Payment\tFrom Whom\tAmount\tDate");
    printf("%d", transaction[0].amount);

	for (int i = 0; i <= num_transaction; i++) {
        if (strcmp(transaction[i].type, "cash") == 0) {

        	printf("\n%s\t%d\t%s\t%s\t%d\t%s",
             transaction[i].type,
             transaction[i].serial_no,
             transaction[i].nature,
             transaction[i].from_whom,
             transaction[i].amount,
             transaction[i].date);
        }
    }
    printf("\n");
    printf("\nType\tSerial No\tNature of Payment\tFrom Whom\tAmount\tDate\tCVV\tExpiry Date\tName on Card");
    for (int i = 0; i <= num_transaction; i++) {
        if (strcmp(transaction[i].type, "card") == 0) {
        	printf("\n%s\t%d\t%s\t%s\t%d\t%s\t%s\t%s\t%s",
             transaction[i].type,
             transaction[i].serial_no,
             transaction[i].nature,
             transaction[i].from_whom,
             transaction[i].amount,
             transaction[i].date,
             transaction[i].cvv,
             transaction[i].expiry_date,
             transaction[i].name_card);
    	}
    }
    printf("\n");
}

void display_menu() {
    printf("transaction Information Module\n");
    printf("---------------------------\n");
    printf("1. Add transaction\n");
    printf("2. Delete transaction\n");
    printf("3. Modify transaction\n");
    printf("4. Search transaction\n");
    printf("5. Display transaction\n");
    printf("6. Exit\n");
    printf("Enter option number: ");
    int option;
    scanf("%d", &option);

    switch (option) {
    case 1:
        add_transaction();
        break;
    case 2:
        delete_transaction();
        break;
    case 3:
        modify_transaction();
        break;
    case 4:
        search_transaction();
        break;
    case 5:
        display_transaction();
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
    load_transaction();
    while (1) {
        display_menu();
    }
    return 0;
}
