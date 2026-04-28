# passman
#  Password Manager (C - CLI)

## goal :

1. create a password manager that can store and retrieve passwords securely
2. use a master password to encrypt and decrypt the stored passwords
3. use a simple command line interface to interact with the password manager
4. use .txt format to store the encrypted passwords
5. use a simple encryption algorithm to encrypt the passwords

---

##  overview :

this is a simple command line based password manager written in C

it lets you:

* store passwords
* encrypt them using a master password
* search and display them
* save/load from a file

everything runs in terminal with a clean menu UI

---

##  features :

*  master password protection
*  encryption + decryption (XOR based)
*  save + load passwords from file
*  search passwords by website
*  display all stored passwords
*  masked password input (no plain typing visible)
*  clean CLI menu with box UI
*  attempt limit (data deleted after too many wrong tries)

---

## files used :

* `passwords.txt` → stores encrypted passwords
* `master_password.txt` → stores master password

---

##  how to run :

### compile :

```bash
gcc main.c -o manager
```

### run :

```bash
./manager
```

---

##  how it works :

1. first time → you set a master password
2. next runs → you must verify it
3. after login → menu appears
4. choose options:

   * add password
   * search password
   * display all
   * exit (auto saves)

---

##  limitations :

* encryption is basic (XOR) → not secure for real-world use
* master password is stored in plain text
* no delete/edit UI yet
* uses fixed size storage (100 entries max)

---

##  future improvements :

* stronger encryption (AES)
* hash master password instead of storing directly
* add delete + update features
* better UI (colors / animations)
* password generator
* file encryption instead of plain text

---

##  note :

this project is made for learning purpose
focus is on understanding:

* file handling
* structs
* encryption basics
* CLI design

---

##  author :

made by Eesa
grade 9 dev on the grind 

---
