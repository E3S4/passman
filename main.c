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
    scanf("%s", new_password.website);

    printf("Enter username: ");
    scanf("%s", new_password.username);

    printf("Enter password: ");
    scanf("%s", new_password.password);

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

        } else if (strstr(passwords[i].website, "gmail") ||
                   strstr(passwords[i].website, "yahoo") ||
                   strstr(passwords[i].website, "outlook")) {

            printf("Email: %s\n", passwords[i].website);

        } else if (strstr(passwords[i].website, "bank") ||
                   strstr(passwords[i].website, "paypal")) {

            printf("Banking: %s\n", passwords[i].website);

        } else {
            printf("Other: %s\n", passwords[i].website);
        }
    }
}

// display
void display_passwords(struct Password *passwords, int count, char *master_password) {
    printf("Stored passwords:\n");
    for (int i = 0; i < count; i++) {
        char decrypted[100];
        decryption(passwords[i].password, decrypted, master_password);

        printf("Website: %s | Username: %s | Password: %s\n",
               passwords[i].website, passwords[i].username, decrypted);
    }
}

// search
void search_password(struct Password *passwords, int count, char *master_password) {
    char website[50];

    printf("Enter website to search: ");
    scanf("%s", website);

    for (int i = 0; i < count; i++) {
        if (strcmp(passwords[i].website, website) == 0) {
            char decrypted[100];
            decryption(passwords[i].password, decrypted, master_password);

            printf("Found -> %s | %s | %s\n",
                   passwords[i].website, passwords[i].username, decrypted);
            return;
        }
    }

    printf("Not found.\n");
}

// hide input
void get_master_password(char *master_password) {
    printf("Enter your master password: ");
    system("stty -echo");
    scanf("%s", master_password);
    system("stty echo");
    printf("\n");
}

// label (fixed)
void add_label(struct Password *passwords, int count) {
    char website[50];

    printf("Enter website to add label: ");
    scanf("%s", website);

    for (int i = 0; i < count; i++) {
        if (strcmp(passwords[i].website, website) == 0) {
            char label[20];

            printf("Enter label (Social/Email/Banking): ");
            scanf("%s", label);

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
    scanf("%s", website);

    for (int i = 0; i < count; i++) {
        if (strcmp(passwords[i].website, website) == 0) {
            char new_pass[100];

            printf("Enter new password: ");
            scanf("%s", new_pass);

            char encrypted[100];
            encryption(new_pass, encrypted, master_password);

            strcpy(passwords[i].password, encrypted);

            printf("Updated successfully.\n");
            return;
        }
    }

    printf("Website not found.\n");
}

//function to save passwords as encrypted in text form
void save_passwords(struct Password *passwords, int count, char *master_password) {
    FILE *file = fopen("passwords.txt", "w");

    if (file == NULL) {
        printf("Error saving passwords.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        char decrypted[100];
        decryption(passwords[i].password, decrypted, master_password);

        fprintf(file, "%s|%s|%s\n", passwords[i].website, passwords[i].username, decrypted);
    }

    fclose(file);
}
    

// search category (still basic)
void search_by_category(struct Password *passwords, int count) {
    char category[20];

    printf("Enter keyword to search: ");
    scanf("%s", category);

    for (int i = 0; i < count; i++) {
        if (strstr(passwords[i].website, category)) {
            printf("%s | %s\n", passwords[i].website, passwords[i].username);
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
    scanf("%s", master_password);

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
    fscanf(file, "%s", stored);
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

// main
int main() {
    struct Password passwords[100];
    int count = 0;
    char master_password[50];

    set_permanent_master_password(master_password);

    if (!verify_master_password(master_password)) {
        return 1;
    }

    // demo flow (i will replace with menu later)
    add_password(passwords, &count, master_password);
    display_passwords(passwords, count, master_password);

    return 0;
}