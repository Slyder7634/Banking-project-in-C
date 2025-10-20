#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <unistd.h>

#include <time.h>

void pause_console()

{

int ch;

while ((ch = getchar()) != '\n' && ch != EOF)

    ;      // flush input

getchar(); // wait for Enter

}

struct statements

{

int acc_no;

char date[20];

char description[100];

float amount;

float balance_after;

};

struct Account

{

int acc_no;

char name[50];

float balance;

char password[20];

};

struct Admin

{

int id;

char name[50];

char password[20];

};

struct Account *users = NULL;

int user_num = 0;

int user_capacity = 0;

int check_password(struct Account *user)

{

char entered_pass[20];

printf("Enter the password for %s: ", user->name);

scanf("%s", entered_pass);



if (strcmp(user->password, entered_pass) == 0)

{

    return 1;

}

else

{

    return 0;

}

}

int check_admin(struct Admin *workers)

{

char entered_pass[20];

printf("Enter the password for %s: ", workers->name);

scanf("%s", entered_pass);



if (strcmp(workers->password, entered_pass) == 0)

{

    return 1;

}

else

{

    printf("Incorrect password.\n");
    return 0;

}

}

struct statements *acc_holder = NULL;

int user_num1 = 0;

int user_capacity1 = 0;

void add_statement_simple(int acc_no, const char *type, float amount, float balance_after)

{

if (user_num1 == user_capacity1)

{

    user_capacity1 = (user_capacity1 == 0) ? 10 : user_capacity1 * 2;

    acc_holder = realloc(acc_holder, user_capacity1 * sizeof(struct statements));

    if (!acc_holder)

    {

        printf("Memory allocation error in add_statement.\n");

        exit(1);

    }

}



// Get today's date

time_t t = time(NULL);

struct tm tm = *localtime(&t);

snprintf(acc_holder[user_num1].date, sizeof(acc_holder[user_num1].date),

         "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);



// Format description like: Deposited ₹500

snprintf(acc_holder[user_num1].description, sizeof(acc_holder[user_num1].description),

         "%s ₹%.2f", type, amount);



acc_holder[user_num1].acc_no = acc_no;

acc_holder[user_num1].amount = amount;

acc_holder[user_num1].balance_after = balance_after;

user_num1++;

}

void delete_user_by_acc(int acc_no) {

int found = 0;



for (int i = 0; i < user_num; i++) {

    if (users[i].acc_no == acc_no) {

        found = 1;



        // Shift remaining users left

        for (int j = i; j < user_num - 1; j++) {

            users[j] = users[j + 1];

        }



        user_num--; // reduce active user count



        // Optional: shrink memory (only if waste matters)

        if (user_num < user_capacity / 2) {

            user_capacity = user_capacity / 2;

            users = realloc(users, user_capacity * sizeof(struct Account));

        }



        printf("Account number %d deleted successfully.\n", acc_no);

        break;

    }

}



if (!found) {

    printf("No account found with account number: %d\n", acc_no);

}

}

int main()

{

// Load users from file

FILE *fp = fopen("../users.txt", "r");

if (!fp)

{

    printf("Failed to open users.txt\n");

    exit(1);

}



while (1)

{

    if (user_num == user_capacity)

    {

        user_capacity = (user_capacity == 0) ? 10 : user_capacity * 2;

        users = realloc(users, user_capacity * sizeof(struct Account));

        if (!users)

        {

            printf("Memory allocation error.\n");

            exit(1);

        }

    }



    int acc;

    char name[50], pass[20];

    float bal;



    int read = fscanf(fp, "%d %s %f %s", &acc, name, &bal, pass);

    if (read != 4)

        break;



    users[user_num].acc_no = acc;

    strcpy(users[user_num].name, name);

    users[user_num].balance = bal;

    strcpy(users[user_num].password, pass);

    user_num++;

}

fclose(fp);



// statement struct

FILE *fp_stmt = fopen("../statements.txt", "r");

if (!fp_stmt)

{

    printf("Failed to open statements.txt\n");

    exit(1);

}



char line[256];

while (fgets(line, sizeof(line), fp_stmt))

{

    if (user_num1 == user_capacity1)

    {user_capacity1 = (user_capacity1 == 0) ? 10 : user_capacity1 * 2;

        acc_holder = realloc(acc_holder, user_capacity1 * sizeof(struct statements));

        if (!acc_holder)

        {

            printf("Memory allocation error.\n");

            exit(1);

        }

    }



    int acc;

    char date[20], desc[100];

    float amount, balance_after;



    // Using sscanf to parse the line

    int parsed = sscanf(line, "%d %19s \"%99[^\"]\" %f %f", &acc, date, desc, &amount, &balance_after);

    if (parsed != 5)

    {

        printf("Skipping malformed line: %s", line);

        continue;

    }



    acc_holder[user_num1].acc_no = acc;

    strcpy(acc_holder[user_num1].date, date);

    strcpy(acc_holder[user_num1].description, desc);

    acc_holder[user_num1].amount = amount;

    acc_holder[user_num1].balance_after = balance_after;

    user_num1++;

}



fclose(fp_stmt);



// admin struct

struct Admin workers[5] = {

    {1001, "Ankit", "7634"},

    {1002, "Slyder", "7634"},

    {1003, "Ankur", "7634"},

    {1004, "Jazzy", "7634"},

    {1005, "Abhijeet", "7634"},

};



char login_type[10];

int user_acc, option, admin_id;

start:

printf("==================================\n");

printf("         BANKING SYSTEM           \n");

printf("==================================\n\n");



printf("Login as\nAdmin or User :: ");

fgets(login_type, sizeof(login_type), stdin);

login_type[strcspn(login_type, "\n")] = '\0';



if (strcasecmp(login_type, "User") == 0)

{

    printf("Enter account number: ");

    scanf("%d", &user_acc);

    while (1)

    {

        int found = 0;

        for (int i = 0; i < user_num; i++)

        {

            if (users[i].acc_no == user_acc)

            {

                found = 1;

                if ((check_password(&users[i]))==1)

                {

                Menu:

                    system("cls");

                    printf("\nWelcome, %s!\n\n", users[i].name);

                    printf("=== User Menu ===\n\n");

                    printf("1. Check account Balance\n");

                    printf("2. Open new bank account\n");

                    printf("3. Deposit money\n");

                    printf("4. Withdraw money\n");

                    printf("5. Transfer money\n");

                    printf("6. Statement generation\n");

                    printf("7. Check account information\n");

                    printf("8. Update information\n");

                    printf("9. Exit to login\n");



                    printf("\nEnter option: ");

                    scanf("%d", &option);

                    getchar();

                    if (option == 9)

                    {

                        system("cls");

                        goto start;

                    }



                    if (option == 1)

                    {

                        system("cls");

                        printf("==================================\n");

                        printf("         CHECK BALANCE           \n");

                        printf("==================================\n\n");



                        printf("Your balance is: ₹%.2f\n", users[i].balance);

                    }

                    if (option == 3)

                    {

                        system("cls");

                        printf("==================================\n");

                        printf("         DEPOSIT MONEY           \n");

                        printf("==================================\n\n");



                        int b = 0;

                        printf("Enter amount to deposit: ");

                        scanf("%d", &b);

                        users[i].balance += b;

                        printf("%d deposited successfully!\n", b);

                        printf("Updated balance: ₹%.2f\n", users[i].balance);

                        add_statement_simple(users[i].acc_no, "Deposited", b, users[i].balance);

                    }

                    if (option == 4)

                    {system("cls");

                        printf("==================================\n");

                        printf("         WITHDRAW MONEY           \n");

                        printf("==================================\n\n");



                        int b = 0;

                        printf("Enter amount to Withdraw : ");

                        scanf("%d", &b);

                        if (b <= users[i].balance)

                        {

                            users[i].balance -= b;

                            printf("%d ₹Withdraw successfully!\n", b);

                            printf("Updated balance: ₹%.2f\n", users[i].balance);

                            add_statement_simple(users[i].acc_no, "Withdrawn", b, users[i].balance);

                        }

                        else

                        {

                            printf("Insufficient balance.\n");

                        }

                    }

                    if (option == 5)

                    {

                        system("cls");

                        printf("==================================\n");

                        printf("         TRANSFER MONEY           \n");

                        printf("==================================\n\n");



                        int b = 0, acc_to = 0, target_found = 0;

                        printf("Enter account number to transfer to: ");

                        scanf("%d", &acc_to);

                        printf("Enter amount to Transfer: ");

                        scanf("%d", &b);



                        if (b <= users[i].balance)

                        {

                            for (int j = 0; j < user_num; j++)

                            {

                                if (users[j].acc_no == acc_to)

                                {

                                    users[i].balance -= b;

                                    users[j].balance += b;

                                    target_found = 1;

                                    printf("₹%d transferred successfully to %s.\n", b, users[j].name);

                                    printf("Your updated balance: ₹%.2f\n", users[i].balance);

                                    add_statement_simple(users[i].acc_no, "Transferred", b, users[i].balance);

                                    add_statement_simple(users[j].acc_no, "Received", b, users[j].balance);



                                    break;

                                }

                            }

                            if (!target_found)

                            {

                                printf("Recipient account not found.\n");

                            }

                        }

                        else

                        {

                            printf("Insufficient balance.\n");

                        }

                    }

                    if (option == 2)

                    {

                        system("cls");

                        char confirm[2], nam[50], pass[20];

                        float new_bal;



                        printf("==================================\n");

                        printf("         NEW ACCOUNT           \n");

                        printf("==================================\n\n");



                        printf("Type Y to continue or N to cancel: ");

                        scanf("%s", confirm);



                        if (strcasecmp(confirm, "Y") == 0)

                        {

                            if (user_num == user_capacity)

                            {

                                user_capacity = (user_capacity == 0) ? 2 : user_capacity * 2;

                                users = realloc(users, user_capacity * sizeof(struct Account));

                            }



                            printf("Enter name: ");

                            scanf("%s", nam);

                            printf("withdraw initial balance: ");scanf("%f", &new_bal);

                            printf("Set password: ");

                            scanf("%s", pass);



                            users[user_num].acc_no = 1000 + user_num;

                            strcpy(users[user_num].name, nam);

                            users[user_num].balance = new_bal;

                            strcpy(users[user_num].password, pass);

                            user_num++;



                            printf("Account created successfully!\n");

                        }

                        else

                        {

                            printf("Cancelled.\n");

                        }

                    }

                    if (option == 7)

                    {

                        system("cls");

                        printf("==================================\n");

                        printf("         ACCOUNT INFO           \n");

                        printf("==================================\n\n");



                        printf("ACCOUNT NUMBER                  ACC HOLDER NAME                  BALANCE\n");

                        printf("%d                              %s                           %.2f\n", users[i].acc_no, users[i].name, users[i].balance);

                    }

                    if (option == 8)

                    {

                        int y;

                        char z[50];

                        system("cls");



                        printf("==================================\n");

                        printf("         UPDATE INFO           \n");

                        printf("==================================\n\n");



                        printf("What do you want to update?\n\n1. Account holder name\n2. Password\n");

                        printf("Enter option: ");

                        scanf("%d", &y);

                        getchar();



                        if (y == 1)

                        {

                            system("cls");

                            printf("==================================\n");

                            printf("         UPDATE NAME           \n");

                            printf("==================================\n\n");



                            printf("\nCurrent name: %s\n", users[i].name);



                            printf("Enter new name: ");

                            fgets(z, sizeof(z), stdin);

                            z[strcspn(z, "\n")] = 0;



                            if (check_password(&users[i]))

                            {

                                strcpy(users[i].name, z);

                                printf("\nYour name has been successfully updated to: %s\n", users[i].name);

                            }

                            else

                            {

                                printf("Password verification failed.\n");

                            }

                        }



                        if (y == 2)

                        {

                            char xy[20];

                            printf("==================================\n");

                            printf("         CHANGE PASSWORD           \n");

                            printf("==================================\n\n");



                            printf("Please verify yourself!\n");



                            if (check_password(&users[i]))

                            {

                                printf("Enter new password: ");

                                fgets(xy, sizeof(xy), stdin);

                                xy[strcspn(xy, "\n")] = 0;



                                strcpy(users[i].password, xy);

                                system("cls");

                                printf("PASSWORD UPDATED SUCCESSFULLY!!\n\nPlease Login Again...");

                                goto start;

                            }

                            else

                            {printf("Password verification failed.\n");

                            }

                        }

                    }

                    if (option == 6)

                    {

                        system("cls");

                        printf("==================================\n");

                        printf("         MINI STATEMENT           \n");

                        printf("==================================\n\n");



                        printf("Showing statement for acc_no: %d\n", users[i].acc_no);



                        int found = 0;

                        for (int k = 0; k < user_num1; k++)

                        {

                            printf("Checking acc_holder[%d].acc_no = %d\n", k, acc_holder[k].acc_no); // Debug

                            if (acc_holder[k].acc_no == users[i].acc_no)

                            {

                                printf("%s | %s | ₹%.2f | Balance after: ₹%.2f\n",

                                       acc_holder[k].date,

                                       acc_holder[k].description,

                                       acc_holder[k].amount,

                                       acc_holder[k].balance_after);

                                found = 1;

                            }

                        }

                        if (!found)

                        {

                            printf("No transaction history found for this account.\n");

                        }

                    }

                    break;

                }
                else{
                    
                    printf("Incorrect password.\n");
                    goto end;
                }

            }

        }

        if (!found)

        {

            printf("\nAccount not found!\n");

            break;

        }

        printf("\n\nPress Enter to go back to menu !!");
        if(option==1){
            getchar();
        }
        else{
            pause_console();
        }

        goto Menu;

    }

}
else if (strcasecmp(login_type, "Admin") == 0)
{
while (1)
{
printf("Enter Admin ID: ");
scanf("%d", &admin_id);

int found = 0;    
    for (int i = 0; i < 5; i++)    
    {    
        if (workers[i].id == admin_id)    
        {    
            found = 1;    
            if ((check_admin(&workers[i]))==1)    
            {    
                while (1)    
                {    
                options:    
                    printf("\nWelcome, %s!\n\n", workers[i].name);    
                    printf("=== Admin Menu ===\n\n");    
                    printf("1. View all accounts\n");    
                    printf("2. Search for an account\n");    
                    printf("3. create new account\n");    
                    printf("4. Close/Delete an account\n");    
                    printf("5. View all transactions\n");    
                    printf("6. Generate detailed customer report\n");    
                    printf("7. Modify customer account balance\n");    
                    printf("8. Update customer information\n");    
                    printf("9. Manage admin users\n");    
                    printf("10. System logs & security checks\n");    
                    printf("11. Exit\n");    

                    printf("\nEnter option: ");    
                    scanf("%d", &option);    
                    getchar(); // flush newline    
                    if (option >= 1 && option <= 11)    
                    {    
                        if (option == 1)    
                        {    
                            system("cls");    
                            printf("ACCOUNT NUMBER                  ACC HOLDER NAME                  BALANCE\n");    
                            for (int i = 0; i < user_num; i++)    
                            {    
                                printf("%d                              %s                           %.2f\n", users[i].acc_no, users[i].name, users[i].balance);    
                            }    
                        }    

                        if (option == 2)    
                        {    
                            system("cls");    
                            printf("Choose search type");    
                            printf("\n1. Search by account number\n2. Search by name\n3. Search by Balance\n4.Go back\n");    
                            int choice, num1 = 0, acc = -1;    
                            scanf("%d", &choice);    

                            if (choice == 1)    
                            {    
                                printf("Enter account number: ");    
                                scanf("%d", &user_acc);    
                                for (int i = 0; i < user_num; i++)    
                                {    
                                    if (users[i].acc_no == user_acc)    
                                    {    
                                        num1++;    
                                        acc = i;    
                                    }    
                                }    

                                if (acc != -1)    
                                {    
                                    printf("ACCOUNT NUMBER                  ACC HOLDER NAME                  BALANCE\n");    
                                    printf("%d                              %s                           %.2f\n", users[acc].acc_no, users[acc].name, users[acc].balance);    
                                }    
                                else    
                                {    
                                    printf("No account found.\n\n");    
                                }    
                                printf("\n\n%d account holder(s) found", num1);    
                            }else if (choice == 3)    
                            {    
                                int user_bal;    
                                printf("Enter balance : ");    
                                scanf("%d", &user_bal);    
                                printf("ACCOUNT NUMBER                  ACC HOLDER NAME                  BALANCE\n");    
                                for (int i = 0; i < user_num; i++)    
                                {    
                                    if (users[i].balance == user_bal)    
                                    {    
                                        acc = i;    
                                        printf("%d                              %s                           %.2f\n", users[acc].acc_no, users[acc].name, users[acc].balance);    
                                        num1++;    
                                    }    
                                }    
                                printf("\n\n%d account holder(s) found", num1);    
                            }    

                            else if (choice == 2)    
                            {    
                                char entered_name[50];    
                                printf("Enter the name: ");    
                                scanf("%s", entered_name);    
                                printf("ACCOUNT NUMBER                  ACC HOLDER NAME                  BALANCE\n");    
                                for (int i = 0; i < user_num; i++)    
                                {    
                                    if (strcasecmp(users[i].name, entered_name) == 0)    
                                    {    
                                        acc = i;    
                                        printf("%d                              %s                           %.2f\n", users[acc].acc_no, users[acc].name, users[acc].balance);    
                                        num1++;    
                                    }    
                                }    
                                if (num1 == 0)    
                                {    
                                    printf("No account found.\n");    
                                }    
                                printf("\n\n%d account holder(s) found", num1);    
                            }    
                            else if (choice == 4)    
                            {    
                                system("cls");    
                                goto options;    
                            }    
                        }    
                        if (option == 3)    
                        {    
                            system("cls");    
                            char confirm[2], nam[50], pass[20];    
                            float new_bal;    

                            printf("==================================\n");    
                            printf("         NEW ACCOUNT           \n");    
                            printf("==================================\n\n");    

                            printf("Type Y to continue or N to cancel: ");    
                            scanf("%s", confirm);    

                            if (strcasecmp(confirm, "Y") == 0)    
                            {    
                                if (user_num == user_capacity)    
                                {    
                                    user_capacity = (user_capacity == 0) ? 2 : user_capacity * 2;    
                                    users = realloc(users, user_capacity * sizeof(struct Account));    
                                }    

                                printf("Enter name: ");    
                                scanf("%s", nam);    
                                printf("withdraw initial balance: ");    
                                scanf("%f", &new_bal);    
                                printf("Set password: ");    
                                scanf("%s", pass);users[user_num].acc_no = 1000 + user_num;    
                                strcpy(users[user_num].name, nam);    
                                users[user_num].balance = new_bal;    
                                strcpy(users[user_num].password, pass);    
                                user_num++;    

                                printf("Account created successfully!\n");    
                            }    
                            else    
                            {    
                                printf("Cancelled.\n");    
                            }    
                        }    
                        if (option == 6)    
                        {    
                            system("cls");    
                            printf("==================================\n");    
                            printf("         USER DETAILS           \n");    
                            printf("==================================\n\n");    

                            printf("Showing Details for acc_no: %d\n", users[i].acc_no);    

                            int found = 0;    
                            for (int k = 0; k < user_num1; k++)    
                            {    
                                printf("Checking acc_holder[%d].acc_no = %d\n", k, acc_holder[k].acc_no); // Debug    
                                printf("Date Desc Amm. balance");    
                                if (acc_holder[k].acc_no == users[i].acc_no)    
                                {    
                                    printf("%s | %s | ₹%.2f | Balance after: ₹%.2f\n",    
                                           acc_holder[k].date,    
                                           acc_holder[k].description,    
                                           acc_holder[k].amount,    
                                           acc_holder[k].balance_after);    
                                    found = 1;    
                                }    
                            }    
                            if (!found)    
                            {    
                                printf("No transaction history found for this account.\n");    
                            }    
                        }    
                        if (option == 5)    
                        {    
                            system("cls");    
                            printf("==================================\n");    
                            printf("         ALL TRANSACTIONS           \n");    
                            printf("==================================\n\n");    

                            for (int k = 0; k < user_num1; k++)    
                            {    
                                printf("%s | %s | ₹%.2f | Balance after: ₹%.2f\n",    
                                       acc_holder[k].date,    
                                       acc_holder[k].description,    
                                       acc_holder[k].amount,    
                                       acc_holder[k].balance_after);    
                            }    
                        }    
                        if (option == 8)    
                        {    
                            int y;    
                            char z[50];    
                            system("cls");    

                            printf("==================================\n");    
                            printf("         UPDATE INFO           \n");    
                            printf("==================================\n\n");    

                            printf("What do you want to update?\n\n1. Account holder name\n2. Password\n");    
                            printf("Enter option: ");    
                            scanf("%d", &y);    
                            getchar();if (y == 1)    
                            {    
                                system("cls");    
                                printf("==================================\n");    
                                printf("         UPDATE NAME           \n");    
                                printf("==================================\n\n");    

                                printf("\nCurrent name: %s\n", users[i].name);    

                                printf("Enter new name: ");    
                                fgets(z, sizeof(z), stdin);    
                                z[strcspn(z, "\n")] = 0;    

                                strcpy(users[i].name, z);    
                                printf("\nYour name has been successfully updated to: %s\n", users[i].name);      
                            }    

                            if (y == 2)    
                            {    
                                char xy[20];    
                                printf("==================================\n");    
                                printf("         CHANGE PASSWORD           \n");    
                                printf("==================================\n\n");    

                                printf("Please Enter user,s previous password !\n");    

                                if (check_password(&users[i]))    
                                {    
                                    printf("Enter new password: ");    
                                    fgets(xy, sizeof(xy), stdin);    
                                    xy[strcspn(xy, "\n")] = 0;    

                                    strcpy(users[i].password, xy);    
                                    system("cls");    
                                    printf("PASSWORD UPDATED SUCCESSFULLY!!\n\n");    
                                    goto start;    
                                }    
                                else    
                                {    
                                    printf("Password verification failed.\n");    
                                }    
                            }    
                        }    

                        if (option == 11)    
                        {    
                            system("cls");    
                            goto start;    
                        }    
                    }    
                    else    
                    {    
                        printf("Choose correct option mentioned above !!\n");    
                    }    

                    printf("\nPress Enter to continue...");    
                    getchar();    
                    system("cls");    
                }    
            }
            else{
                    
                    printf("Incorrect password.\n");
                    goto end;
            }    
            goto end;    
        }    
    }    

    if (!found)    
    {    
        system("cls");    
        printf("Admin ID not found.\n");    
        pause_console();    
        goto start;    
    }    
}

}

else
{
printf("Invalid login type. Please enter 'Admin' or 'User'.\n");
}

end:

goto save;

save:
{
FILE *out = fopen("../users.txt", "w");
for (int i = 0; i < user_num; i++)
{
fprintf(out, "%d %s %.2f %s\n", users[i].acc_no, users[i].name, users[i].balance, users[i].password);
}
fclose(out);
}

goto hie;

hie:
{
FILE *save_fp = fopen("../statements.txt", "a");
if (!save_fp)
{
printf("Failed to save statements to file.\n");
exit(1);
}

for (int i = 0; i < user_num1; i++)
{
fprintf(save_fp, "%d %s \"%s\" %.2f %.2f\n",
acc_holder[i].acc_no,
acc_holder[i].date,
acc_holder[i].description,
acc_holder[i].amount,
acc_holder[i].balance_after);
}

fclose(save_fp);

}

free(users);
printf("\nThank you for using the Banking System!\n");
return 0;

}