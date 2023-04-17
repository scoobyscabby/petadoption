#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CUSTOMERS 100
#define MAX_PETS 100 
#define MAX_pastowner 100
#define MAX_transaction 100
#define MAX_revenue 100
#define MAX_ACCOUNTS 100


void display_box();
void print_welcome_message();
void print_note();
void print_quote();
void display_pet_automation();
void module1_customer_info();
void module2_pet_info();
void module3_payment();
void module4_adoption_status();
void module5_past_owner_info();
void module6_search_filter();
void module7_revenue_profit();
void module8_adoption_progress_tracking();
void module9_login_portal();

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
	
    FILE *fp= fopen("customerinformation.txt", "r");
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

void display_menu1() {
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

void display_menu2() { 
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

void display_menu3() {
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

void display_menu4() {
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

void display_menu5() {
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


/* Define user struct */
typedef struct {
    char username[20];
    char password[20];
    char role[10];
} user;

/* Initialize user array */
user accounts[MAX_ACCOUNTS];

/* Initialize global variable to keep track of number of accounts */
int numAccounts = 0;

/* Define function to check if username and password match */
int verifyLogin(char username[], char password[]) {
    int i;
    for (i = 0; i < numAccounts; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

/* Define function to prompt user to create new account */
void createAccount() {
    char username[20], password[20], role[10];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Enter role (admin/user): ");
    scanf("%s", role);
    if (numAccounts < MAX_ACCOUNTS) {
        strcpy(accounts[numAccounts].username, username);
        strcpy(accounts[numAccounts].password, password);
        strcpy(accounts[numAccounts].role, role);
        numAccounts++;
        printf("Account created successfully!\n");
                FILE *fp = fopen("account.txt", "w");
        if (fp != NULL) {
            int i;
            for (i = 0; i < numAccounts; i++) {
                fprintf(fp, "%s %s %s\n", accounts[i].username, accounts[i].password, accounts[i].role);
            }
            fclose(fp);
        }
        else {
            printf("Error: Could not open file.\n");
        }
    }

    else {
        printf("Maximum number of accounts reached.\n");
    }
}

/* Define function to prompt user to change password */
void changePassword(int index) {
    char password[20];
    printf("Enter new password: ");
    scanf("%s", password);
    strcpy(accounts[index].password, password);
    printf("Password changed successfully!\n");
            FILE *fp = fopen("account.txt", "w");
        if (fp != NULL) {
            int i;
            for (i = 0; i < numAccounts; i++) {
                fprintf(fp, "%s %s %s\n", accounts[i].username, accounts[i].password, accounts[i].role);
            }
            fclose(fp);
        }
        else {
            printf("Error: Could not open file.\n");
        }
    }



/* Define function to prompt user to delete account */
void deleteAccount() {
    int index, i;
    char response;
    char username[20], password[20];
    printf("Enter username of account to be deleted: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    index = verifyLogin(username, password);
    if (index == -1) {
        printf("Incorrect username/password combination. Account not deleted.\n");
        return;
    }
    printf("Are you sure you want to delete this account? (y/n): ");
    scanf(" %c", &response);
    if (response == 'y') {
        for (i = index; i < numAccounts - 1; i++) {
            accounts[i] = accounts[i+1]; /* Shift all accounts after deleted one up by one */
        }
        numAccounts--;
        printf("Account deleted successfully!\n");
                FILE *fp = fopen("account.txt", "w");
        if (fp != NULL) {
            int i;
            for (i = 0; i < numAccounts; i++) {
                fprintf(fp, "%s %s %s\n", accounts[i].username, accounts[i].password, accounts[i].role);
            }
            fclose(fp);
        }
        else {
            printf("Error: Could not open file.\n");
        }
    }

    }



/* Define function to display account information */
void viewAccounts() {
    int i;
    printf("%-20s %-20s %-10s\n", "Username", "Password", "Role");
    printf("------------------------------------------------\n");
    for (i = 0; i < numAccounts; i++) {
        printf("%-20s %-20s %-10s\n", accounts[i].username, accounts[i].password, accounts[i].role);
    }
}

/* Define main function */
int login_main() {
    int i, attempts = 0, index;
    char username[20], password[20], role[10];
    
    /* Initialize default accounts */
    strcpy(accounts[0].username, "admin");
    strcpy(accounts[0].password, "admin");
    strcpy(accounts[0].role, "admin");
    numAccounts++;
    strcpy(accounts[1].username, "clerk");
    strcpy(accounts[1].password, "password");
    strcpy(accounts[1].role, "user");
    numAccounts++;

    /* Prompt user to login */
    do {
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);
        index = verifyLogin(username, password);
        if (index == -1) {
            printf("Invalid username or password. Please try again.\n");
            attempts++;
        }
    } while (index == -1 && attempts < 3);

    /* Check if user has exceeded maximum number of attempts */
    while (attempts == 3) {
        printf("Maximum number of attempts reached. Exiting program.\n");
    } 
	printf("Access granted. Welcome %s!\n", username);
}
    /* Check user role and provide appropriate options */
    int right_main()  {
       int index;
        if (strcmp(accounts[index].role, "admin") == 0) {
            int choice;
            do {
                printf("Choose an option:\n");
                printf("1. Create new account\n");
                printf("2. Delete account\n");
                printf("3. Change password\n");
                printf("4. View accounts\n");
                printf("5. Exit\n");
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        createAccount();
                        break;
                    case 2:
                        deleteAccount();
                        break;
                    case 3:
                        changePassword(index);
                        break;
                    case 4:
                        viewAccounts();
                        break;
                    case 5:
                        printf("Exiting program.\n");
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                        break;
                }
            } while (choice != 5);
        }
        else {
            int choice;
            do {
                printf("Choose an option:\n");
                printf("1. Change password\n");
                printf("2. View account information\n");
                printf("3. Exit\n");
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        changePassword(index);
                        break;
                    case 2:
                        printf("%-20s %-10s\n", "Username", "Role");
                        printf("-------------------------\n");
                        printf("%-20s %-10s\n", accounts[index].username, accounts[index].role);
                        break;
                    case 3:
                        printf("Exiting program.\n");
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                        break;
                }
            } while (choice != 3);
        }
    }
 

int revenue_main() {
    load_revenue();

    while (1) {
        display_menu5();
    }

    return 0;
}
int transaction_main() {
    load_transaction();
    while (1) {
        display_menu4();
    }
    return 0;
}
int petowner_main() {
    load_pastowner();
    while (1) {
        display_menu3();
    }
    return 0;
}
int customer_main() {
    load_customers();
    while (1) {
        display_menu1();
    }
    return 0;
}

int petinfo_main() { 
    load_pets(); 
    while (1) {
        display_menu2(); 
    }
    return 0;
}  

void display_box() {
    printf("========================================\n");
    printf("|                                      |\n");
    printf("|           Pawsome Pet Care           |\n");
    printf("|  Pet Adoption Automation Software    |\n");
    printf("|                                      |\n");
    printf("========================================\n");
}

void print_welcome_message() {
    const char* messages[3] = {
        "Welcome to Pawsome Pet Care! Hope you have a purr-fect day.",
        "Pet Care. the ultimate pet managment software .",
        "We're so glad you're here! ."
    };
    int index = rand() % 3;
    printf("%s", messages[index]);
}



void print_note() {


printf("Note: This system is only accessible to authorized personnel.\n");


 
}

void print_quote() {
    const char* quotes[3] = {
        "\"Until one has loved an animal, a part of one's soul remains unawakened.\" - Anatole France",
        "\"Pets are humanizing. They remind us we have an obligation and responsibility to preserve and nurture and care for all life.\" - James Cromwell",
        "\"The purity of a person's heart can be quickly measured by how they regard animals.\" - Anonymous"
    };
    int index = rand() % 3;
    printf("\n\n%s\n\n", quotes[index]);
}

void module1_customer_info() {
    printf("Customer Information Module\n");
    customer_main();
}

void module2_pet_info() {
    printf("Pet Information Module\n");
    // implementation code goes here
    petinfo_main();
}

void module3_payment() {
    printf("Payment Module\n");
    // implementation code goes here
    transaction_main();
}

//void module4_adoption_status() {
  //  printf("Adoption Status Module\n");
    // implementation code goes here
//}

void module5_past_owner_info() {
    printf("Past Owner Information Module\n");
    // implementation code goes here
    petowner_main();
}

//void module6_search_filter() {
  //  printf("Search and Filter Module\n");
    // implementation code goes here
//}

void module7_revenue_profit() {
    printf("Revenue and Profit Module\n");
    // implementation code goes here
    revenue_main();
}

//void module8_adoption_progress_tracking() {
  //  printf("Adoption Progress Tracking Module\n");
    // implementation code goes here
//}

void module9_login_portal() {
    printf("Login Portal Module\n");
    // implementation code goes here
     right_main() ;
    
}

int main() {
	login_main();
    srand(time(NULL));
    
    // Display header and welcome message
    display_box();
    printf("\n");
    print_welcome_message();
    printf("\n");
    
    // Display current date and time on left side
    time_t now = time(NULL);
struct tm *tm = localtime(&now);

char date[11];
strftime(date, sizeof(date), "%d/%m/%Y", tm);
printf("%*s\n", 80 - strlen(date), date);
  
    printf("%*s\n", 80 - strlen(date), date);
    
    // Display Pet Adoption Automation Software on right side
    
    
    // Display note
    print_note();
    
    printf("\n");
    
    // Display random quote
    print_quote();
    
    int choice;
    do {
        printf("\nSelect a module:\n");
        printf("1. Customer Information\n");
        printf("2. Pet Information\n");
        printf("3. Payment\n");
        printf("4. Past Owner Information\n");
        printf("5. Revenue and Profit\n");
        printf("6. Login Portal\n");
        printf("7 Exit\n");
        
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                module1_customer_info();
                break;
            case 2:
                module2_pet_info();
                break;
            case 3:
                module3_payment();
                break;
            case 4:
                module5_past_owner_info();
                break;
            case 5:
                module7_revenue_profit();
                break;
            case 6:
                module9_login_portal();
                break;
            case 7:
                printf("\nExiting...\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
                break;
        }
    } while (choice != 7);
    
    return 0;
}
