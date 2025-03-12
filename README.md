
# ATM Management System with SQLite Database

This project implements an ATM management system in C where users can perform various actions related to their accounts. It uses SQLite as a database to store user and account information instead of traditional text files. The system allows users to register, log in, view and update their account details, make transactions, transfer ownership, and more.

## Features

### 1. User Registration and Login
- Register new users with unique names (names must be unique).
- Log in with existing user credentials.
- Store user information in the SQLite database.

### 2. Account Management
- **View Account Details**: Users can view account information by providing the account ID.
  - Accounts can be of type: savings, fixed01, fixed02, fixed03, or current.
  - Interest rates are calculated for savings and fixed accounts.
- **Update Account Information**: Users can update their country or phone number associated with an account.
  - The update is saved into the database after modification.
  
### 3. Transactions
- Users can perform **deposits** and **withdrawals** to their accounts.
  - Fixed accounts (fixed01, fixed02, fixed03) do not support transactions.

### 4. Account Removal
- Users can **remove their own accounts** from the system.
  
### 5. Transfer Ownership
- Users can transfer ownership of their accounts to another user, updating the database accordingly.

### 6. Bonus Features (Optional)
- **User Notifications**: When an account ownership is transferred, the recipient user gets an instant notification (using pipes and child processes).
- **Encryption of Passwords**: Implement encryption for storing and verifying user passwords.
- **Relational Database**: All user and account data is stored in an SQLite database instead of text files.
- **Improved User Interface**: Enhancements to the terminal interface for better user experience.

## Project Structure

```
.
├── atm-system
├── data
│   ├── atm.db
│   └── sakila.db
├── Makefile
├── obj
│   ├── authAndReg.d
│   ├── authAndReg.o
│   ├── dataBaseTools.d
│   ├── dataBaseTools.o
│   ├── helpers.d
│   ├── helpers.o
│   ├── main.d
│   ├── main.o
│   ├── menus.d
│   ├── menus.o
│   ├── system.d
│   ├── system.o
│   ├── tools.d
│   └── tools.o
├── README.md
├── src
│   ├── authAndReg.c
│   ├── dataBaseTools.c
│   ├── errors.h
│   ├── header.h
│   ├── helpers.c
│   ├── main.c
│   ├── menus.c
│   ├── SQLiteQueries.h
│   ├── system.c
│   └── tools.c
└── todo
```

## Database Schema

The project uses an SQLite database with the following schema:

1. **users**: Stores user information.
   - `id` INTEGER PRIMARY KEY
   - `name` TEXT
   - `password` TEXT

2. **accounts**: Stores account details for each user.
   - `id` INTEGER PRIMARY KEY
   - `user_id` INTEGER (foreign key referencing `users(id)`)
   - `account_name` TEXT
   - `account_id` INTEGER
   - `date_created` TEXT
   - `country` TEXT
   - `phone_number` TEXT
   - `balance` REAL
   - `account_type` TEXT (current, savings, fixed01, fixed02, fixed03)

## Installation

1. Clone this repository to your local machine.

    ```bash
    git clone https://github.com/yourusername/atm-management-system.git
    cd atm-management-system
    ```

2. Install SQLite development libraries (if not already installed).

    On Ubuntu/Debian:

    ```bash
    sudo apt-get install libsqlite3-dev
    ```

    On macOS:

    ```bash
    brew install sqlite
    ```

3. Compile the program using the Makefile.

    ```bash
    make
    ```

4. Run the application.

    ```bash
    ./atm
    ```

## Usage

### 1. Register a new user:
- Upon launching the application, users are prompted to register by entering their name and password.

### 2. Log in:
- Users can log in by providing their name and password.

### 3. Manage Accounts:
- View account details by entering the account ID.
- Update account information (country or phone number) by providing the account ID and the field to update.
- Transfer ownership of an account to another user.

### 4. Make Transactions:
- Deposit or withdraw money from supported accounts.
- Fixed accounts (fixed01, fixed02, fixed03) do not support transactions.

### 5. Account Removal:
- Users can remove their accounts by entering the account ID.

## Contributing

Feel free to fork the repository and make improvements or bug fixes. If you want to contribute, please make sure to:

- Fork the repository.
- Create a new branch (`git checkout -b feature/your-feature-name`).
- Make your changes.
- Commit your changes (`git commit -am 'Add feature'`).
- Push to the branch (`git push origin feature/your-feature-name`).
- Create a new Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.