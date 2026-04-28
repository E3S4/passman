// goal :
// 1. create a password manager that can store and retrieve passwords securely
// 2. use a master password to encrypt and decrypt the stored passwords
// 3. use a simple command line interface to interact with the password manager
// 4. use .txt format to store the encrypted passwords
// 5. use a simple encryption algorithm  to encrypt the passwords

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Password {
    char website[50];
    char username[50];
    char password[100];
};

// encryption
void encryption(char *input, char *output, char *key) {
    int key_len = strlen(key);
    if (key_len == 0) return; // safety

    for (int i = 0; input[i] != '\0'; i++) {
        output[i] = input[i] ^ key[i % key_len];
    }
    output[strlen(input)] = '\0';
}

// decryption (same logic)
void decryption(char *input, char *output, char *key) {
    encryption(input, output, key);
}

// add password
void add_password(struct Password *passwords, int *count, char *master_password) {

    if (*count >= 100) {
        printf("Storage full!\n");
        return;
    }

    struct Password new_password;

    printf("Enter website: ");
    scanf("%49s", new_password.website);

    printf("Enter username: ");
    scanf("%49s", new_password.username);

    printf("Enter password: ");
    scanf("%99s", new_password.password);

    // encrypt before storing
    char encrypted_password[100];
    encryption(new_password.password, encrypted_password, master_password);

    strcpy(new_password.password, encrypted_password);

    passwords[*count] = new_password;
    (*count)++;

    printf("Password added successfully.\n");
}

// categorize
void categorize_password(struct Password *passwords, int count) {

    printf("Categorizing passwords...\n");

    for (int i = 0; i < count; i++) {

        if (strstr(passwords[i].website, "facebook") ||
            strstr(passwords[i].website, "twitter") ||
            strstr(passwords[i].website, "instagram")) {

            printf("Social Media: %s\n", passwords[i].website);

        }

        else if (strstr(passwords[i].website, "gmail") ||
                 strstr(passwords[i].website, "yahoo") ||
                 strstr(passwords[i].website, "outlook")) {

            printf("Email: %s\n", passwords[i].website);
        }

        else if (strstr(passwords[i].website, "bank") ||
                 strstr(passwords[i].website, "paypal")) {

            printf("Banking: %s\n", passwords[i].website);
        }

        else {
            printf("Other: %s\n", passwords[i].website);
        }
    }
}

// display
void display_passwords(struct Password *passwords, int count, char *master_password) {

    printf("\nStored passwords:\n");

    for (int i = 0; i < count; i++) {

        char decrypted[100];
        decryption(passwords[i].password, decrypted, master_password);

        printf("Website: %s | Username: %s | Password: %s\n",
               passwords[i].website,
               passwords[i].username,
               decrypted);
    }
}

// search
void search_password(struct Password *passwords, int count, char *master_password) {

    char website[50];

    printf("Enter website to search: ");
    scanf("%49s", website);

    for (int i = 0; i < count; i++) {

        if (strcmp(passwords[i].website, website) == 0) {

            char decrypted[100];
            decryption(passwords[i].password, decrypted, master_password);

            printf("Found -> %s | %s | %s\n",
                   passwords[i].website,
                   passwords[i].username,
                   decrypted);
            return;
        }
    }

    printf("Not found.\n");
}

// hide input
void get_master_password(char *master_password) {

    printf("Enter your master password: ");

    system("stty -echo");   // hide input (linux)
    scanf("%49s", master_password);
    system("stty echo");

    printf("\n");
}

// label (still simple, not stored)
void add_label(struct Password *passwords, int count) {

    char website[50];

    printf("Enter website to add label: ");
    scanf("%49s", website);

    for (int i = 0; i < count; i++) {

        if (strcmp(passwords[i].website, website) == 0) {

            char label[20];

            printf("Enter label (Social/Email/Banking): ");
            scanf("%19s", label);

            printf("Label '%s' added to '%s'\n", label, website);
            return;
        }
    }

    printf("Website not found.\n");
}

// update
void update_password(struct Password *passwords, int count, char *master_password) {

    char website[50];

    printf("Enter website to update: ");
    scanf("%49s", website);

    for (int i = 0; i < count; i++) {

        if (strcmp(passwords[i].website, website) == 0) {

            char new_pass[100];

            printf("Enter new password: ");
            scanf("%99s", new_pass);

            char encrypted[100];
            encryption(new_pass, encrypted, master_password);

            strcpy(passwords[i].password, encrypted);

            printf("Updated successfully.\n");
            return;
        }
    }

    printf("Website not found.\n");
}

// save passwords (FIXED -> saves encrypted now)
void save_passwords(struct Password *passwords, int count) {

    FILE *file = fopen("passwords.txt", "w");

    if (file == NULL) {
        printf("Error saving passwords.\n");
        return;
    }

    for (int i = 0; i < count; i++) {

        fprintf(file, "%s|%s|%s\n",
                passwords[i].website,
                passwords[i].username,
                passwords[i].password); // encrypted
    }

    fclose(file);
}

// load passwords
void load_passwords(struct Password *passwords, int *count) {

    FILE *file = fopen("passwords.txt", "r");

    if (file == NULL) return;

    while (fscanf(file, "%49[^|]|%49[^|]|%99[^\n]\n",
                  passwords[*count].website,
                  passwords[*count].username,
                  passwords[*count].password) == 3) {

        (*count)++;
    }

    fclose(file);
}

// search category (basic)
void search_by_category(struct Password *passwords, int count) {

    char category[20];

    printf("Enter keyword to search: ");
    scanf("%19s", category);

    for (int i = 0; i < count; i++) {

        if (strstr(passwords[i].website, category)) {
            printf("%s | %s\n",
                   passwords[i].website,
                   passwords[i].username);
        }
    }
}

// set master password
void set_permanent_master_password(char *master_password) {

    FILE *file = fopen("master_password.txt", "r");

    if (file != NULL) {
        fclose(file);
        printf("Master password already set.\n");
        return;
    }

    printf("Set your master password: ");
    scanf("%49s", master_password);

    file = fopen("master_password.txt", "w");
    fprintf(file, "%s", master_password);
    fclose(file);

    printf("Master password set.\n");
}

// verify
int verify_master_password(char *master_password) {

    FILE *file = fopen("master_password.txt", "r");

    if (file == NULL) {
        printf("No master password found.\n");
        return 0;
    }

    char stored[50];
    fscanf(file, "%49s", stored);
    fclose(file);

    int attempts = 0;

    while (attempts < 5) {

        get_master_password(master_password);

        if (strcmp(master_password, stored) == 0) {
            printf("Access granted.\n");
            return 1;
        }

        attempts++;
        printf("Wrong! Attempts left: %d\n", 5 - attempts);
    }

    printf("Too many attempts. Deleting data...\n");
    remove("passwords.txt");

    return 0;
}
//  draw box with title
void draw_box_with_title() {

    printf("|");
    for (int i = 0; i < 70; i++) printf("_");
    printf("\n");

    printf("|%-70s|\n", "   PASSWORD MANAGER");

    for (int i = 0; i < 4; i++) {
        printf("|%-70s|\n", " ");
    }

    printf("|");
    for (int i = 0; i < 70; i++) printf("_");
    printf("|\n");
}

// main
int main() {

    struct Password passwords[100];
    int count = 0;
    char master_password[50];

    set_permanent_master_password(master_password);

    if (!verify_master_password(master_password)) {
        return 1;
    }

    load_passwords(passwords, &count);

    char choice;

    while (1) {


    system("clear"); // linux 
    draw_box_with_title();

    printf("Enter choice: ");
    scanf(" %c", &choice);

        printf("\nSelect The Correct Choice:\n");
        printf("1. Add Password\n");
        printf("2. Search Passwords\n");
        printf("3. Display All\n");
        printf("4. Exit\n");

        scanf(" %c", &choice);

        switch (choice) {

            case '1':
                add_password(passwords, &count, master_password);
                break;

            case '2':
                search_password(passwords, count, master_password);
                break;

            case '3':
                display_passwords(passwords, count, master_password);
                break;

            case '4':
                save_passwords(passwords, count);
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}