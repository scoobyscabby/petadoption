#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 100

struct Customer {
    int id;
    char name[20];
    char email[50];
    char address[100];
    char phone[20];
    char id_proof[50];
    char adopted_pet[20];
};

struct Customer customers[MAX_CUSTOMERS];

int num_customers = 0;

void load_customers() {
    FILE *fp;
    fp = fopen("customerinformation.txt", "r");
    if (fp == NULL) {
        return;
    }
    num_customers = 0;
    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", &customers[num_customers].id, customers[num_customers].name, 
                  customers[num_customers].email, customers[num_customers].address, customers[num_customers].phone, 
                  customers[num_customers].id_proof, customers[num_customers].adopted_pet) == 7) {
        num_customers++;
    }
    fclose(fp);
}

void save_customers() {
    FILE *fp;
    fp = fopen("customerinformation.txt", "w");
    for (int i = 0; i < num_customers; i++) {
        fprintf(fp, "%d,%s,%s,%s,%s,%s,%s\n", customers[i].id, customers[i].name, customers[i].email, 
                customers[i].address, customers[i].phone, customers[i].id_proof, customers[i].adopted_pet);
    }
    fclose(fp);
}

void add_customer() {
    if (num_customers >= MAX_CUSTOMERS) {
        printf("Sorry, the database is full.\n");
        return;
    }
    struct Customer customer;
    printf("Enter customer ID: \n");
    scanf("%d", &customer.id);
    printf("Enter customer name: \n");
    scanf("%s", customer.name);
    printf("Enter customer email: \n");
    scanf("%s", customer.email);
    printf("Enter customer physical address:\n ");
    scanf("%s", customer.address);
    printf("Enter customer phone number:\n ");
    scanf("%s", customer.phone);
    printf("Enter customer ID proof (e.g. government-issued ID): \n");
    scanf("%s", customer.id_proof);
    printf("Enter adopted pet name: \n");
    scanf("%s", customer.adopted_pet);
    customers[num_customers] = customer;
    num_customers++;
    printf("Customer information added successfully.\n");
    save_customers();
}

void delete_customer() {
    int id;
    printf("Enter customer ID to delete: \n");
    scanf("%d", &id);
    for (int i = 0; i < num_customers; i++) {
        if (customers[i].id == id) {
            for (int j = i; j < num_customers - 1; j++) {
                customers[j] = customers[j + 1];
            }
            num_customers--;
            save_customers();
            printf("Customer deleted.\n");
            return;
        }
    }
    printf("No customer found with ID %d.\n", id);
}

void modify_customer() {
    int id;
    printf("Enter customer ID to modify: \n");
    scanf("%d", &id);

    for (int i = 0; i < num_customers; i++) {
        if (customers[i].id == id) {
            printf("Which field do you want to modify?\n");
            printf("1. Name\n2. Email\n3. Physical Address\n4. Phone\n5. ID Proof\n6. Adopted Pet\n");
            int option;
            scanf("%d", &option);

            switch (option) {
            case 1:
                printf("Enter new name: \n");
                scanf("%s", customers[i].name);
                break;
            case 2:
                printf("Enter new email: \n");
                scanf("%s", customers[i].email);
                break;
            case 3:
                printf("Enter new physical address: \n");
                scanf("%s", customers[i].address);
                break;
            case 4:
                printf("Enter new phone number: ");
                scanf("%s", customers[i].phone);
                break;
            case 5:
                printf("Enter new ID proof: ");
                scanf("%s", customers[i].id_proof);
                break;
            case 6:
                printf("Enter new adopted pet name: ");
                scanf("%s", customers[i].adopted_pet);
                break;
            default:
                printf("Invalid option selected.\n");
                break;
            }

            save_customers();
            printf("Customer information updated successfully.\n");
            return;
        }
    }
    printf("No customer found with ID %d.\n", id);
}

void search_customer() {
    char name[20];
    printf("Enter customer name to search: ");
    scanf("%s", name);
    printf("\n");

    int count = 0;

    for (int i = 0; i < num_customers; i++) {
        if (strcmp(customers[i].name, name) == 0) {
            if (count == 0) {
                printf("Matching customers found:\n");
            }
            count++;
            
            printf("ID: %d\nName: %s\nEmail: %s\nPhysical Address: %s\nPhone: %s\nID Proof: %s\nAdopted Pet Name: %s\n\n", 
                   customers[i].id, customers[i].name, customers[i].email, customers[i].address, customers[i].phone, 
                   customers[i].id_proof, customers[i].adopted_pet);
        }
    }

    if (count == 0) {
        printf("No customer found with name %s.\n", name);
    }
}

void display_customers() {
    printf("ID\tName\tEmail\tPhysical Address\tPhone\tID Proof\tAdopted Pet Name\n");
    for (int i = 0; i < num_customers; i++) {
        printf("%d\t%s\t%s\t%s\t\t%s\t%s\t%s\n", customers[i].id, customers[i].name, customers[i].email, 
                customers[i].address, customers[i].phone, customers[i].id_proof, customers[i].adopted_pet);
    }
}

void display_menu() {
    printf("Customer Information Module\n");
    printf("---------------------------\n");
    printf("1. Add Customer\n");
    printf("2. Delete Customer\n");
    printf("3. Modify Customer\n");
    printf("4. Search Customer\n");
    printf("5. Display Customers\n");
    printf("6. Exit\n");
    printf("Enter option number: ");
    int option;
    scanf("%d", &option);

    switch (option) {
    case 1:
        add_customer();
        break;
    case 2:
        delete_customer();
        break;
    case 3:
        modify_customer();
        break;
    case 4:
        search_customer();
        break;
    case 5:
        display_customers();
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
    load_customers();
    while (1) {
        display_menu();
    }
    return 0;
}
