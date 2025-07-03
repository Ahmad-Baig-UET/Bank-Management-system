#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <sstream> 
using namespace std;

//          Function Prototypes 
//               Utility 
void showLogo();
void setColor(int);


//          Menu 
void showAdminMenu();
void showUserMenu();

//        Login & Signup 
void createAccountRequest();
bool login();
void SeeAccountNumber();

//           Admin 
void approveAccounts();  //approves a account recently created
void approveLoans();   //approves requested loans
void manageInterestRates();     //manages interest rates on loans
void manageLoans();             //manages loans like return date
void manageCredits();                 //credit payements and their history
void listAllAccounts();                  //all existing accounts
void setBankRules();                 //set some rules like minimum balance, maximum withdraw
void manageATMCash();                      //adds fund to atm storage 
void divideCash();                          //split bw atm and vault
void recordInvestment();                               //investments made by bank
void setAccountTypes();                          //assign saving or current to users
void setProfitRate();                                     //set monthly profit for saving account 
void removeUser();                                   //removes user from system

//               User 
void manageDueDates();   //ALL USER FUNCTIONS HAVE SAME WORKING AS THE PROTOTYPE MEANING SUGGESTS
void depositCash();
void withdrawCash();
void changeAccountType();
void createNewAccount();
void checkBalance();
void payCredit();
void requestLoan();
void viewReturnDate();
void takeProfit();
void returnLoan();
void transferMoney();
void closeAccount();
void atmWithdraw();
void openSavingAccount();


// just to make it feel like real app like jazzcaash 
void loadingBar();
void welcome();





int main() {
    welcome();
    int choice;
    do {

        system("cls"); // Clear screen
        showLogo(); // Show logo

        cout << "0. Exit\n";
        cout << "1. Login as User\n";
        cout << "2. Login as Admin\n";
        cout << "3. Create Account Request\n";
        cout << "4. See Account Number\n";
        cout << "Enter choice: ";
        cin >> choice;
        loadingBar();
        if (choice == 1) {
            if (login()) {
                showUserMenu();
            }
            else {
                cout << "Access denied.\n"; system("pause");
            }
        }
        else if (choice == 2) {
            string pass;
            cin.ignore();
            cout << "Enter Admin Password: ";
        
            getline(cin, pass);
            
            if (pass == "admin123") {
                showAdminMenu();
            }
            else {
                cout << "Incorrect Admin Password.\n"; system("pause");
            }
        }
        else if (choice == 3) {
            createAccountRequest();
        }
        else if (choice == 4) {
            SeeAccountNumber();
        }
        else if (choice == 0) {
            loadingBar();
            cout << "Exiting...\n";
        }
        else {
            cout << "Invalid choice.\n"; system("pause");
        }
    } while (choice != 0);

    return 0;
}






void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); // Changes colour
}

void showLogo() {    //To Show logo on every function and make it like a constant screen design 
    setColor(11);
    cout << "=====================================\n";
    cout << "          SNT BANK OF LAHORE         \n";
    cout << "=====================================\n";
    setColor(14);
}


//            Login System 



bool verifyCredentials(string name, string password, string accNumber) {    //Verifies credentials in a bool if true then proceed
    ifstream fileUser("usernames.txt");
    ifstream filePass("passwords.txt");
    ifstream fileAcc("accountnumbers.txt");

    string fileName, filePassWord, fileAccNumber;
cin.ignore();
    while (getline(fileUser, fileName) &&
        getline(filePass, filePassWord) &&
        getline(fileAcc, fileAccNumber)) {
        if (name == fileName && password == filePassWord && accNumber == fileAccNumber) {
            return true;
        }
    }
    return false;
}

bool login() {
    string inputName, inputPassword, inputAccNumber;              //Login with pass and stuff then it verifies from verify fucntion
    system("cls"); // Clear screen
    showLogo(); // Show logo
    cout << "---- Login ----\n";
    cout << "Enter Username: ";
    cin.ignore();
    getline(cin, inputName);
    cout << "Enter Password: ";
    getline(cin, inputPassword);
    cout << "Enter Account Number: ";
    getline(cin, inputAccNumber);

    return verifyCredentials(inputName, inputPassword, inputAccNumber);
}

void createAccountRequest() {              //create new account request 
    string name, cnic, password;
    system("cls"); // Clear screen
    showLogo(); // Show logo
    cout << "---- Create Account Request ----\n";
    cin.ignore();
    cout << "Enter Full Name: ";
    getline(cin, name);
    cout << "Enter CNIC: ";
    getline(cin, cnic);
    cout << "Enter Password: ";
    getline(cin, password);

    ofstream pendingFile("pending_accounts.txt", ios::app);
    pendingFile << name << "," << cnic << "," << password << endl;
    pendingFile.close();

    cout << "Account request submitted. Wait for admin approval.\n";
    system("pause");
}



void viewReturnDate() {
    system("cls");
    showLogo();
    cout << "--- View Your Loan Return Date ---\n";

    string username;
    cin.ignore();
    cout << "Enter your username: ";
    getline(cin, username);

    ifstream file("loans.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t pos1 = line.find(',');             // After username
        size_t pos2 = line.find(',', pos1 + 1);   // After loan amount
        size_t pos3 = line.find(',', pos2 + 1);   // After due date

        string name = line.substr(0, pos1);
        string amount = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string dueDate = line.substr(pos2 + 1, pos3 - pos2 - 1);
        string totalDue = line.substr(pos3 + 1);

        if (name == username) {
            cout << "\n? Loan Return Details:\n";
            cout << "Loan Amount: Rs " << amount << endl;
            cout << "Return Date: " << dueDate << endl;
            cout << "Total Payable with Interest: Rs " << totalDue << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\n? No loan record found for this user.\n";
    }

    system("pause");
}


void SeeAccountNumber()
{
    system("cls");
    showLogo();
    string username;
    cin.ignore();
    cout << "--- Retrieve Account Number ---\n";
    cout << "Enter your username: ";
    getline(cin, username);

    ifstream userFile("usernames.txt");
    ifstream accFile("accountnumbers.txt");

    string nameLine, accLine;
    bool found = false;

    while (getline(userFile, nameLine) && getline(accFile, accLine)) {
        if (nameLine == username) {
            cout << "\n? Account Number: " << accLine << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\n? User not found.\n";
    }

    userFile.close();
    accFile.close();
    system("pause");

}



//            Admin Functions 
void approveAccounts() {
    system("cls");
    showLogo();
    cout << "--- Approve Account Requests ---\n";

    ifstream in("pending_accounts.txt");
    ofstream users("usernames.txt", ios::app);
    ofstream passes("passwords.txt", ios::app);
    ofstream accs("accountnumbers.txt", ios::app);

    string name, cnic, pass;
    string line;
    while (getline(in, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.rfind(',');

        name = line.substr(0, pos1);
        cnic = line.substr(pos1 + 1, pos2 - pos1 - 1);
        pass = line.substr(pos2 + 1);
        string yesss;
        cout << name;
        cout << endl << cnic;
        cout << endl << "Approve: ";
        cin >> yesss;
        if (yesss == "yes") {

            srand(time(0));
            long long accNo = 1000000000 + rand() % 900000000;

            users << name << endl;
            passes << pass << endl;
            accs << accNo << endl;

            cout << "Approved: " << name << " | Account#: " << accNo << "\n";
        }
        else {
            cout << "Not approved. ";
        }
    }
    in.close();
    ofstream clear("pending_accounts.txt");
    clear.close();
    system("pause");
}

void approveLoans() {
    system("cls");
    showLogo();
    cout << "--- Approve Loan Requests ---\n";

    ifstream in("loan_requests.txt");
    ofstream out("loans.txt", ios::app);

    string line;
    while (getline(in, line)) {
        out << line << endl;
        cout << "Approved: " << line << endl;
    }

    in.close();
    ofstream clear("loan_requests.txt");
    clear.close();
    system("pause");
}

void manageInterestRates() {
    system("cls");
    showLogo();
    cout << "--- Set Interest Rate ---\n";
    float rate;
    cout << "Enter interest rate %: ";
    cin >> rate;
    ofstream out("interest_rate.txt");
    out << rate;
    out.close();
    cout << "Interest rate set.\n";
    system("pause");
}

void manageLoans() {
    system("cls");
    showLogo();
    cout << "--- All Loans ---\n";
    ifstream file("loans.txt");
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
    system("pause");
}

void manageCredits() {
    system("cls");
    showLogo();
    cout << "--- All Credit Payments ---\n";
    ifstream file("credit_payments.txt");
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
    system("pause");
}

void listAllAccounts() {
    system("cls");
    showLogo();
    cout << "--- All Approved Users ---\n";
    ifstream u("usernames.txt");
    ifstream a("accountnumbers.txt");

    string name, acc;
    while (getline(u, name) && getline(a, acc)) {
        cout << "Name: " << name << " | Account#: " << acc << endl;
    }
    system("pause");
}

void setBankRules() {
    system("cls");
    showLogo();
    float minBal, maxWithdraw;
    cout << "--- Set Bank Rules ---\n";
    cout << "Enter minimum balance required: ";
    cin >> minBal;
    cout << "Enter maximum withdrawal limit: ";
    cin >> maxWithdraw;
    ofstream out("rules.txt");
    out << minBal << "," << maxWithdraw;
    out.close();
    cout << "Rules saved.\n";
    system("pause");
}

void manageATMCash() {
    system("cls");
    showLogo();
    float total;
    cout << "--- ATM Cash Management ---\n";
    cout << "Enter cash to refill ATM: ";
    cin >> total;
    ofstream out("atm_cash.txt");
    out << total;
    out.close();
    cout << "Cash refilled.\n";
    system("pause");
}

void divideCash() {
    system("cls");
    showLogo();
    float ratio;
    cout << "--- Divide Cash (ATM/Bank Vault) ---\n";
    cout << "Enter % for ATM (0-100): ";
    cin >> ratio;
    ofstream out("cash_division.txt");
    out << ratio;
    out.close();
    cout << "Cash division updated.\n";
    system("pause");
}

void recordInvestment() {
    system("cls");
    showLogo();
    float amt;
    cout << "--- Record Bank Investment ---\n";
    cout << "Enter amount to invest: ";
    cin >> amt;
    ofstream out("investments.txt", ios::app);
    out << amt << endl;
    out.close();
    cout << "Investment recorded.\n";
    system("pause");
}

void setAccountTypes() {
    system("cls");
    showLogo();
    cout << "--- Set Account Type ---\n";
    string user, type;
    cin.ignore();
    cout << "Username: "; getline(cin, user);
    cout << "Type (saving/current): "; getline(cin, type);
    ofstream out("account_types.txt", ios::app);
    out << user << "," << type << endl;
    out.close();
    cout << "Account type set.\n";
    system("pause");
}

void setProfitRate() {
    system("cls");
    showLogo();
    cout << "--- Set Monthly Profit Rate for Savings ---\n";
    float rate;
    cout << "Enter % rate: ";
    cin >> rate;
    ofstream out("profit_rate.txt");
    out << rate;
    out.close();
    cout << "Profit rate saved.\n";
    system("pause");
}

void removeUser() {
    system("cls");
    showLogo();
    string user;
    cin.ignore();
    cout << "Enter username to remove: ";
    getline(cin, user);
    ofstream out("removed_users.txt", ios::app);
    out << user << endl;
    out.close();
    cout << "User removal request recorded.\n";
    system("pause");
}

//                 Admin Menu 
void showAdminMenu() {
    int choice;
    do {
        system("cls");
        showLogo();
        cout << "0. Exit to Main Menu\n";
        cout << "1. Approve Accounts\n";
        cout << "2. Approve Loans\n";
        cout << "3. Manage Interest Rates\n";
        cout << "4. Manage Loans\n";
        cout << "5. Manage Credits\n";
        cout << "6. List All Accounts\n";
        cout << "7. Set Bank Rules\n";
        cout << "8. ATM Cash Management\n";
        cout << "9. Divide Cash\n";
        cout << "10. Record Investment\n";
        cout << "11. Set Account Types\n";
        cout << "12. Set Profit Rate\n";
        cout << "13. Remove User\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: approveAccounts(); break;
        case 2: approveLoans(); break;
        case 3: manageInterestRates(); break;
        case 4: manageLoans(); break;
        case 5: manageCredits(); break;
        case 6: listAllAccounts(); break;
        case 7: setBankRules(); break;
        case 8: manageATMCash(); break;
        case 9: divideCash(); break;
        case 10: recordInvestment(); break;
        case 11: setAccountTypes(); break;
        case 12: setProfitRate(); break;
        case 13: removeUser(); break;
        case 0: cout << "Returning...\n"; break;
        default: cout << "Invalid option.\n"; system("pause");
        }
    } while (choice != 0);
}


//         USER FUNCTIONS 

void manageDueDates() {
    system("cls");
    showLogo();
    cout << "--- Loan Due Dates & Transactions ---\n";
    ifstream file("loans.txt");
    string line;
    while (getline(file, line)) cout << line << endl;
    file.close();
    system("pause");
}

void depositCash() {
    system("cls");
    showLogo();
    cout << "--- Deposit Cash ---\n";
    string acc; float amt;
    cout << "Account number: "; cin >> acc;
    cout << "Amount: "; cin >> amt;
    ofstream file("transactions.txt", ios::app);
    file << acc << ",deposit," << amt << endl;
    file.close();
    cout << "? Deposited.\n"; system("pause");
}

void withdrawCash() {
    system("cls");
    showLogo();
    cout << "--- Withdraw Cash ---\n";
    string acc; float amt;
    cout << "Account number: "; cin >> acc;
    cout << "Amount: "; cin >> amt;
    ofstream file("transactions.txt", ios::app);
    file << acc << ",withdraw," << amt << endl;
    file.close();
    cout << "? Withdraw recorded.\n"; system("pause");
}

void changeAccountType() {
    system("cls");
    showLogo();
    string user, type;
    cin.ignore();
    cout << "Username: "; getline(cin, user);
    cout << "New type (saving/current): "; getline(cin, type);
    ofstream out("account_types.txt", ios::app);
    out << user << "," << type << endl;
    out.close();
    cout << "? Type changed.\n"; system("pause");
}

void createNewAccount() {
    createAccountRequest(); // Reuse
}




void checkBalance() {
    system("cls");
    showLogo();
    cout << "--- Balance Check ---\n";

    string accNumber;
    cout << "Enter your account number: ";
    cin >> accNumber;

    ifstream file("transactions.txt");
    if (!file.is_open()) {
        cout << "Error opening transactions file.\n";
        system("pause");
        return;
    }

    string line;
    float balance = 0;

    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        if (pos1 == string::npos || pos2 == string::npos) continue;

        string fileAcc = line.substr(0, pos1);
        string type = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string amountStr = line.substr(pos2 + 1);

        if (fileAcc != accNumber) continue;

        float amount = 0;
        stringstream ss(amountStr);
        ss >> amount;
        if (ss.fail()) continue; // Skip if conversion fails

        if (type == "deposit") {
            balance += amount;
        }
        else if (type == "withdraw") {
            balance -= amount;
        }
    }

    file.close();
    cout << "Available Balance: Rs " << balance << endl;
    system("pause");
}


void payCredit() {
    system("cls");
    showLogo();
    string user; float amt;
    cin.ignore();
    cout << "Username: "; getline(cin, user);
    cout << "Amount to pay: "; cin >> amt;

    // Get user's account number
    string accNum, line;
    ifstream userFile("usernames.txt"), accFile("accountnumbers.txt");
    while (getline(userFile, line)) {
        string accLine;
        getline(accFile, accLine);
        if (line == user) {
            accNum = accLine;
            break;
        }
    }
    userFile.close();
    accFile.close();

    if (accNum == "") {
        cout << "User not found.\n";
        system("pause");
        return;
    }

    // Check balance manually
    float balance = 0;
    ifstream trans("transactions.txt");
    while (getline(trans, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        if (pos1 == string::npos || pos2 == string::npos) continue;

        string acc = line.substr(0, pos1);
        string type = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string amountStr = line.substr(pos2 + 1);

        if (acc != accNum) continue;

        float amount = 0;
        stringstream ss(amountStr);
        ss >> amount;
        if (ss.fail()) continue;

        if (type == "deposit") balance += amount;
        else if (type == "withdraw") balance -= amount;
    }
    trans.close();

    if (amt > balance) {
        cout << "Insufficient balance.\n";
    }
    else {
        // Log payment
        ofstream out("credit_payments.txt", ios::app);
        out << user << "," << amt << endl;
        ofstream tfile("transactions.txt", ios::app);
        tfile << accNum << ",withdraw," << amt << endl;
        cout << "? Credit paid.\n";
    }
    system("pause");
}



void requestLoan() {
    system("cls");
    showLogo();
    string user, due; float amt;
    cin.ignore();
    cout << "Username: "; getline(cin, user);
    cout << "Loan amount: "; cin >> amt;
    cout << "Due date (YYYY-MM-DD): "; cin.ignore(); getline(cin, due);

    float rate = 0;
    ifstream rateFile("interest_rate.txt");
    rateFile >> rate;
    rateFile.close();

    float interestAmt = amt * rate / 100;
    float totalDue = amt + interestAmt;

    ofstream out("loan_requests.txt", ios::app);
    out << user << "," << amt << "," << due << "," << totalDue << endl;
    out.close();

    cout << "Interest Rate: " << rate << "%\n";
    cout << "? Loan of Rs " << amt << " requested. Total payable: Rs " << totalDue << "\n";
    system("pause");
}

void returnLoan() {
    system("cls");
    showLogo();
    string user; float amt;
    cin.ignore();
    cout << "Username: "; getline(cin, user);
    cout << "Amount: "; cin >> amt;

    // Find account number
    string accNum, line;
    ifstream userFile("usernames.txt"), accFile("accountnumbers.txt");
    while (getline(userFile, line)) {
        string accLine;
        getline(accFile, accLine);
        if (line == user) {
            accNum = accLine;
            break;
        }
    }
    userFile.close();
    accFile.close();

    if (accNum == "") {
        cout << "User not found.\n";
        system("pause");
        return;
    }

    // Check balance (manual float conversion)
    float balance = 0;
    ifstream trans("transactions.txt");
    while (getline(trans, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        if (pos1 == string::npos || pos2 == string::npos) continue;

        string acc = line.substr(0, pos1);
        string type = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string amountStr = line.substr(pos2 + 1);

        if (acc != accNum) continue;

        float amount = 0;
        stringstream ss(amountStr);
        ss >> amount;
        if (ss.fail()) continue;

        if (type == "deposit") balance += amount;
        else if (type == "withdraw") balance -= amount;
    }
    trans.close();

    if (amt > balance) {
        cout << "Insufficient balance to return loan.\n";
    }
    else {
        ofstream out("loan_returns.txt", ios::app);
        out << user << "," << amt << endl;
        ofstream tfile("transactions.txt", ios::app);
        tfile << accNum << ",withdraw," << amt << endl;
        cout << "? Loan returned.\n";
    }
    system("pause");
}



void takeProfit() {
    system("cls");
    showLogo();
    string user;
    float rate = 0;
    cin.ignore();
    cout << "Username: "; getline(cin, user);

    // Check account type (must be saving)
    bool isSaving = false;
    string line;
    ifstream types("account_types.txt");
    while (getline(types, line)) {
        size_t pos = line.find(',');
        string u = line.substr(0, pos);
        string t = line.substr(pos + 1);
        if (u == user && t == "saving") {
            isSaving = true;
            break;
        }
    }
    types.close();
    if (!isSaving) {
        cout << "Only savings accounts earn profit.\n";
        system("pause");
        return;
    }

    // Get profit rate from file
    ifstream rateFile("profit_rate.txt");
    rateFile >> rate;
    rateFile.close();

    // Get account number for user
    string accNum;
    ifstream users("usernames.txt"), accs("accountnumbers.txt");
    while (getline(users, line)) {
        string acc;
        getline(accs, acc);
        if (line == user) {
            accNum = acc;
            break;
        }
    }
    users.close(); accs.close();
    if (accNum == "") {
        cout << "Account number not found.\n";
        system("pause");
        return;
    }

    // Calculate balance manually
    float balance = 0;
    ifstream trans("transactions.txt");
    while (getline(trans, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        if (pos1 == string::npos || pos2 == string::npos) continue;

        string acc = line.substr(0, pos1);
        string type = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string amountStr = line.substr(pos2 + 1);

        if (acc != accNum) continue;

        float amount = 0;
        stringstream ss(amountStr);
        ss >> amount;
        if (ss.fail()) continue;

        if (type == "deposit") balance += amount;
        else if (type == "withdraw") balance -= amount;
    }
    trans.close();

    // Apply profit
    float profit = balance * rate / 100;

    ofstream out("transactions.txt", ios::app);
    out << accNum << ",deposit," << profit << endl;

    cout << "Profit @ " << rate << "% = Rs " << profit << " added to your account.\n";
    system("pause");
}





void transferMoney() {
    system("cls");
    showLogo();
    string from, to;
    float amt;
    cin.ignore();
    cout << "From (Account): "; getline(cin, from);
    cout << "To (Account): "; getline(cin, to);
    cout << "Amount: "; cin >> amt;

    float balance = 0;
    string line;

    // Read transactions and calculate 'from' balance
    ifstream trans("transactions.txt");
    while (getline(trans, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        if (pos1 == string::npos || pos2 == string::npos) continue;

        string acc = line.substr(0, pos1);
        string type = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string amountStr = line.substr(pos2 + 1);

        float amount = 0;
        stringstream ss(amountStr);
        ss >> amount;
        if (ss.fail()) continue;

        if (acc == from) {
            if (type == "deposit") balance += amount;
            else if (type == "withdraw") balance -= amount;
        }
    }
    trans.close();

    if (amt > balance) {
        cout << "Insufficient funds to transfer.\n";
    }
    else {
        // Record transfer
        ofstream out("transfers.txt", ios::app);
        out << from << "," << to << "," << amt << endl;

        ofstream tfile("transactions.txt", ios::app);
        tfile << from << ",withdraw," << amt << endl;
        tfile << to << ",deposit," << amt << endl;

        cout << "? Transfer complete.\n";
    }
    system("pause");
}



void closeAccount() {
    system("cls");
    showLogo();
    string user;
    cin.ignore();
    cout << "Username: "; getline(cin, user);
    ofstream out("close_requests.txt", ios::app);
    


    out << user << endl;
    out.close();
    cout << "? Closure request sent.\n"; system("pause");
}

void atmWithdraw() {
    system("cls");
    showLogo();
    string acc; float amt;
    cout << "Account number: "; cin >> acc;
    cout << "Withdraw amount: "; cin >> amt;
  
    ofstream out("atm_withdrawals.txt", ios::app);
 


    out << acc << "," << amt << endl;
    out.close();
    cout << "? ATM withdrawal recorded.\n"; system("pause");
}

void openSavingAccount() {
    system("cls");
    showLogo();
    string user;
    cin.ignore();
    cout << "Username: "; getline(cin, user);
    ofstream out("account_types.txt", ios::app);
    out << user << ",saving" << endl;
    out.close();
    cout << "? Saving account requested.\n"; system("pause");
}

//            USER MENU 
void showUserMenu() {
    int choice;
    do {
        system("cls");
        showLogo();
        setColor(2);
        cout << "0. Exit to Main Menu\n";
        cout << "1. Manage Due Dates\n";
        cout << "2. Deposit Cash\n";
        cout << "3. Withdraw Cash\n";
        cout << "4. Change Account Type\n";
        cout << "5. Create New Account\n";
        cout << "6. Check Balance\n";
        cout << "7. Pay Credit\n";
        cout << "8. Take Loan\n";
        cout << "9. View Return Date\n";
        cout << "10. Take Profit\n";
        cout << "11. Return Loan\n";
        cout << "12. Transfer Money\n";
        cout << "13. Close Account\n";
        cout << "14. ATM Withdraw\n";
        cout << "15. Open Saving Account\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: manageDueDates(); break;
        case 2: depositCash(); break;
        case 3: withdrawCash(); break;
        case 4: changeAccountType(); break;
        case 5: createNewAccount(); break;
        case 6: checkBalance(); break;
        case 7: payCredit(); break;
        case 8: requestLoan(); break;
        case 9: viewReturnDate(); break;
        case 10: takeProfit(); break;
        case 11: returnLoan(); break;
        case 12: transferMoney(); break;
        case 13: closeAccount(); break;
        case 14: atmWithdraw(); break;
        case 15: openSavingAccount(); break;
        case 0: cout << "Returning...\n"; break;
        default: cout << "Invalid option.\n"; system("pause");
        }
    } while (choice != 0);
}



void loadingBar() {
    system("cls");
    setColor(10);
    cout << "Loading";
    for (int i = 0; i < 5; i++) {
        Sleep(300);
        cout << ".";
        Sleep(60);
    }
    cout << "\n";
}




void welcome() {
    system("cls");
    setColor(10);
    cout << "WELCOME TO SNT BANK";
    for (int i = 0; i < 6; i++) {
        Sleep(300);
        cout << ".";
        Sleep(60);
    }
    cout << "\n";
}

