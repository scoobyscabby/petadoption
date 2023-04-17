#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define MAX_PETS 100 

struct Pet {
    int id;
    char name[20];
    char breed[20];
    int age;
    char gender[10];
    char is_vaccinated[4];
    char other_med_info[50];
    char med_condition[50];
  char pet_status[20];
    int pet_id;
};

struct Pet pets[MAX_PETS]; 
int num_pets = 0; 

void load_pets() { 
    FILE *fp;
    fp = fopen("petinformation.txt", "r");
    if (fp == NULL) {
        return;
    } 
    num_pets = 0;
    while (fscanf(fp, "%d,%[^,],%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%d\n",
                  &pets[num_pets].id, pets[num_pets].name, pets[num_pets].breed, &pets[num_pets].age,
                  pets[num_pets].gender, pets[num_pets].is_vaccinated, pets[num_pets].other_med_info,
                  pets[num_pets].med_condition, pets[num_pets].pet_status, &pets[num_pets].pet_id) == 10) {
        num_pets++;
    } 
    fclose(fp);
}

void save_pets() { 
    FILE *fp;
    fp = fopen("petinformation.txt", "w"); 
    for (int i = 0; i < num_pets; i++) {
        fprintf(fp, "%d,%s,%s,%d,%s,%s,%s,%s,%s,%d\n",
                pets[i].id, pets[i].name, pets[i].breed, pets[i].age, pets[i].gender,
                pets[i].is_vaccinated, pets[i].other_med_info, pets[i].med_condition, pets[i].pet_status, pets[i].pet_id); 
    } 
    fclose(fp);
}

void add_pet() { 
    if (num_pets >= MAX_PETS) {
        printf("Sorry, the database is full.\n");
        return;
    }
    struct Pet pet;
    printf("Enter pet ID\n: ");
    scanf("%d", &pet.id);
    printf("Enter pet name\n: ");
    scanf("%s", pet.name);
    printf("Enter pet breed\n: ");
    scanf("%s", pet.breed);
    printf("Enter pet age\n: ");
    scanf("%d", &pet.age);
    printf("Enter pet gender\n: ");
    scanf("%s", pet.gender);
    printf("Enter whether pet is vaccinated (yes/no)\n: ");
    scanf("%s", pet.is_vaccinated);
    printf("Enter  color\n: ");
    scanf("%s", pet.other_med_info);
    printf("Enter any medical conditions\n: ");
    scanf("%s", pet.med_condition);    
   printf("Enter pet status\n: ");
scanf("%s", pet.pet_status);
    pet.pet_id = num_pets + 1;
    pets[num_pets] = pet;
    num_pets++;
    printf("Pet information added woof woof .\n");
    save_pets(); 
}

void delete_pet() { 
    int id;
    printf("Enter pet ID to delete: ");
    scanf("%d", &id); 
    for (int i = 0; i < num_pets; i++) {
        if (pets[i].id == id) { 
            for (int j = i; j < num_pets - 1; j++) {
                pets[j] = pets[j+1];
            } 
            num_pets--;
            save_pets();
            printf("Pet deleted.\n");
            return;
        }
    }
    printf("No pet found with ID %d.\n", id);
}

void search_pet() { 
    int id;
    printf("Enter pet ID to search: ");
    scanf("%d", &id); 
    for (int i = 0; i < num_pets; i++) {
        if (pets[i].id == id) { 
            printf("ID: %d\nName: %s\nBreed: %s\nAge: %d\nGender: %s\nVaccinated: %s\ncolor: %s\nMedical Condition: %s\nPet Status: %s\n",
                    pets[i].id, pets[i].name, pets[i].breed, pets[i].age, pets[i].gender,
                    pets[i].is_vaccinated, pets[i].other_med_info, pets[i].med_condition, pets[i].pet_status);
            return; 
        }
    }
    printf("No pet found with ID %d.\n", id);
}

void modify_pet() { 
    int id;
    printf("Enter pet ID to modify: ");
    scanf("%d", &id); 
    for (int i = 0; i < num_pets; i++) {
        if (pets[i].id == id) {
            printf("Which field do you want to modify?\n"); 
            printf("1. Name\n2. Breed\n3. Age\n4. Gender\n5. Vaccinated\n6. Other Medical Info\n7. Medical Condition\n8. Pet Status\n"); 
            int option;
            scanf("%d", &option); 
            switch (option) {
                case 1:
                    printf("Enter new name: ");
                    scanf("%s", pets[i].name);
                    break;
                case 2:
                    printf("Enter new breed: ");
                    scanf("%s", pets[i].breed);
                    break;
                case 3:
                    printf("Enter new age: ");
                    scanf("%d", &pets[i].age);
                    break;
                case 4:
                    printf("Enter new gender: ");
                    scanf("%s", pets[i].gender);
                    break;
                case 5:
                    printf("Enter whether pet is vaccinated (yes/no): ");
                    scanf("%s", pets[i].is_vaccinated);
                    break;
                case 6:
                    printf("Enter new color : ");
                    scanf("%s", pets[i].other_med_info);
                    break;
                case 7:
                    printf("Enter new medical condition: ");
                    scanf("%s", pets[i].med_condition);
                    break;
                case 8:
                    printf("Enter new pet status: ");
                    scanf("%s", pets[i].pet_status);
                    break;
                default:
                    printf("Invalid option.\n");
                    break;
            }
            save_pets(); 
            printf("Pet information updated.\n");
            return;
        }
    }
    printf("No pet found with ID %d.\n", id);
}

void display_pets() { 
    printf("ID\tName\tBreed\tAge\tGender\tVaccinated\tcolor\tMedical Condition\tPet Status\n"); 
    for (int i = 0; i < num_pets; i++) {
        printf("%d\t%s\t%s\t%d\t%s\t%s\t\t%s\t\t%s\t%s\t\t%d\n",
                pets[i].id, pets[i].name, pets[i].breed, pets[i].age, pets[i].gender,
                pets[i].is_vaccinated, pets[i].other_med_info, pets[i].med_condition, pets[i].pet_status, pets[i].pet_id);
    }
}

void display_menu() { 
    printf("Pet Information Module\n"); 
    printf("-----------------------\n"); 
    printf("1. Add Pet\n"); 
    printf("2. Delete Pet\n"); 
    printf("3. Search Pet\n"); 
    printf("4. Modify Pet\n"); 
    printf("5. Display Pets\n"); 
    printf("6. Exit\n"); 
    printf("Enter option number: "); 
    int option;
    scanf("%d", &option); 
    switch (option) {
        case 1:
            add_pet(); 
            break;
        case 2:
            delete_pet(); 
            break;
        case 3:
            search_pet(); 
            break;
        case 4:
            modify_pet(); 
            break;
        case 5:
            display_pets(); 
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
    load_pets(); 
    while (1) {
        display_menu(); 
    }
    return 0;
}    



