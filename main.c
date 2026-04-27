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

// add a function to search for a password by website name
void search_password(struct Password *passwords, int count, char *master_password) {
    char website[50];
    printf("Enter website to search: ");
    scanf("%s", website);
    for (int i = 0; i < count; i++) {
        if (strcmp(passwords[i].website, website) == 0) {
            char decrypted_password[100];
            decryption(passwords[i].password, decrypted_password, master_password);
            printf("Website: %s, Username: %s, Password: %s\n",
                     passwords[i].website, passwords[i].username, decrypted_password);
            return;
        }
    }
    printf("Password for website '%s' not found.\n", website);
}

// add a function not to echo master password when typing it 
void get_master_password(char *master_password) {
    printf("Enter your master password: ");
    // disable echoing
    system("stty -echo");
    scanf("%s", master_password);
    // enable echoing
    system("stty echo");
    printf("\n");
}

// add a function to add labels like Saving Password for Facebook as Social Media, Saving Password for Gmail as Email, etc and Wrong master password should not allow access to the stored passwords
void add_label(struct Password *passwords, int count) {
    char website[50];
    printf("Enter website to add label: ");
    scanf("%s", website);
    for (int i = 0; i < count; i++) {
        if (strcmp(passwords[i].website, website) == 0) {
            char label[20];
            printf("Enter label for this website (e.g., Social Media, Email, Banking):
            scanf("%s", label);
            printf("Label '%s' added to website '%s'.\n", label, website
            );
            return;
        }
    }
    printf("Website '%s' not found.\n", website);
}
    // add a function to update/delete a stored password
void update_password(struct Password *passwords, int count, char *master_password) {
    char website[50];
    printf("Enter website to update password: ");
    scanf("%s", website);
    for (int i = 0; i < count; i++) {
        if (strcmp(passwords[i].website, website) == 0) {
            char new_password[100];
            printf("Enter new password: ");
            scanf("%s", new_password);
            char encrypted_password[100];
            encryption(new_password, encrypted_password, master_password);
            strcpy(passwords[i].password, encrypted_password);
            printf("Password for website '%s' updated successfully.\n", website);
            return;
        }
    }
    printf("Website '%s' not found.\n", website);
}
    // add a function to search passwords by category
void search_by_category(struct Password *passwords, int count) {
    char category[20];
    printf("Enter category to search (e.g., Social Media, Email, Banking): ");
    scanf("%s", category);
    printf("Passwords in category '%s':\n", category);
    for (int i = 0; i < count; i++) {
        if (strstr(passwords[i].website, category) != NULL) {
            printf("Website: %s, Username: %s\n", passwords[i].website, passwords[i].username);
        }
    }
}  
// add a function to set master password as permanent and user cant change it and the encrypted passwords get deleted after 5 wrong attempts of entering the master password
void set_permanent_master_password(char *master_password) {
    FILE *file = fopen("master_password.txt", "r");

    // 🔴 If already exists → don't allow overwrite
    if (file != NULL) {
        printf("Master password already set. You cannot change it.\n");
        fclose(file);
        return;
    }

    // 🟢 First time setup
    printf("Set your master password: ");
    scanf("%s", master_password);

    file = fopen("master_password.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(file, "%s", master_password);
    fclose(file);

    printf("Master password set successfully.\n");
}

int verify_master_password(char *master_password) {
    FILE *file = fopen("master_password.txt", "r");

    if (file == NULL) {
        printf("No master password found. Please set it first.\n");
        return 0;
    }

    char stored_password[50];
    fscanf(file, "%s", stored_password);
    fclose(file);

    int attempts = 0;

    while (attempts < 5) {
        printf("Enter master password: ");
        scanf("%s", master_password);

        if (strcmp(master_password, stored_password) == 0) {
            printf("Access granted.\n");
            return 1;
        } else {
            attempts++;
            printf("Wrong password! Attempts left: %d\n", 5 - attempts);
        }
    }

    // 💀 After 5 failed attempts
    printf("Too many failed attempts. Deleting all stored passwords...\n");
    remove("passwords.txt");

    return 0;
}

// initialise the program
int main() {
    struct Password passwords[100];
    int count = 0;
    char master_password[50];

    set_permanent_master_password(master_password);

    if (!verify_master_password(master_password)) {
        return 1; // Exit if master password verification fails
    }

    // Example usage
    add_password(passwords, &count, master_password);
    categorize_password(passwords, count);
    display_passwords(passwords, count, master_password);
    search_password(passwords, count, master_password);
    add_label(passwords, count);
    update_password(passwords, count, master_password);
    search_by_category(passwords, count);

    return 0;
}
