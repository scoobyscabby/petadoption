
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_pastowner 100

struct pastowner {
    int id;
    char name[20];
    char email[50];
    char address[100];
    char phone[20];
    char id_proof[50];
    char owned_pet[20];
    char reason[50];
    char info[100];
};

struct pastowner pastowner[MAX_pastowner];
int num_pastowner = 0;

void load_pastowner() {
    FILE *fp;
    fp = fopen("pastownerinformation.txt", "r");
    if (fp == NULL) {
        return;
    }
    
    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", &pastowner[num_pastowner].id, pastowner[num_pastowner].name,
                    pastowner[num_pastowner].email, pastowner[num_pastowner].address, pastowner[num_pastowner].phone,
                    pastowner[num_pastowner].id_proof, pastowner[num_pastowner].owned_pet, pastowner[num_pastowner].reason, pastowner[num_pastowner].info) == 9) 
                    {
					
        num_pastowner++;
    }

    fclose(fp);
}

void save_pastowner() {
    FILE *fp;
    fp = fopen("pastownerinformation.txt", "w");
    for (int i = 0; i < num_pastowner; i++) {
        fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%s,%s\n", pastowner[i].id, pastowner[i].name, pastowner[i].email,
                pastowner[i].address, pastowner[i].phone, pastowner[i].id_proof, pastowner[i].owned_pet, pastowner[i].reason, pastowner[i].info);
    }
    fclose(fp);
}

void add_pastowner() {
    if (num_pastowner >= MAX_pastowner) {
        printf("Sorry, the database is full.\n");
        return;
    }
    struct pastowner new_pastowner;
    printf("Enter pastowner ID: ");
    scanf("%d", &new_pastowner.id);
    printf("Enter pastowner name: ");
    scanf("%s", new_pastowner.name);
    printf("Enter pastowner email: ");
    scanf("%s", new_pastowner.email);
    printf("Enter pastowner physical address: ");
    scanf("%s", new_pastowner.address);
    printf("Enter pastowner phone number: ");
    scanf("%s", new_pastowner.phone);
    printf("Enter pastowner ID proof (e.g. government-issued ID): ");
    scanf("%s", new_pastowner.id_proof);
    printf("Enter owned pet name: ");
    scanf("%s", new_pastowner.owned_pet);
    printf("Enter reason for giving up pet: ");
    scanf("%s", new_pastowner.reason);
    printf("Enter additional information about pet: ");
    scanf("%s", new_pastowner.info);
    pastowner[num_pastowner] = new_pastowner;
    num_pastowner++;
    printf("pastowner information added successfully.\n");
    save_pastowner();
}


void delete_pastowner() {
    int id;
    printf("Enter pastowner ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < num_pastowner; i++) {
        if (pastowner[i].id == id) {
            for (int j = i; j < num_pastowner - 1; j++) {
                pastowner[j] = pastowner[j + 1];
            }
            num_pastowner--;
            save_pastowner();
            printf("pastowner deleted.\n");
            return;
        }
    }
    printf("No pastowner found with ID %d.\n", id);
}

void modify_pastowner() {
    int id;
    printf("Enter pastowner ID to modify: ");
    scanf("%d", &id);

    for (int i = 0; i < num_pastowner; i++) {
        if (pastowner[i].id == id) {
            printf("Which field do you want to modify?\n");
            printf("1. Name\n2. Email\n3. Physical Address\n4. Phone\n5. ID Proof\n6. Owned Pet\n7. Reason\n8. Info\n");
            int option;
            scanf("%d", &option);

            switch (option) {
            case 1:
                printf("Enter new name: ");
                scanf("%s", pastowner[i].name);
                break;
            case 2:
                printf("Enter new email: ");
                scanf("%s", pastowner[i].email);
                break;
            case 3:
                printf("Enter new physical address: ");
                scanf("%s", pastowner[i].address);
                break;
            case 4:
                printf("Enter new phone number: ");
                scanf("%s", pastowner[i].phone);
                break;
            case 5:
                printf("Enter new ID proof: ");
                scanf("%s", pastowner[i].id_proof);
                break;
            case 6:
                printf("Enter new owned pet name: ");
                scanf("%s", pastowner[i].owned_pet);
                break;
            case 7:
                printf("Enter new reason for giving up pet: ");
                scanf("%s", pastowner[i].reason);
                break;
            case 8:
                printf("Enter new additional information about pet: ");
                scanf("%s", pastowner[i].info);
                break;
            default:
                printf("Invalid option selected.\n");
                break;
            }

            save_pastowner();
            printf("pastowner information updated successfully.\n");
            return;
        }
    }
    printf("No pastowner found with ID %d.\n", id);
}

void search_pastowner() {
    char name[20];
    printf("Enter pastowner name to search: ");
    scanf("%s", name);
    printf("\n");

    int count = 0;

    for (int i = 0; i < num_pastowner; i++) {
        if (strcmp(pastowner[i].name, name) == 0) {
            if (count == 0) {
                printf("Matching pastowner found:\n");
            }
            count++;

            printf("ID: %d\nName: %s\nEmail: %s\nPhysical Address: %s\nPhone: %s\nID Proof: %s\nOwned Pet Name: %s\nReason: %s\nInfo: %s\n\n",
                   pastowner[i].id, pastowner[i].name, pastowner[i].email, pastowner[i].address, pastowner[i].phone,
                   pastowner[i].id_proof, pastowner[i].owned_pet, pastowner[i].reason, pastowner[i].info);
        }
    }

    if (count == 0) {
        printf("No pastowner found with name %s.\n", name);
    }
}

void display_pastowner() {
    printf("ID\tName\tEmail\tPhysical Address\tPhone\tID Proof\tOwned Pet Name\tReason\tInfo\n");
    for (int i = 0; i < num_pastowner; i++) {
        printf("%d\t%s\t%s\t%s\t\t%s\t%s\t%s\t\t%s\t%s\n", pastowner[i].id, pastowner[i].name, pastowner[i].email,
               pastowner[i].address, pastowner[i].phone, pastowner[i].id_proof, pastowner[i].owned_pet, pastowner[i].reason, pastowner[i].info);
    }
}

void display_menu() {
    printf("pastowner Information Module\n");
    printf("---------------------------\n");
    printf("1. Add pastowner\n");
    printf("2. Delete pastowner\n");
    printf("3. Modify pastowner\n");
    printf("4. Search pastowner\n");
    printf("5. Display pastowner\n");
    printf("6. Exit\n");
    printf("Enter option number: ");
    int option;
    scanf("%d", &option);

    switch (option) {
    case 1:
        add_pastowner();
        break;
    case 2:
        delete_pastowner();
        break;
    case 3:
        modify_pastowner();
        break;
    case 4:
        search_pastowner();
        break;
    case 5:
        display_pastowner();
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
    load_pastowner();
    while (1) {
        display_menu();
    }
    return 0;
}
