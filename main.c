// goal :
// 1. create a password manager that can store and retrieve passwords securely
// 2. use a master password to encrypt and decrypt the stored passwords
// 3. use a simple command line interface to interact with the password manager
// 4. use .txt format to store the encrypted passwords
// 5. use a simple encryption algorithm  to encrypt the passwords

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// defining a structure to hold the password information
struct Password {
   char website[50];
    char username[50];
    char password[100];
};
// function prototypes
void encryption(char *input, char *output, char *key) {
    int key_len = strlen(key);
    for (int i = 0; input[i] != '\0'; i++) {
        output[i] = input[i] ^ key[i % key_len];
    }
    output[strlen(input)] = '\0';
}
void decryption(char *input, char *output, char *key) {
    encryption(input, output, key); // XOR decryption is the same as encryption
}

// ask the user to enter the master password and that remains permanent and stores in the .txt file
void set_master_password(char *master_password) {
   char e/s[10];
   // if the user has already set a master password, then ask them to enter it again to confirm or else if he hasnt then ask him to set it for the first time
   FILE *file = fopen("master_password.txt", "r");
    if (file != NULL) {
        fclose(file);
        strcpy(e/s, "Enter");
    } else {
        strcpy(e/s, "Set");
    }
    // then it does it stuff here
    printf("%s your master password: ", e/s);
    scanf("%s", master_password);
    FILE *file = fopen("master_password.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(file, "%s", master_password);
    fclose(file);
}
// func to enter password and store it in the .txt file with encryption
void add_password(struct Password *passwords, int *count, char *master_password) {
    struct Password new_password;
    printf("Enter website: ");
    scanf("%s", new_password.website);
    printf("Enter username: ");
    scanf("%s", new_password.username);
    printf("Enter password: ");
    scanf("%s", new_password.password);
    
    // encrypt the password before storing
    char encrypted_password[100];
    encryption(new_password.password, encrypted_password, master_password);
    strcpy(new_password.password, encrypted_password);
    
    passwords[*count] = new_password;
    (*count)++;
}   

// func to categorise website based on social media, email, banking, etc
void categorize_password(struct Password *passwords, int count) {
    printf("Categorizing passwords...\n");
    for (int i = 0; i < count; i++) {
        if (strstr(passwords[i].website, "facebook") != NULL || strstr(passwords[i].website, "twitter") != NULL || strstr(passwords[i].website, "instagram") != NULL) {
            printf("Social Media: %s\n", passwords[i].website);
        } else if (strstr(passwords[i].website, "gmail") != NULL || strstr(passwords[i].website, "yahoo") != NULL || strstr(passwords[i].website, "outlook") != NULL) {
            printf("Email: %s\n", passwords[i].website);
        } else if (strstr(passwords[i].website, "bank") != NULL || strstr(passwords[i].website, "paypal") != NULL) {
            printf("Banking: %s\n", passwords[i].website);
        } else {
            printf("Other: %s\n", passwords[i].website);
        }
    }
}

// funnc to decprt and display the stored passwords
void display_passwords(struct Password *passwords, int count, char *master_password) {
    printf("Stored passwords:\n");
    for (int i = 0; i < count; i++) {
        char decrypted_password[100];
        decryption(passwords[i].password, decrypted_password, master_password);
        printf("Website: %s, Username: %s, Password: %s\n", passwords[i].website, passwords[i].username, decrypted_password);
    }
}

int main(){
// array to store passwords
    struct Password passwords[100];
    int count = 0;
    char master_password[50];
  // setting up master password  
    set_master_password(master_password);
   // asking life choices :skull 
    int choice;
    do {
        printf("1. Add password\n");
        printf("2. Categorize passwords\n");
        printf("3. Display passwords\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                add_password(passwords, &count, master_password);
                break;
            case 2:
                categorize_password(passwords, count);
                break;
            case 3:
                display_passwords(passwords, count, master_password);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);
    
    return 0;

}
