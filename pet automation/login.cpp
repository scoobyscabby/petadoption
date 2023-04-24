#include <stdio.h>
#include <string.h>

/* Define maximum number of accounts that can be created */
#define MAX_ACCOUNTS 100

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
int main() {
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
    if (attempts == 3) {
        printf("Maximum number of attempts reached. Exiting program.\n");
    }
    
    /* Check user role and provide appropriate options */
    else {
        printf("Access granted. Welcome %s!\n", username);
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

    return 0;
}
