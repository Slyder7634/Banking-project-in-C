🏦 Banking System in C

A complete console-based banking management system built in C language, demonstrating core programming, file handling, and user authentication concepts.
This project simulates real-world banking operations such as account creation, deposits, withdrawals, balance checks, and secure user logins.

🚀 Features

✅ User Accounts

Create new bank accounts with name, number, and password.

Secure login using password verification.

✅ Transactions

Deposit or withdraw money from accounts.

Check account balance and transaction history.

✅ Admin Panel

View, search, and manage all customer accounts.

Reset passwords or delete inactive users.

Generate transaction and balance reports.

✅ File Handling (Persistence)

All user and transaction data is saved in files (using C file I/O).

Data remains persistent even after the program is closed.

✅ Security

Passwords are hashed or encoded using a custom encoding logic (will add later).

Prevents unauthorized access and invalid operations.

🧱 Tech Stack
Component	Description
Language	C (Standard C99)
Compiler	GCC / MinGW / Turbo C
Concepts Used	File I/O, Structures, Loops, Functions, Pointers
IDE (Optional)	VS Code / Code::Blocks / Dev-C++


⚙️ How to Run
🧩 Option 1: Using GCC
gcc main.c -o banking
./banking

🧩 Option 2: Using Code::Blocks or VS Code

Open the project folder.

Compile and run main.c.

Follow the on-screen menu.

🧮 Example Workflow
Welcome to Banking System
1. Create Account
2. Login
3. Admin Login
Enter choice: 1

Enter name: Abhijeet
Set password: ****
Initial deposit: 1000
✅ Account created successfully!

(After login)
1. Deposit
2. Withdraw
3. Check Balance
4. Logout

📊 Data Storage Example

Data is stored in plain text or binary format using file I/O.
Example (accounts.txt):

1001, Abhijeet, 3500.00, password
1002, Riya, 8200.50, password

🧠 Concepts Demonstrated

Structured programming in C

Modular design and function reusability

File handling and data persistence

Password verification and security logic

Admin/user role separation

Dynamic memory management (malloc, realloc)

🏗️ Future Enhancements

🚧 Planned features to make it even stronger:

Add encryption for password storage

Implement transaction logs with timestamps

Create a GUI version using C++ or Python

Add bank interest or loan modules

Migrate to SQL database for scalability

📜 License

This project is open-source and available under the MIT License — free to modify and distribute.



- Abhijeet Sharmma
👨‍💻 BCA Student 
