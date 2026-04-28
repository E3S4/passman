# Password Manager (C - CLI)

## goal :

1. create a password manager that can store and retrieve passwords securely
2. use a master password to encrypt and decrypt the stored passwords
3. use a simple command line interface to interact with the password manager
4. use .txt format to store the encrypted passwords
5. use a simple encryption algorithm to encrypt the passwords

---

## overview :

this is a command line based password manager written in C

it allows you to store, search, and display passwords while keeping them encrypted using a master password

the program uses file handling to save and load data and provides a structured menu interface in the terminal

---

## features :

* master password protection
* encryption and decryption (XOR based)
* save and load passwords from file
* search passwords by website
* display all stored passwords
* masked password input
* structured CLI menu interface
* limited login attempts with data reset

---

## files used :

* passwords.txt → stores encrypted passwords
* master_password.txt → stores master password

---

## how to run :

compile :

```bash
gcc main.c -o manager
```

run :

```bash
./manager
```

---

## how it works :

1. on first run, user sets a master password
2. on next runs, user must verify the master password
3. after successful login, menu is displayed
4. user can:

   * add password
   * search password
   * display all passwords
   * exit (data is saved automatically)

---

## limitations :

* encryption method is basic and not secure for real-world use
* master password is stored in plain text
* no delete or edit functionality
* fixed storage limit (100 entries)

---

## future improvements :

* implement stronger encryption
* hash the master password
* add delete and update features
* improve user interface
* add password generator
* encrypt entire file instead of storing plain text

---

## note :

this project is built for learning purposes and focuses on:

* file handling
* structures in C
* basic encryption concepts
* command line interface design

---

## author :

Eesa
