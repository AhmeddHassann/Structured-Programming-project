#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
string wantedNumber = "0";
int numberLine = 0;
struct Date 
{
	int day = 10;
	int month = 5;
	int year = 2020;
};
struct Line 
{
	string mobileNumber;
	string packageType;
	double balance = 0;
	Date date;
};
struct User 
{
	string ID;
	string email;
	string name;
	string password;
	string address;
	Line line[3];
}users[4];

//the following function shows the menu or list of services 
//so the user can choose the number of the service he wants
void menu()
{
	cout << "Choose a Service :" << endl
		<< "1-Call" << endl
		<< "2-SMS" << endl
		<< "3-Recharge" << endl
		<< "4-Change Package" << endl
		<< "5-Transfer Balance" << endl;
}

void chooseLine(string serviceName) 
{
	cout << "Choose The Line You Want To " + serviceName << endl;
}

void neededNumber(string serviceName) 
{
	cout << "Enter The Number You Want To " + serviceName << endl;
}

void wrongNumber() 
{
	cout << "This Number Isn't Found Please Check And Try Again" << endl;
}

void notEnoughBalance() 
{
	cout << "Your Balance Isn't Enough Please Recharge And Try Again" << endl;
}

void changePackageSuccess(User &loggedUser, string packageName, int numberLine) 
{
	cout << "Changed Successfully To " + packageName << endl;
	loggedUser.line[numberLine - 1].packageType = packageName;
}

void makeCall(User& loggedUser, char& serviceContinue) 
{
	chooseLine("Call From");
	cin >> numberLine;
	if (loggedUser.line[numberLine - 1].balance >= 0.25) 
	{
		neededNumber("Call");
		cin >> wantedNumber;
		if (wantedNumber.length() != 11)
		{
			wrongNumber();
		}
		else 
		{
			loggedUser.line[numberLine - 1].balance -= 0.25;
			printf("your balance is : %.2f L.E\n", loggedUser.line[numberLine - 1].balance);
		}
	}
	else
	{
		notEnoughBalance();
	}
}

//this function is used to send Text if the user choose it
//and it check the balance if it is enough and the number he want to text him if it is correct or not
void sendSMS(User& loggedUser, char& serviceContinue)
{
	char message[160];
	chooseLine("Text From");
	cin >> numberLine;

	neededNumber("Text");
	cin >> wantedNumber;

	cout << "Write The Message To Send With Maximum 160 Characters " << endl;
	gets_s(message, 160);
	cin.getline(message, 160);

	if (loggedUser.line[numberLine - 1].balance >= 0.25)
	{

		if (wantedNumber.length() == 11)
		{
			loggedUser.line[numberLine - 1].balance -= 0.25;
			printf("Message Sent \nYour Balance is: %.2f L.E\n", loggedUser.line[numberLine - 1].balance);
		}
		else
		{
			wrongNumber();
		}
	}
	else
	{
		notEnoughBalance();
	}
}

//this function is used to recharge the balance of the user if he choose it
//and it checks the serialNumber if it is correct or Not
void rechargeBalance(User &loggedUser, char &serviceContinue)
{

	string serialNumber;
	int chargeAmount;

	chooseLine("Recharge It");
	cin >> numberLine;

	cout << "Enter Serial Number of 16 Digits (eg: 1234567891234567)" << endl;
	cin >> serialNumber;

	if (serialNumber.length() != 16)
	{
		cout << "Invalid Serial Number, Please Check And Try Again" << endl;
	}
	else
	{
		cout << "Enter Charge Amount" << endl;
		cin >> chargeAmount;
		loggedUser.line[numberLine - 1].balance += chargeAmount;
		printf("Your Balance Is Now : %.2f L.E\n", loggedUser.line[numberLine - 1].balance);
	}
}

// the following function is used when the user wants to change his package or renew its subscribtion 
// and check his balance if it is enough and shows a menu for types of packages if he wanted to change to choose from

void changePackage(User &loggedUser, char &serviceContinue) 
{

	cout << "1-Renew Your Subscription" << endl << "2-Change Package Type" << endl;

	int option; // user chooses to renew or change his package so he choose the number of option
	cin >> option;

	if (option == 1)
	{
		chooseLine("Renew Its Subscription");
		cin >> numberLine;

		printf("Your Package Type is: %s \n", loggedUser.line[numberLine - 1].packageType.c_str());

		if (loggedUser.line[numberLine - 1].packageType == "Flexat" && loggedUser.line[numberLine - 1].balance >= 100)
		{
			loggedUser.line[numberLine - 1].balance -= 100;
			printf("Renew Succesfully, Your Balance is Now: %.2f L.E \n", loggedUser.line[numberLine - 1].balance);
		}

		else if (loggedUser.line[numberLine - 1].packageType == "DragonBytes" && loggedUser.line[numberLine - 1].balance >= 50)
		{
			loggedUser.line[numberLine - 1].balance -= 50;
			printf("Renew Succesfully \nYour Balance is Now: %.2f L.E \n", loggedUser.line[numberLine - 1].balance);
		}

		else if (loggedUser.line[numberLine - 1].packageType == "Buisness" && loggedUser.line[numberLine - 1].balance >= 200)
		{
			loggedUser.line[numberLine - 1].balance -= 200;
			printf("Renew Succesfully \nYour Balance is Now: %.2f L.E \n", loggedUser.line[numberLine - 1].balance);
		}

		else
		{
			notEnoughBalance();
			printf("Your Balance Is : %.2f L.E\n", loggedUser.line[numberLine - 1].balance);
		}
	}

	else if (option == 2) 
	{

		int numberOfPackage;
		cout << "1-Flexat For 100 L.E" << endl << "2-DragonBytes For 50 L.E" << endl << "3-Buisness For 200 L.E" << endl;
		cin >> numberOfPackage;

		chooseLine("Change Its Package");
		cin >> numberLine;

		switch (numberOfPackage)
		{
		case 1:
			if (loggedUser.line[numberLine - 1].balance >= 100)
			{
				loggedUser.line[numberLine - 1].balance -= 100;
				changePackageSuccess(loggedUser, "flexat", numberLine);
				printf("Your Balance is Now: %.2f L.E\n", loggedUser.line[numberLine - 1].balance);
			}
			else
			{
				notEnoughBalance();
			}
			break;

		case 2:
			if (loggedUser.line[numberLine - 1].balance >= 50)
			{
				loggedUser.line[numberLine - 1].balance -= 50;
				changePackageSuccess(loggedUser, "DragonBytes", numberLine);
				printf("Your Balance is Now: %.2f L.E\n", loggedUser.line[numberLine - 1].balance);
			}

			else
			{
				notEnoughBalance();
			}
			break;

		case 3:
			if (loggedUser.line[numberLine - 1].balance >= 200)
			{
				loggedUser.line[numberLine - 1].balance -= 200;
				changePackageSuccess(loggedUser, "Buisness", numberLine);
				printf("Your Balance is Now: %.2f L.E\n", loggedUser.line[numberLine - 1].balance);
			}
			else
			{
				notEnoughBalance();
			}
			break;
		}
	}
}
//this function used when the user wants to transfer balance to another number 
//and it checks if the number is on same network and if the balance is enough to transfer 
void transferBalance(User& loggedUser, char& serviceContinue)
{
	chooseLine("Transfer From");
	cin >> numberLine;

	neededNumber("Transfer To");
	cin >> wantedNumber;

	if (wantedNumber[3] == '5')
	{
		cout << "Enter The Amount You Want To Transfer" << endl;
		int transferBalance;
		cin >> transferBalance;
		int x, y;
		if (loggedUser.line[numberLine - 1].balance >= transferBalance)
		{
			for (int j = 0; j < 4; j++)
			{
				bool isSameNetwork = false;
				for (int q = 0; q < 3; q++)
				{
					if (users[j].line[q].mobileNumber == wantedNumber)
					{
						x = j;
						y = q;
						users[x].line[y].balance += transferBalance;
						loggedUser.line[numberLine - 1].balance -= transferBalance;
						printf("Transfer Successfully Your Balance is Now: %.2f L.E \n", loggedUser.line[numberLine - 1].balance);
						printf("And His Balance Is Now: %.2f L.E \n", users[x].line[y].balance);
						isSameNetwork = true;
					}
				}
				if (isSameNetwork)
				{
					break;
				}
			}
		}
		else
		{
			notEnoughBalance();
			printf("your balance is : %.2f L.E \n", loggedUser.line[numberLine - 1].balance);
		}
	}
	else {
		cout << "This Number Isn't On The Same Network Please Choose Another Number on Same Network" << endl;
	}
}

int main()
{
	users[0] = { "user1","user1@gmail.com","USER1","user1pass","Nasr City, Cairo, Egypt",{{"01150154760","Flexat",1,{25,5,2020}},{"01152584970","Buisness",5,{25,6,2020}} }};
	users[1] = { "user2","user2@gmail.com","USER2","user2pass","Fifth Settlement, Cairo, Egypt",{{"01150154761","Flexat",1,{25,5,2020}},{"01152584971","Buisness",5,{25,6,2020}},{"01158864781","DragonBytes",10,{25,7,2020 }} } };
	users[2] = { "user3","user3@gmail.com","USER3","user3pass","Semouha, Alexandria, Egypt",{{"01150154762","Flexat",1,{25,5,2020}},{"01152584972","Buisness",5,{25,6,2020}} } };
	users[3] = { "user4","user4@gmail.com","USER4","user4pass","Mohandsen, Giza, Egypt",{{"01150154763","Flexat",1,{25,5,2020}},{"01152584973","Buisness",5,{25,6,2020}} } };
	string id, password;

	bool isFound = false; // to check if the id and password found or not

	User loggedUser;

	while (isFound == false)
	{
		cout << "Enter Your ID: ";
		cin >> id;

		cout << "Enter Your Password: ";
		cin >> password;

		for (int i = 0; i < sizeof(users) / sizeof(User); i++) 
		{
			if (users[i].ID == id && users[i].password == password)
			{
				isFound = true;
				loggedUser = users[i];
			}
		}

		cout << (isFound ? "\nWelcome " + loggedUser.name +"\n" : "Your ID or Password Isnt Correct Please Check and Try Again") << endl;
	}

	char serviceContinue;
	printf("Your Email is: %s \nYour Address is: %s \n\n", loggedUser.email.c_str(), loggedUser.address.c_str());
	for (int j = 0; j < 3; j++) 
	{
		if (loggedUser.line[j].mobileNumber.length() == 11)
		{
			printf("Your Number is : %s \n", loggedUser.line[j].mobileNumber.c_str());
			printf("Your Balance is : %.2f L.E\n", loggedUser.line[j].balance);
			printf("Your Package Type is : %s \n", loggedUser.line[j].packageType.c_str());
			printf("Your Start Line Date is : %d / %d / %d \n", loggedUser.line[j].date.day , loggedUser.line[j].date.month , loggedUser.line[j].date.year);
			printf("Your Renewal Line Date is : %d / %d / %d \n", loggedUser.line[j].date.day+1 , loggedUser.line[j].date.month , loggedUser.line[j].date.year + 1);
		}
		else
		{
			break;
		}
		cout << endl;
	}
			printf("Do You Want A Service? Y/N\n");
			cin >> serviceContinue;

	while (password == loggedUser.password && (serviceContinue == 'y' || serviceContinue == 'Y'))
	{
		menu();
		int Service; cin >> Service;
		switch (Service)
		{
		case 1 :
			makeCall(loggedUser, serviceContinue);
			cout << "Do You Want Another Service Y/N" << endl;
			cin >> serviceContinue;
			break;
		case 2 :
			sendSMS(loggedUser, serviceContinue);
			cout << "Do You Want Another Service Y/N" << endl;
			cin >> serviceContinue;
			break;
		case 3 : 
			rechargeBalance(loggedUser, serviceContinue);
			cout << "Do You Want Another Service Y/N" << endl;
			cin >> serviceContinue;
			break;
		case 4 : 
			changePackage(loggedUser, serviceContinue);
			cout << "Do You Want Another Service Y/N" << endl;
			cin >> serviceContinue;
			break;
		case 5 :
			transferBalance(loggedUser, serviceContinue);
			cout << "Do You Want Another Service Y/N" << endl;
			cin >> serviceContinue;
			break;
		default :
			cout << "Please Enter a Valid Service" << endl;
			cout << "Do You Want Another Service Y/N" << endl;
			cin >> serviceContinue;
			break;
		}
		
	}
}

