#include <iostream>
#include <string>

using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

struct Line {
    string mobileNumber;
    string packageType;
    double balance;
    Date date;

    void displayLineInfo() const {
        cout << "Number: " << mobileNumber << "\nBalance: " << balance << "\nPackage: " << packageType << endl;
    }

    bool hasEnoughBalance(double amount) const {
        return balance >= amount;
    }

    void deductBalance(double amount) {
        if (balance >= amount) {
            balance -= amount;
        }
    }
};

struct User {
    string ID;
    string email;
    string name;
    string password;
    string address;
    Line lines[3];  // Store user's lines

    void printUserInfo() const {
        cout << "Email: " << email << "\nAddress: " << address << endl;
    }

    bool isValidPassword(const string& pass) const {
        return password == pass;
    }

    Line* getLine(int index) {
        if (index >= 0 && index < 3) {
            return &lines[index];
        }
        return nullptr;  // Invalid index
    }
};

// Function prototypes for services
void makeCall(User& loggedUser);
void sendSMS(User& loggedUser);
void rechargeBalance(User& loggedUser);
void changePackage(User& loggedUser);
void transferBalance(User& loggedUser);
void menu();

void makeCall(User& loggedUser) {
    int numberLine;
    string wantedNumber;

    cout << "Choose The Line You Want To Call From: ";
    cin >> numberLine;
    if (loggedUser.lines[numberLine - 1].balance >= 0.25) {
        cout << "Enter The Number You Want To Call: ";
        cin >> wantedNumber;
        if (wantedNumber.length() != 11) {
            cout << "This Number Isn't Found. Please Check and Try Again." << endl;
        } else {
            loggedUser.lines[numberLine - 1].balance -= 0.25;
            printf("Your balance is: %.2f L.E\n", loggedUser.lines[numberLine - 1].balance);
        }
    } else {
        cout << "Your Balance Isn't Enough. Please Recharge." << endl;
    }
}

void sendSMS(User& loggedUser) {
    int numberLine;
    string wantedNumber;
    char message[160];

    cout << "Choose The Line You Want To Text From: ";
    cin >> numberLine;

    cout << "Enter The Number You Want To Text: ";
    cin >> wantedNumber;

    cout << "Write The Message To Send (Maximum 160 Characters): ";
    cin.ignore();  // To clear the buffer
    cin.getline(message, 160);

    if (loggedUser.lines[numberLine - 1].balance >= 0.25) {
        if (wantedNumber.length() == 11) {
            loggedUser.lines[numberLine - 1].balance -= 0.25;
            printf("Message Sent\nYour Balance is: %.2f L.E\n", loggedUser.lines[numberLine - 1].balance);
        } else {
            cout << "This Number Isn't Found. Please Check and Try Again." << endl;
        }
    } else {
        cout << "Your Balance Isn't Enough. Please Recharge." << endl;
    }
}

void rechargeBalance(User& loggedUser) {
    int numberLine;
    string serialNumber;
    int chargeAmount;

    cout << "Choose The Line You Want To Recharge: ";
    cin >> numberLine;

    cout << "Enter Serial Number of 16 Digits: ";
    cin >> serialNumber;

    if (serialNumber.length() != 16) {
        cout << "Invalid Serial Number. Please Check and Try Again." << endl;
    } else {
        cout << "Enter Charge Amount: ";
        cin >> chargeAmount;
        loggedUser.lines[numberLine - 1].balance += chargeAmount;
        printf("Your Balance is Now: %.2f L.E\n", loggedUser.lines[numberLine - 1].balance);
    }
}

void changePackage(User& loggedUser) {
    int numberLine;
    int packageChoice;

    cout << "Choose The Line You Want To Change Package For: ";
    cin >> numberLine;

    cout << "1 - Flexat (100 L.E)\n2 - DragonBytes (50 L.E)\n3 - Business (200 L.E)\nChoose a Package: ";
    cin >> packageChoice;

    if (packageChoice == 1 && loggedUser.lines[numberLine - 1].balance >= 100) {
        loggedUser.lines[numberLine - 1].packageType = "Flexat";
        loggedUser.lines[numberLine - 1].balance -= 100;
        printf("Package Changed to Flexat. Your Balance is Now: %.2f L.E\n", loggedUser.lines[numberLine - 1].balance);
    } else if (packageChoice == 2 && loggedUser.lines[numberLine - 1].balance >= 50) {
        loggedUser.lines[numberLine - 1].packageType = "DragonBytes";
        loggedUser.lines[numberLine - 1].balance -= 50;
        printf("Package Changed to DragonBytes. Your Balance is Now: %.2f L.E\n", loggedUser.lines[numberLine - 1].balance);
    } else if (packageChoice == 3 && loggedUser.lines[numberLine - 1].balance >= 200) {
        loggedUser.lines[numberLine - 1].packageType = "Business";
        loggedUser.lines[numberLine - 1].balance -= 200;
        printf("Package Changed to Business. Your Balance is Now: %.2f L.E\n", loggedUser.lines[numberLine - 1].balance);
    } else {
        cout << "Not Enough Balance. Please Recharge.\n";
    }
}

void transferBalance(User& loggedUser) {
    int numberLine;
    string wantedNumber;
    int transferAmount;

    cout << "Choose The Line You Want To Transfer From: ";
    cin >> numberLine;

    cout << "Enter The Number You Want To Transfer To: ";
    cin >> wantedNumber;

    if (wantedNumber[3] == '5') {
        cout << "Enter The Amount You Want To Transfer: ";
        cin >> transferAmount;

        if (loggedUser.lines[numberLine - 1].balance >= transferAmount) {
            loggedUser.lines[numberLine - 1].balance -= transferAmount;
            // Assuming transfer is done successfully
            cout << "Transfer Successful!\nYour Balance is Now: " << loggedUser.lines[numberLine - 1].balance << endl;
        } else {
            cout << "Your Balance Isn't Enough. Please Recharge." << endl;
        }
    } else {
        cout << "This Number Isn't On The Same Network. Please Choose Another Number on Same Network." << endl;
    }
}

void menu() {
    cout << "Choose a Service: " << endl;
    cout << "1 - Make a Call" << endl;
    cout << "2 - Send SMS" << endl;
    cout << "3 - Recharge Balance" << endl;
    cout << "4 - Change Package" << endl;
    cout << "5 - Transfer Balance" << endl;
}

int main() {
    User users[4] = {
        {"user1", "user1@gmail.com", "USER1", "user1pass", "Nasr City, Cairo, Egypt", {{"01150154760", "Flexat", 1, {25, 5, 2020}}, {"01152584970", "Buisness", 5, {25, 6, 2020}} }},
        {"user2", "user2@gmail.com", "USER2", "user2pass", "Fifth Settlement, Cairo, Egypt", {{"01150154761", "Flexat", 1, {25, 5, 2020}}, {"01152584971", "Buisness", 5, {25, 6, 2020}} }},
        {"user3", "user3@gmail.com", "USER3", "user3pass", "Semouha, Alexandria, Egypt", {{"01150154762", "Flexat", 1, {25, 5, 2020}}, {"01152584972", "Buisness", 5, {25, 6, 2020}} }},
        {"user4", "user4@gmail.com", "USER4", "user4pass", "Mohandsen, Giza, Egypt", {{"01150154763", "Flexat", 1, {25, 5, 2020}}, {"01152584973", "Buisness", 5, {25, 6, 2020}} }}
    };

    string id, password;
    bool isFound = false;
    User loggedUser;

    // User login
    while (!isFound) {
        cout << "Enter Your ID: ";
        cin >> id;

        cout << "Enter Your Password: ";
        cin >> password;

        for (int i = 0; i < 4; i++) {
            if (users[i].ID == id && users[i].isValidPassword(password)) {
                isFound = true;
                loggedUser = users[i];
                break;
            }
        }

        cout << (isFound ? "\nWelcome " + loggedUser.name + "\n" : "Your ID or Password isn't correct. Please check and try again.") << endl;
    }

    // Display User Info
   
