# Password Manager (C - CLI)

## goal :

1. create a password manager that can store and retrieve passwords securely
2. use a master password to encrypt and decrypt the stored passwords
3. use a simple command line interface to interact with the program
4. use a .txt file to store encrypted passwords
5. apply a basic encryption algorithm for learning purposes

---

## overview :

this project is a terminal-based password manager written in C

it provides a simple system to store credentials (website, username, password), protect them using a master password, and retrieve them when needed

the focus of this project is on understanding core programming concepts such as file handling, data structures, and basic encryption

---

## features :

* master password authentication
* encryption and decryption using a simple XOR-based method
* persistent storage using file handling
* add new credentials
* search credentials by website
* display all stored credentials
* masked input for sensitive fields
* structured menu-driven interface
* attempt limit for authentication

---

## file structure :

* `passwords.txt`
  stores encrypted credentials in the format:

  ```
  website|username|encrypted_password
  ```

* `master_password.txt`
  stores the master password

---

## build and run :

compile :

```bash id="build01"
gcc main.c -o manager
```

run :

```bash id="run01"
./manager
```

---

## program flow :

1. on first execution, the user sets a master password
2. on subsequent runs, the user must verify the master password
3. once authenticated, the main menu is displayed
4. the user can choose to:

   * add a new password
   * search for an existing password
   * display all stored passwords
   * exit the program (data is saved before exit)

---

## limitations :

* the encryption method is not secure for real-world usage
* the master password is stored in plain text
* input handling is basic and may not support spaces
* storage is limited to 100 entries
* no delete or advanced editing functionality

---

## future improvements :

* implement stronger encryption (e.g., AES)
* hash the master password instead of storing it directly
* support safer input handling (e.g., fgets)
* add delete and update operations
* improve terminal UI and layout
* add password generator and strength checker
* encrypt the entire file instead of individual fields

---

## learning outcomes :

this project helps in understanding:

* structures and memory usage in C
* file handling (read/write operations)
* basic encryption logic
* input/output handling in CLI applications
* modular program design

---

## author :

Eesa
