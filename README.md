# Password Manager (C - CLI)

## goal :

1. create a password manager that can store and retrieve passwords securely
2. use a master password to encrypt and decrypt stored data
3. build a clean command line interface for interaction
4. store data in a text file format
5. implement a simple encryption method for learning

---

## overview :

this is a terminal-based password manager written in C

the idea is simple: store credentials safely, lock them behind a master password, and only reveal them when needed

it’s not trying to be industry-level secure — it’s built to understand how systems like this actually work under the hood

---

## architecture :

the program is structured into clear parts:

* `struct Password`
  stores website, username, and encrypted password

* encryption logic
  handles converting plain text into encrypted form and back

* file system
  saves and loads data from text files

* CLI layer
  handles all user interaction through a menu

---

## features :

* master password setup and verification
* XOR-based encryption and decryption
* file-based storage (persistent data)
* add new credentials
* search credentials by website
* display all stored credentials
* masked input for passwords
* menu-driven interface
* limited login attempts

---

## data format :

stored in `passwords.txt` like this:

```id="fmt01"
website|username|encrypted_password
```

simple, readable, and easy to parse

---

## build and run :

compile :

```bash id="cmd01"
gcc main.c -o manager
```

run :

```bash id="cmd02"
./manager
```

---

## flow :

1. first run → set a master password
2. next runs → verify it
3. after login → menu shows up
4. choose what you want to do:

   * add password
   * search password
   * display all
   * exit (auto saves)

---

## design choices :

* fixed-size arrays → simple and predictable
* text files → easy to debug and inspect
* XOR encryption → lightweight and good for learning
* modular functions → cleaner code structure

---

## limitations :

* encryption is basic (not secure for real-world use)
* master password is stored in plain text
* input does not support spaces
* no delete or edit functionality yet
* max 100 stored entries

---

## future improvements :

* stronger encryption (AES or similar)
* hash the master password
* better input handling (fgets)
* add delete and update features
* improve UI/UX in terminal
* password generator + strength checker
* encrypt full file instead of fields

---

## learning focus :

this project helps you understand:

* how data is structured and stored
* how file handling works in C
* how basic encryption works
* how CLI tools are designed
* how to break code into clean modules

---

## author :

Eesa
