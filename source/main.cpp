#include <iostream>
#include <windows.h>
#include <limits>    // Include for numeric_limits
#include <fstream>   // to use file handling
#include <iomanip>   // to manipulate onput and output for a better looking (Ex: tables)
#include <vector>    // to use vector data structure
#include <sstream>   // to use flexible string data retreival and searches on data reciewing from the file
#include <algorithm> // to use remove_if() function
#include <ctime>     // To get current time
using namespace std;

//! -- All Function Declaration Goes here
struct UserData
{
    string firstName;
    string lastName;
    string dateOfBirth;
    string nationalIdNumber;
    string username;
    string password;
};
struct transactionData
{
    string username;
    string purpose;
    string ammount;
    string type;
    string who;
    string dateTime;
};

// a sub main function for development and testing perposes
void subMain();

// Login Screen - 1
int loginScreen(int from);

// Home Screen - 2
int homeScreen(int from);

// create new account - 3
int createNewAccount(int from);
// create new account components
bool isStrongPassword(const string &password);
// Function to check if username exists in the file
bool usernameExists(const string &username);
// Read user data from file
vector<UserData> readUserDataFromFile();
// read transactions from file
vector<transactionData> readTransactionDataFromFile(string username);
// Check Balance - 4
int balanceInquiry(int from); // gives the output for balance inquiry
// returns the balance of a user
float balance(string username);
// deposite cash - 5

// to get the current time
string currentTime();
int depositeCash(int from);
// check if username is valid and ask the username 2 times for confirmation
string confirmTransactionUsername(string type);
// withdraw cash - 6
int withdrawCash(int from);

// fund transfer - 7
int fundTransfer(int from);

// transaction history - 8
int transactionHistory(int from);

// account deactivation - 9
int accountDeactivation(int from);

// Login screen components
string takePassword(); // function to take password without exposing
int verifyLogin();     // to verify username and password are correct
int quitContinue();    // function for asking user if they want to continue or quit

// logo print
void logoPrint();

// Home Screen Components
void optionDisplay(); // To display the options in the home screen
int primaryOption();  // To taek user input of which option they want to select

//! -- Main Function

//? main - 0
int main()
{
    subMain();
    // vector<transactionData> transactions = readTransactionDataFromFile("kamal");
    // for (const transactionData &transaction : transactions)
    // {
    //     cout << "type : " << transaction.type << endl;
    //     cout << "ammount : " << transaction.ammount << endl;
    // }
    // Access user data using a loop or by index
    // vector<UserData> users = readUserDataFromFile();
    // for (const UserData &user : users)
    // {
    //     cout << "First Name: " << user.firstName << endl;
    //     cout << "Last Name: " << user.lastName << endl;
    //     // ... and so on for other fields
    //     cout << endl;
    // }
    return 0;
}
// Using this submain for all the real app callings.
// so in the developing phase we can just call this function if we want to
// run the actual program and without calling this we can just call other functions to test
// a perticular part in the code
void subMain()
{
    system("cls"); // cearing the cmd for a clean look
    logoPrint();
    loginScreen(0);
}

//! -- All other function initializations goes here

void logoPrint()
{
    string fileName = "./logo.txt";
    string line = "";
    ifstream inFile;

    if (inFile.is_open())
    {
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
    }
    else
    {
        cout << "Welcome to Command-Line Cash!" << endl;
    }
    inFile.close();
}

//? Login Screen - 1
int loginScreen(int from)
{
    // system("cls"); // clear the screen

    // checking if retured value is 0
    // if it is not 0 telling error message and
    // asking username and password again
    int verifyLoginHold = 1;

    while (verifyLoginHold != 0)
    {
        // if the user is rederected to login page from the home screen using logout button
        // before asking to login, asking him if we want to continue or exit.
        if (from == 2)
        {
            int quitCon = 2;

            while (true)
            {
                quitCon = quitContinue();
                // Discard a part of input beign in the buffer including newline
                // in order to this to work we have to include <limits> header file
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (quitCon == 0 || quitCon == 1)
                {
                    break;
                }
            }
            if (quitCon == 1)
            {
                break;
            }
        }

        // checking the value returned from the verification and
        // sending to homescreen or asking username password again
        verifyLoginHold = verifyLogin();
        if (verifyLoginHold == 0)
        {
            homeScreen(1);
        }
        else
        {
            cout << "Your username or Password is incorrect!" << endl;
        }
        from = 0;
    }

    return 1;
}
//* Login screen Components
// function for asking user if they want to continue or quit
int quitContinue()
{
    // taking character input from user
    char quitCon;
    cout << "Do you want to continue? (C - Continue/ Q - Quit) - ";
    cin >> quitCon;
    // if user input is c or C return 0
    if (quitCon == 'c' || quitCon == 'C')
    {
        return 0;
    }
    // if user input is q or Q return 1
    else if (quitCon == 'q' || quitCon == 'Q')
    {
        return 1;
    }
    // anything else will return 2
    else
    {
        return 2;
    }
}

string takePassword()
{
    HANDLE hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;

    // Create a restore point Mode
    // is know 503
    GetConsoleMode(hStdInput, &mode);

    // Enable echo input
    // set to 499
    SetConsoleMode(
        hStdInput,
        mode & (~ENABLE_ECHO_INPUT));

    // Take input
    string ipt;
    cout << "Enter Password - ";
    getline(cin, ipt);

    // Otherwise next cout will print
    // into the same line
    cout << endl;

    // Restore the mode
    SetConsoleMode(hStdInput, mode);

    return ipt;
}

// to take username and password from user and
// verify if username and password are correct

int verifyLogin()
{
    // fixed username and password
    static string username = "group6", password = "group6@123";
    string gotUsername, gotPassword;

    // getting username from user

    cout << "Enter username - ";
    getline(cin, gotUsername);
    // getting password from user
    gotPassword = takePassword();

    // verifying if the username and password is correct
    if (username == gotUsername && password == gotPassword)
    {
        // if usrname and password is correct returning 0
        return 0;
    }
    else
    {
        // if it is wrong returning 1
        return 1;
    }
}
//? Home Screen - 2
int homeScreen(int from)
{
    system("cls");
    // Primary operation will be repeated until user enters 7 to logout

    int primaryOptionHold = 0;
    do
    {
        // clearing the screen
        system("cls");
        // to diplay the avalable options
        optionDisplay();
        cout << endl;
        primaryOptionHold = primaryOption();
        // calling curespoding function acording to the user's call
        if (primaryOptionHold == 1)
        {
            createNewAccount(2);
        }
        else if (primaryOptionHold == 2)
        {
            balanceInquiry(2);
        }
        else if (primaryOptionHold == 3)
        {
            depositeCash(2);
        }
        else if (primaryOptionHold == 4)
        {
            withdrawCash(2);
        }
        else if (primaryOptionHold == 5)
        {
            fundTransfer(2);
        }
        else if (primaryOptionHold == 6)
        {
            transactionHistory(2);
        }
        else if (primaryOptionHold == 7)
        {
            accountDeactivation(2);
        }
        else if (primaryOptionHold == 8)
        {
            loginScreen(2);
        }
        else
        {
            cout << "Invalid input!!";
        }

    } while (primaryOptionHold != 8);

    return 2;
}

//* Home Screen Components

// this function will display the options user have
// and get input from user! and return that option
int primaryOption()
{
    int primaryOptions = 0;
    cout << "Enter the operation you want to perform - ";
    cin >> primaryOptions;

    return primaryOptions;
}

void optionDisplay()
{
    // number of options
    int numOfOpt = 8; // using a variable for easy future updates if needed
    // using an array so i could use a loop for displaying the options
    string options[numOfOpt] = {"Create new Account",
                                "Balance Inquiry",
                                "Cash Deposite",
                                "Cash Withdraw",
                                "Fund Transfer",
                                "Transaction History",
                                "Account Deactivation",
                                "Logout"};
    // using <iomanip> input and output manipulation builtin library for a table like output
    // cout << setw(20) << left << "Option Number" << setw(50) << left << "Option Description" << endl;
    cout << setw(2) << left << "|" << setw(15) << right << "--------------" << setw(2) << left << "|" << setw(23) << left << "--------------"
         << setw(40) << "|" << endl;
    cout << setw(2) << left << "|" << setw(15) << right << "Option Number" << setw(2) << left << "|" << setw(23) << left << "Options"
         << setw(40) << "|" << endl;
    cout << setw(2) << left << "|" << setw(15) << right << "--------------" << setw(2) << left << "|" << setw(23) << left << "--------------"
         << setw(40) << "|" << endl;
    for (int i = 0; i < numOfOpt; i++)
    {
        cout << setw(2) << left << "|" << setw(15) << right << i + 1 << setw(2) << left << "|" << setw(23) << left << options[i]
             << setw(2) << left << "|" << endl;
    }
    cout << setw(2) << left << "|" << setw(15) << right << "--------------" << setw(2) << left << "|" << setw(23) << left << "--------------"
         << setw(40) << "|" << endl;
}

//? create new account - 3
// Function to create a new user account within the system
int createNewAccount(int from)
{
    // Prompt user for necessary information
    // firstName - 0, lastName - 1, dateOfBirth - 2, nationalIdNumber - 3, userName - 4, password - 5
    int numOfData = 6; // using a variable in case if we need another field we can just incriment one and add that field to keys and work
    // To use a for loop to take the inputs
    string keys[numOfData] = {"First Name", "Last Name", "Date Of Birth [yyy-mm-dd]", "National Id Number", "Username", "Password"};
    // to store the values user have entered
    string values[numOfData];

    // Discard a part of input beign in the buffer including newline
    // in order to this to work we have to include <limits> header file
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Get user input for each field upto national id number
    for (int i = 0; i < numOfData - 2; i++)
    {
        cout << "Enter your " << keys[i] << " - ";
        getline(cin, values[i]);
    }
    // using a temperory username to take username and check if it's already exist
    string username;
    cout << "Enter your Username: ";
    getline(cin, username); // Username index
    while (true)
    {
        // Check if username already exists
        if (usernameExists(username))
        {
            cout << "Username already exists. Please choose another username." << endl;
            cout << "Enter your Username: ";
            getline(cin, username); // Username index
        }
        else
        {
            values[4] = username;
            break;
        }
    }

    // Taking separate input and Validate user input to ensure secure password creation
    // temporarily storing password for checking
    string password, confirmPassword;
    // Loop to get a strong and matching 2 passwords password from the user
    do
    {
        // Prompt for password and get user input
        cout << "Enter your Password (Must be at least 8 characters and include uppercase, lowercase, digits, and special characters) - ";
        getline(cin, password);

        // Validate password strength
        while (!isStrongPassword(password))
        {
            cout << "Password is weak. Please ensure it meets the complexity requirements." << endl;
            // Re-prompt for password if it's weak
            cout << "Enter your Password (Must be at least 8 characters and include uppercase, lowercase, digits, and special characters) - ";
            getline(cin, password);
        }
        // Prompt for password confirmation
        cout << "Confirm your Password: ";
        getline(cin, confirmPassword);
        if (confirmPassword != password)
        {
            cout << "Passwords doesn't match!!" << endl;
        }
        else
        {
            values[numOfData - 1] = password;
        }
    } while (confirmPassword != password); // Repeat until passwords match

    // Store user information in a file

    // Open "accounts.txt" in append mode
    ofstream file("accounts.txt", ios::app);
    // creating a new file for user to store his transaction
    ofstream userTransactionFile("accounts/" + values[4] + ".txt");
    userTransactionFile.close();
    // Check if file open was successful
    if (!file.is_open())
    {
        // sending an error message
        cerr << "Error opening file!" << endl;
        return 1; // Indicate error
    }
    // Write user information to the file
    for (int i = 0; i < numOfData; i++)
    {
        file << keys[i] << " - " << values[i] << "\n";
    }
    // adding a new line to maek keep up a gap betwwen datas
    file << "\n";

    // Handle potential errors during account creation
    cout << "New account created successfully!" << endl;

    // Close the file
    file.close();
    return 3;
}

//* create new account Components

// Function to check password strength
// making it a constant to prevent modifications
// passwing the address of password directly inside to
// use the actual password to prevent errors while copying the string
bool isStrongPassword(const string &password)
{
    int hasUpper = 0;
    int hasLower = 0;
    int hasDigit = 0;
    int hasSpecial = 0;

    // Check for minimum length (adjust as needed)
    if (password.length() < 8)
    {
        return false;
    }

    // Check for character types
    for (char c : password) // for every (Char c) in password
    {
        if (isupper(c))
        {
            hasUpper = 1;
        }
        else if (islower(c))
        {
            hasLower = 1;
        }
        else if (isdigit(c))
        {
            hasDigit = 1;
        }
        else if (ispunct(c))
        {
            hasSpecial = 1;
        }
    }

    // Ensure password meets complexity requirements (adjust as needed)
    return hasUpper && hasLower && hasDigit && hasSpecial;
}
// Function to check if username exists in the file
bool usernameExists(const string &username)
{
    // Open the accounts.txt file in read mode
    ifstream file("accounts.txt");
    // Check if the file opened successfully
    if (file.is_open())
    {
        string line;
        // Loop through each line in the file
        while (getline(file, line))
        {
            // Search for the line containing "Username"
            if (line.find("Username") != string ::npos)
            {
                // Extract the username value after the "-" delimiter
                string value = line.substr(line.find("-") + 2);
                // Compare the provided username with the extracted value
                if (username == value)
                {
                    // Username found, close the file and return true
                    file.close();
                    return true;
                }
            }
        }
        // Username not found in the file, close the file and return false
        file.close(); // Close the file even if username not found

        return false;
    }
    else
    {
        // Error opening the file, indicate error and return false
        cerr << "Error opening file accounts.txt!" << endl;
        return false;
    }
}

// Read user data from file
vector<UserData> readUserDataFromFile()
{
    // Open the "accounts.txt" file in read mode
    ifstream file("accounts.txt");
    vector<UserData> users; // Stores user data extracted from the file

    // Check if the file opened successfully
    if (file.is_open())
    {
        string line;
        int lineNumber = 0; // Track line number for potential error handling

        // Read lines until end of file (including the empty line)
        UserData user;
        while (getline(file, line))
        {
            lineNumber++;
            // if there is an empty line one user's data is over
            // so add that user data to users and reset user
            // and Skip empty lines between user records
            if (line.empty())
            {
                users.push_back(user); // Add user data to the vector
                user = UserData();     // Reset user struch for the next user
                continue;              // skiping the empty line
            }
            // Split the line based on the delimiter "-"
            string value = line.substr(line.find("-") + 2); // Extract data after - sign

            // Assign data to user struct fields based on line number (modulo 7)
            switch (lineNumber % 7)
            {
            case 1:
                user.firstName = value;
                break;
            case 2:
                user.lastName = value;
                break;
            case 3:

                user.dateOfBirth = value;

                break;
            case 4:
                user.nationalIdNumber = value;
                break;
            case 5:
                user.username = value;
                break;
            case 6:
                user.password = value;
                break;

            default:
                // Handle unexpected data
                cerr << "Warning: Unexpected data on line " << lineNumber << endl;
                break;
            }
        }
        // forthe last user record (if not the empty line is missed)
        if (!user.firstName.empty())
        {
            users.push_back(user);
        }
        file.close();
    }
    else
    {
        cerr << "Error opening file!" << endl;
    }

    return users;
}
//? Check Balance - 4
/**
 * Handles the process of inquiring about a user's account balance.
 *
 * This function prompts the user for their username (confirmed through
 * `confirmTransactionUsername`). It then calculates the user's current balance
 * by calling the `balance` function and passing the username. Finally, it displays
 * the user's current balance to the console.
 *
 * @param from (unused parameter in this implementation).
 * @return An integer value (purpose unclear in the provided code).
 */
int balanceInquiry(int from)
{
    // Access account data based on username credentials
    string type = "Balance Inquiry";

    string username = confirmTransactionUsername(type);
    float balanceAmmount;

    ;

    balanceAmmount = balance(username);
    // Retrieve and display the current balance
    cout << "Your current balance is: " << balanceAmmount << endl; // << /* Get balance from data store */ << endl;

    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return 4;
}
/**
 * Calculates the current balance for a user by analyzing their transaction history.
 *
 * This function takes a username as input and calls `readTransactionDataFromFile`
 * to retrieve the user's transaction data from a file. It then iterates through
 * the transactions and accumulates the total deposit and withdrawal amounts based on
 * the transaction type ("withdraw", "deposite", "to", or "from").
 *
 * - "withdraw" and "to" transactions are considered debits (subtracting from balance).
 * - "deposite" and "from" transactions are considered credits (adding to balance).
 *
 * Finally, the function returns the user's current balance by subtracting the total
 * withdrawals from the total deposits.
 *
 * @param username The username for which to calculate the balance.
 * @return The user's current balance as a float.
 */
float balance(string username)
{
    float totalWithdraw = 0, totalDeposite = 0, floatValue;
    vector<transactionData> transactions = readTransactionDataFromFile(username);
    for (const transactionData &transaction : transactions)
    {
        stringstream hold(transaction.ammount);
        hold >> floatValue;
        // if the transaction type is withdraw it is a withdraw
        // if the transaction type is to it is a fund transfer to another account
        if (transaction.type == "withdraw" || transaction.type == "to")
        {
            totalWithdraw = totalWithdraw + floatValue;
        }
        // if the transaction type is deposite it is a deposite
        // if the transaction type is from it is a fund reciewd from another account
        else if (transaction.type == "deposite" || transaction.type == "from")
        {
            totalDeposite = totalDeposite + floatValue;
        }
    }
    return (totalDeposite - totalWithdraw);
}
/**
 * Prompts the user for a username and confirms it before proceeding with a transaction.
 *
 * This function takes a transaction type ("deposit" or "withdraw") as input.
 * It then prompts the user to enter a username for the transaction. If the username
 * does not exist in the system (checked by a placeholder `usernameExists` function),
 * it offers the user the option to create a new account (calling `createNewAccount`).
 *
 * Once a valid username is entered, the function prompts the user to confirm the
 * username. It validates if the confirmed username matches the original entry.
 * This confirmation step helps prevent typos or accidental usage of incorrect usernames.
 *
 * If the username is confirmed, the function returns the confirmed username as a string.
 *
 * @param type The type of transaction ("deposit" or "withdraw").
 * @return The confirmed username as a string.
 */

string confirmTransactionUsername(string type)
{
    string username, ConfirmUsername;
    do
    {
        do
        {
            // Discard a part of input beign in the buffer including newline
            // in order to this to work we have to include <limits> header file
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Prompt for username and get user input
            cout << "Enter account username to " << type << " - ";
            getline(cin, username);
            // checking if the username is a valid username before depositing or transfering the amount
            if (usernameExists(username))
            {
                break;
            }
            else
            {
                // if the user name does not exist before asking to enter the username once again
                // asking user if you want to create a new account
                char newAcc;
                cout << "This username does not exist!" << endl;
                while (true)
                {
                    cout << "Do you want to create a new account? (Y/N) - ";
                    cin >> newAcc;

                    if (newAcc == 'y' || newAcc == 'Y')
                    {
                        createNewAccount(5);
                        break;
                    }
                    else if (newAcc == 'n' || newAcc == 'N')
                    {
                        break;
                    }
                    else
                    {
                        cout << "Invalid Input!" << endl;
                    }
                }
            }

        } while (true);

        // Prompt for username confirmation
        cout << "Confirm your Username -  ";
        getline(cin, ConfirmUsername);
        if (ConfirmUsername != username)
        {
            cout << "Username doesn't match!!" << endl;
        }
        else
        {
            return username;
        }
    } while (username != ConfirmUsername); // Repeat until username match
    return username;
}
/**
 * Gets the current date and time in a formatted string (YYYY-MM-DD HH:MM:SS).
 *
 * This function retrieves the current time from the system and converts it
 * to a human-readable format. The format used is year-month-day followed by
 * a space, then hour:minute:second.
 *
 * @return A string containing the current date and time in YYYY-MM-DD HH:MM:SS format.
 */
string currentTime()
{
    // Get the current time in seconds since the epoch (January 1, 1970, 00:00:00 UTC)
    time_t now = time(0);            // Get current time in seconds since epoch
    tm *localTime = localtime(&now); // Convert to local time structure
    // Convert the time_t value to a local time structure (tm)
    // This structure holds various components of the date and time
    int year = localTime->tm_year + 1900; // Adjust for base year
    // Months are 0-indexed (January is 0), so add 1 for human-readable format
    int month = localTime->tm_mon + 1;

    int day = localTime->tm_mday;
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;

    // Format the date and time as a string using string concatenation
    string formattedDateTime = to_string(year) + "-" +
                               to_string(month) + "-" +
                               to_string(day) + " " +
                               to_string(hour) + ":" +
                               to_string(minute) + ":" +
                               to_string(second);
    // Return the formatted current date and time string
    return formattedDateTime;
}
//? deposite cash - 5

/**
 * Handles the process of depositing cash to a user's account.
 *
 * This function prompts the user for the username (which is confirmed
 * through `confirmTransactionUsername`), deposit purpose, and amount.
 * It then writes the transaction details (username, purpose, amount, type,
 * "none" for recipient, current date/time) to a file named "username.txt"
 * located in the "accounts" directory. The file format assumes a specific
 * structure with data fields separated by "-". An empty line is appended after
 * each transaction record.
 *
 * The function validates the deposit amount (non-negative) and allows the user
 * to confirm the amount before writing the transaction data.
 *
 * @return An integer value.
 */
int depositeCash(int from)
{
    int numOfData = 6;
    string keys[numOfData] = {"username", "purpose", "ammount", "type", "who", "dateTime"};
    string values[numOfData];
    values[3] = "deposite";
    values[4] = "none";
    // updating time of deposite
    values[5] = currentTime();
    values[0] = confirmTransactionUsername(values[3]);
    cout << "Enter the purpose of the deposite - ";
    getline(cin, values[1]);
    char confirm;
    do
    {
        // Discard a part of input beign in the buffer including newline
        // in order to this to work we have to include <limits> header file
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter the ammount you want to deposite - ";
        getline(cin, values[2]);

        cout << "Confirm if the ammount is correct (Y/N) - ";
        cin >> confirm;
        float depositeAmount;
        stringstream buffer(values[2]);
        buffer >> depositeAmount;
        if (depositeAmount < 0)
        {
            cout << "Invalid deposite ammount!!" << endl;
        }
        if (confirm == 'y' || confirm == 'Y')
        {
            break;
        }
        else if (confirm == 'n' || confirm == 'N')
        {
        }
        else
        {
            cout << "Invalid Input!!" << endl;
        }
    } while (true);

    ofstream depositeFile("accounts/" + values[0] + ".txt", ios::app);

    if (depositeFile.is_open())
    {
        for (int i = 0; i < numOfData; i++)
        {
            depositeFile << keys[i] << " - " << values[i] << endl;
        }
        depositeFile << endl;
    }
    // Prompt user for deposit amount
    // Validate deposit amount (e.g., non-negative value)
    // Update account balance in the data store based on deposit amount
    cout << values[2] << " LKR Cash Deposited Sucessfully to " << values[0] << "'s Account!"; // <<  Get deposit amount from user  << " successfully!" << endl;
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return 5;
}

/**
 * Handles the process of withdrawing cash from a user's account.
 *
 * This function prompts the user for the username (which is confirmed
 * through `confirmTransactionUsername`), withdrawal purpose, and amount.
 * It then checks the account balance (using a placeholder `balance` function)
 * to ensure sufficient funds.
 *
 * If the balance is sufficient, the transaction details (username, purpose,
 * amount, type, "none" for recipient, current date/time) are written to a file
 * named "username.txt" located in the "accounts" directory. The file format
 * assumes a specific structure with data fields separated by "-". An empty line
 * is appended after each transaction record.
 *
 * If the balance is insufficient, an error message is displayed to the user.
 *
 * @return An integer value (purpose unclear in the provided code).
 */
//? Withdraw cash - 6
int withdrawCash(int from)
{
    int numOfData = 6;
    string keys[numOfData] = {"username", "purpose", "ammount", "type", "who", "dateTime"};
    string values[numOfData];
    values[3] = "withdraw";
    values[4] = "none";
    values[5] = currentTime();
    values[0] = confirmTransactionUsername(values[3]);

    cout << "Enter the purpose of the withdraw - ";
    getline(cin, values[1]);
    char confirm;
    float withdrawAmmount;
    do
    {
        // Discard a part of input beign in the buffer including newline
        // in order to this to work we have to include <limits> header file
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter the ammount you want to withdraw - ";
        getline(cin, values[2]);

        cout << "Confirm if the ammount is correct (Y/N) - ";
        cin >> confirm;
        stringstream buffer(values[2]);
        buffer >> withdrawAmmount;
        if (withdrawAmmount < 0)
        {
            cout << "Invalid withdraw ammount!!" << endl;
        }
        if (confirm == 'y' || confirm == 'Y')
        {
            break;
        }
        else if (confirm == 'n' || confirm == 'N')
        {
        }
        else
        {
            cout << "Invalid Input!!" << endl;
        }
    } while (true);
    ifstream withdrawAmountCheck("accounts/" + values[0] + ".txt", ios::app);
    string line;
    // checking if the account balance is greater than the withdraw ammount

    if (balance(values[0]) > withdrawAmmount)
    {

        ofstream withdrawFile("accounts/" + values[0] + ".txt", ios::app);
        if (withdrawFile.is_open())
        {

            for (int i = 0; i < numOfData; i++)
            {
                withdrawFile << keys[i] << " - " << values[i] << endl;
            }
            withdrawFile << endl;
        }

        // Prompt user for deposit amount
        // Validate deposit amount (e.g., non-negative value)
        // Update account balance in the data store based on deposit amount
        cout << values[2] << " LKR Cash Withdrawed from" << values[0] << "'s Account"; // <<  Get deposit amount from user  << " successfully!" << endl;
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else
    {

        cout << "Insufficient Balance!!" << endl;
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        homeScreen(6);
    }
    return 6;
}

/**
 * Reads transaction data for a specific user from a file.
 *
 * This function takes the username as input and attempts to open a file named
 * "username.txt" located in the "accounts" directory. The file is assumed to
 * store transaction data in a specific format.
 *
 * The function parses the file line by line, extracting transaction details
 * based on their position within the file. It uses a switch statement to assign
 * data to the appropriate fields (username, purpose, amount, type, etc.) in a
 * `transactionData` struct. Empty lines are used as delimiters between different
 * users' transaction records.
 *
 * If the file is opened successfully, the function populates a `vector<transactionData>`
 * with the extracted transactions and returns it. If the file cannot be opened,
 * an error message is printed to standard error (cerr).
 *
 * @param username The username for which to read transaction data.
 * @return A vector containing transaction data objects for the specified user.
 */
vector<transactionData> readTransactionDataFromFile(string username)
{
    ifstream file("accounts/" + username + ".txt");
    // Open the "username.txt" file in read mode

    vector<transactionData> transactions; // Stores transaction data extracted from the file

    // Check if the file opened successfully
    if (file.is_open())
    {
        string line;
        int lineNumber = 0; // Track line number for potential error handling

        // Read lines until end of file (including the empty line)
        transactionData transaction;
        while (getline(file, line))
        {
            lineNumber++;
            // if there is an empty line one transaction's data data is over
            // so add that user data to datas and reset data
            // and Skip empty lines between user records
            if (line.empty())
            {
                transactions.push_back(transaction); // Add transaction data to the vector
                transaction = transactionData();     // Reset transaction struct for the next transaction
                continue;                            // skiping the empty line
            }
            // Split the line based on the delimiter "-"
            string value = line.substr(line.find("-") + 2); // Extract data after - sign

            // Assign data to transaction struct fields based on line number (modulo 7)
            switch (lineNumber % 7)
            {
            case 1:
                transaction.username = value;
                break;
            case 2:
                transaction.purpose = value;
                break;
            case 3:

                transaction.ammount = value;

                break;
            case 4:
                transaction.type = value;
                break;
            case 5:
                transaction.who = value;
                break;
            case 6:
                transaction.dateTime = value;
                break;
            default:
                // Handle unexpected data
                cerr << "Warning: Unexpected data on line " << lineNumber << endl;
                break;
            }
        }
        // forthe last user record (if not the empty line is missed)
        if (!transaction.username.empty())
        {
            transactions.push_back(transaction);
        }
        file.close();
    }
    else
    {
        cerr << "Error opening file!" << endl;
    }

    return transactions;
}
//? fund transfer - 7
// Function to enable transferring funds to another account
int fundTransfer(int from)
{
    int numOfData = 6;
    string keys[numOfData] = {"username", "purpose", "ammount", "type", "who", "dateTime"};
    string values[numOfData];
    values[3] = "transfer";
    values[5] = currentTime();
    values[0] = confirmTransactionUsername("owener's account");
    values[4] = confirmTransactionUsername("who you want to send money");

    cout << "Enter the purpose of the transaction- ";
    getline(cin, values[1]);
    char confirm;
    float withdrawAmmount;
    do
    {
        // Discard a part of input beign in the buffer including newline
        // in order to this to work we have to include <limits> header file
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter the ammount you want to transfer - ";
        getline(cin, values[2]);

        cout << "Confirm if the ammount is correct (Y/N) - ";
        cin >> confirm;
        stringstream buffer(values[2]);
        buffer >> withdrawAmmount;
        if (withdrawAmmount < 0)
        {
            cout << "Invalid transfer ammount!!" << endl;
        }
        if (confirm == 'y' || confirm == 'Y')
        {
            break;
        }
        else if (confirm == 'n' || confirm == 'N')
        {
        }
        else
        {
            cout << "Invalid Input!!" << endl;
        }
    } while (true);
    ifstream withdrawAmountCheck("accounts/" + values[0] + ".txt", ios::app);
    string line;
    // checking if the account balance is greater than the withdraw ammount

    if (balance(values[0]) > withdrawAmmount)
    {

        ofstream withdrawFile("accounts/" + values[0] + ".txt", ios::app);
        ofstream recieveFile("accounts/" + values[4] + ".txt", ios::app);
        if (withdrawFile.is_open() && recieveFile.is_open())
        {

            for (int i = 0; i < numOfData; i++)
            {
                for (int k = 0; k < 2; k++)
                {
                    if (k == 0)
                    {
                        values[3] = "to";
                        withdrawFile << keys[i] << " - " << values[i] << endl;
                    }
                    else if (k == 1)
                    {
                        values[3] = "from";
                        string hold = values[0];
                        values[0] = values[4];
                        values[4] = hold;
                        recieveFile << keys[i] << " - " << values[i] << endl;
                    }
                }
            }
            withdrawFile << endl;
            recieveFile << endl;
        }

        // Prompt user for deposit amount
        // Validate deposit amount (e.g., non-negative value)
        // Update account balance in the data store based on deposit amount
        cout << values[2] << " LKR transfered to " << values[4]
             << "from" << values[0] << "'s Account" << endl; // <<  Get deposit amount from user  << " successfully!" << endl;
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else
    {

        cout << "Insufficient Balance!!" << endl;
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        homeScreen(6);

        // Prompt user for recipient account information - username
        // Validate recipient information
        // Prompt user for transfer amount
        // Validate transfer amount (e.g., sufficient balance)
        // Update account balances (sender and recipient) in the data store
        cout << "Successfully transferred "; // << /* Get transfer amount from user */ << " to recipient." << endl;
    }
    return 7;
}

//? transaction history - 8
// Function to display past transactions associated with the account
int transactionHistory(int from)
{
    // Access transaction history data based on logged-in user credentials
    // Display a formatted list of past transactions (e.g., date, amount, type)
    // Allow user to navigate through transaction history (optional)
    cout << "Displaying transaction history..." << endl;
    // Implement logic to display transactions
    return 8;
}

//? account deactivation - 9
// Function to permanently deactivate the logged-in user account
int accountDeactivation(int from)
{
    // Prompt user for confirmation to deactivate
    // Provide clear information about the irreversible nature of deactivation
    // Deactivate the account by removing or marking it as inactive in the data store
    cout << "Your account has been deactivated." << endl;
    return 9;
}
