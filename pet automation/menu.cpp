
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Function declarations
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

int main() {
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
        printf("4. Adoption Status\n");
        printf("5. Past Owner Information\n");
        printf("6. Search and Filter\n");
        printf("7. Revenue and Profit\n");
        printf("8. Adoption Progress Tracking\n");
        printf("9. Login Portal\n");
        printf("10. Exit\n");
        
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
                module4_adoption_status();
                break;
            case 5:
                module5_past_owner_info();
                break;
            case 6:
                module6_search_filter();
                break;
            case 7:
                module7_revenue_profit();
                break;
            case 8:
                module8_adoption_progress_tracking();
                break;
            case 9:
                module9_login_portal();
                break;
            case 10:
                printf("\nExiting...\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
                break;
        }
    } while (choice != 10);
    
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
    // implementation code goes here
}

void module2_pet_info() {
    printf("Pet Information Module\n");
    // implementation code goes here
}

void module3_payment() {
    printf("Payment Module\n");
    // implementation code goes here
}

void module4_adoption_status() {
    printf("Adoption Status Module\n");
    // implementation code goes here
}

void module5_past_owner_info() {
    printf("Past Owner Information Module\n");
    // implementation code goes here
}

void module6_search_filter() {
    printf("Search and Filter Module\n");
    // implementation code goes here
}

void module7_revenue_profit() {
    printf("Revenue and Profit Module\n");
    // implementation code goes here
}

void module8_adoption_progress_tracking() {
    printf("Adoption Progress Tracking Module\n");
    // implementation code goes here
}

void module9_login_portal() {
    printf("Login Portal Module\n");
    // implementation code goes here
}
