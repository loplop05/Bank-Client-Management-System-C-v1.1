



#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cctype>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

string const clientsFile = "ClientsData.txt";

struct sClient {
	string accountNumber;
	string pinCode;
	string name;
	string phone;
	double accountBalance;
	bool markForDelete = false;
};



// 1
void mainMenu()
{

	cout << "\n==================================================\n";

	cout << "\t\t Main Menu Screen ";

	cout << "\n==================================================\n";
	cout << "\n  [1] Show Client List." << endl;
	cout << "  [2] Add New Client." << endl;
	cout << "  [3] Delete Client." << endl;
	cout << "  [4] Update Client Info ." << endl;
	cout << "  [5] Find Client." << endl;
	cout << "  [6] Transactions." << endl;
	cout << "  [7] Exit." << endl;
	cout << "==================================================\n";

}

// ==================================================================================

void PrintClientRecord(sClient Client) {
	cout << "|" << setw(15) << left << Client.accountNumber;
	cout << "|" << setw(10) << left << Client.pinCode;
	cout << "|" << setw(40) << left << Client.name;
	cout << "|" << setw(12) << left << Client.phone;
	cout << "|" << setw(12) << left << Client.accountBalance;
}

void PrintAllClientsData(vector <sClient> vClients) {
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_________________________________________________________________________________\n";

	cout << "|" << left << setw(15) << "Account Number";
	cout << "|" << left << setw(10) << "Pin Code";
	cout << "|" << left << setw(40) << "Client Name";
	cout << "|" << left << setw(12) << "Phone";
	cout << "|" << left << setw(12) << "Balance";
	cout << "\n_________________________________________________________________________________\n";

	for (sClient Client : vClients) {
		PrintClientRecord(Client);
		cout << endl;
	}
	cout << "\n_________________________________________________________________________________\n";
}

void printClientCard(sClient c)
{
	cout << "Account Number : " << c.accountNumber << endl;
	cout << "Pin Code       : " << c.pinCode << endl;
	cout << "Name           : " << c.name << endl;
	cout << "Account Balance: " << c.accountBalance << endl;
}


void PrintClientRecordForTransactionsMenu(sClient Client) {
	cout << "|" << setw(15) << left << Client.accountNumber;
	
	cout << "|" << setw(40) << left << Client.name;

	cout << "|" << setw(12) << left << Client.accountBalance;

}


void PrintAllClientsDataForTransactionMenu(vector <sClient> vClients) {
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_________________________________________________________________________________\n";

	cout << "|" << left << setw(15) << "Account Number";
	
	cout << "|" << left << setw(40) << "Client Name";

	cout << "|" << left << setw(12) << "Balance";
	cout << "\n_________________________________________________________________________________\n";

	int sum = 0; 
	for (sClient Client : vClients) {
		PrintClientRecordForTransactionsMenu(Client);
		sum += Client.accountBalance;
		cout << endl;
	}
	cout << "\n_________________________________________________________________________________\n";

	 
	cout << "\t\t\t\t\t\t Total Balances = " << sum << "$ " << endl;
}


// ==================================================================================
vector<string> split(string stLine, string sep) {
	vector<string> vString;
	int pos = 0;
	string newSt;

	while ((pos = stLine.find(sep)) != string::npos) {
		newSt = stLine.substr(0, pos);
		if (newSt != "") {
			vString.push_back(newSt);
		}
		stLine.erase(0, pos + sep.length()); // Remove processed part
	}

	if (stLine != "") {
		vString.push_back(stLine); // Add last part
	}
	return vString;
}

// ==================================================================================
sClient ConvertLineToRecord(string line, string sep = "#//#")
{

	sClient c;

	vector <string> vClientData = split(line, sep);
	c.accountNumber = vClientData[0];
	c.pinCode = vClientData[1];
	c.name = vClientData[2];
	c.phone = vClientData[3];
	c.accountBalance = stod(vClientData[4]);

	return c;

}


vector <sClient> loadClientsDataFromFile(string clientsFile)

{

	fstream myfile;
	vector<sClient> vFileContent;

	myfile.open(clientsFile, ios::in); // Read Mode ; \

	if (myfile.is_open())
	{

		string line;
		sClient client;

		while (getline(myfile, line))
		{

			client = ConvertLineToRecord(line);
			vFileContent.push_back(client);
		}


		myfile.close();
	}

	return vFileContent;
}


string ConvertRecordToLine(sClient client, string seprator = "#//#")
{
	string recordLine = "";
	recordLine += client.accountNumber + seprator;
	recordLine += client.pinCode + seprator;
	recordLine += client.name + seprator;
	recordLine += client.phone + seprator;
	recordLine += to_string(client.accountBalance);
	return recordLine;
}



// ==================================================================================

bool checkIfAccNumExist(string accountNumber , string filename)
{
	fstream myfile; 
	sClient c; 
	vector <sClient> vClients; 
	myfile.open(filename, ios::in); 

	if (myfile.is_open())
	{
		string line; 

		while (getline(myfile, line))
		{

			c = ConvertLineToRecord(line);

			if (c.accountNumber == accountNumber)
			{
				myfile.close();
				return true; 

			}
			vClients.push_back(c);


		}

		myfile.close(); 
	}

	return false;

}


sClient addNewCleint()
{

	sClient c;
	cout << "\n=======================================\n";
	cout << "Add New Client Screen :" << endl;
	cout << "=======================================" << endl;

	cout << "Enter Account number :" << endl;
	getline(cin >> ws, c.accountNumber);
	while (checkIfAccNumExist(c.accountNumber, clientsFile)) {


		cout << "\nClient with [" << c.accountNumber << "] already exists, Enter another Account Number? ";      
		getline(cin >> ws, c.accountNumber);


	}
	cout << "Enter Pin Code ? " << endl;
	getline(cin, c.pinCode);

	cout << "Enter Name ? " << endl;
	getline(cin, c.name);

	cout << "Enter Phone ?" << endl;
	getline(cin, c.phone);

	cout << "Enter Account Balance ? " << endl;
	cin >> c.accountBalance;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << endl;
	cout << "\n=======================================\n";
	cout << "CLIENT ADDED SUCCECFULLY !" << endl;
	cout << "=======================================";
	return c;
}

// ==================================================================================




// ==================================================================================



vector <sClient> saveClientDataToFile(string filename, vector<sClient> vClients)
{


	fstream myfile; 


	myfile.open(filename, ios::out);

	sClient c; 
		string line; 
	if (myfile.is_open())
	{

		for (sClient c : vClients)
		{

			if (c.markForDelete == false)
			{

				line = ConvertRecordToLine(c);

				myfile << line << endl; 
			}


		}


		myfile.close();


	}


	return vClients; 


}



// ==================================================================================
// ==================================================================================
bool searchForAccountByNumber(string accountNumber, sClient &client)
{
	vector<sClient> vClients = loadClientsDataFromFile(clientsFile);

	for (sClient c : vClients)
	{


		if (c.accountNumber == accountNumber)
		{
			client = c; 
			return true; 
		}

	}

	return false; 

}

bool markUpforDeleteByAccountNumber(string accountNumber, vector<sClient>& vClients)
{

	

	for (sClient &c : vClients)
	{

		if (c.accountNumber == accountNumber)
		{

			c.markForDelete = true;
			return true; 

		}



	}


	return false; 

}

bool deleteAccountByNumber(string accountNumber, vector<sClient>& vClients)
{


	sClient client; 


	char answer = 'n';


	if (searchForAccountByNumber(accountNumber, client))
	{

		printClientCard(client); 

		cout << endl; 
		cout << "Do you want to delete This Client ?" << endl; 

		cin >> answer; 

		if (answer == 'y' || answer == 'Y')
		{

			if (markUpforDeleteByAccountNumber(accountNumber, vClients))
			{

				cout << "\n_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n";
				cout << "       Account Deleted Succefully !  " << endl; 
				cout << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n";
				
				saveClientDataToFile(clientsFile, vClients);
				return true; 



			}
			else {


				cout << "No Account with this number ! " << endl; 
				return false;
			}
			

		}



	}
	else {


		cout << "No Account with this number ! " << endl;
		return false;
	}


	return false; 



}

// ==================================================================================
// ==================================================================================

sClient changeClientRecord(string accountNumber)
{

	sClient c;
	c.accountNumber = accountNumber;

	cout << "Enter Pin Code ? " << endl;
	getline(cin, c.pinCode);

	cout << "Enter Name ? " << endl;
	getline(cin, c.name);

	cout << "Enter Phone ?" << endl;
	getline(cin, c.phone);

	cout << "Enter Account Balance ? " << endl;
	cin >> c.accountBalance;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return c;
}

bool searchAccountByAccNumber(string accountNumber, sClient client )
{

	vector<sClient> vClients = loadClientsDataFromFile(clientsFile);
	


	for (sClient c : vClients)
	{

		if (c.accountNumber == accountNumber)
		{


			client = c ; 
			return true; 

		}




	}

	return false; 





}

bool updateAccountByAccountNumber(string accountNumber, vector<sClient>& vClients)
{

	sClient c; 

	if (searchForAccountByNumber(accountNumber, c))
	{
	
		printClientCard(c);
	char answer; 
	
	cout << "\n Are you sure you want to update the client data ? " << endl;

	cin >> answer;
	cin.ignore(1, '\n');

	if (answer == 'y' || answer == 'Y')
	{

		
		
			
		
		for (sClient &client : vClients)
		{

			if (client.accountNumber == accountNumber)
			{
				client = changeClientRecord(accountNumber);
				break;
			}

		}

		saveClientDataToFile(clientsFile, vClients);
		cout << "\n\nClient Updated Successfully.";
		return true; 

		}




	}





	return false; 




}



void AddingNewClient(vector <sClient> &vClients)
{

	sClient newClient = addNewCleint();
	vClients.push_back(newClient);


	saveClientDataToFile(clientsFile, vClients);

}


void DeletingClient(vector <sClient>& vClients)
{
	string accountNumber; 
	cout << "Enter The Account number you want to delete :" << endl; 
	cin >> accountNumber;
	deleteAccountByNumber(accountNumber, vClients);

}


void updatingClient(vector <sClient>& vClients)
{

	string accountNumber; 

	cout << "Enter the Account Number you want to update it :" << endl; 

	cin >> accountNumber; 

	updateAccountByAccountNumber(accountNumber,vClients);

}


void findClient()
{

	vector<sClient> vClients = loadClientsDataFromFile(clientsFile);
	
	string accNumber; 
	cout << "Enter The Account Number of the Client :" << endl; 
	cin >> accNumber;
	bool found = false; 

	for (sClient c : vClients)
	{


		if (c.accountNumber == accNumber)
		{

			cout << "CLIENT OF NUM (" << accNumber << ") INFO:" << endl;

			printClientCard(c);
			found = true; 
		}



	}

	if (!found)
	{
		cout << "CLIENT OF NUM (" << accNumber << ") NOT FOUND !" << endl;
		cout << "PRESS ANY KEY TO BACK TO THE MENU (:" << endl;

	}

}


// ==================================================================================
//  EXTENSIONS ( PART 2 OF THE PROJECT ) 
// ==================================================================================


void TransactionsMenu()
{


	cout << "=========================================" << endl; 
	cout << "\t TRANSACTIONS MENU " << endl;
	cout << "=========================================" << endl; 

	cout << "\t\t[1] Deposit ." << endl;
	cout << "\t	[2] WithDraw ." << endl;
	cout << "\t	[3] Total Balances ." << endl;
	cout << "\t	[4] Main Menu ." << endl;
	cout << "=========================================" << endl;






}



int addDeposit(string accountNumber, int amount , vector <sClient> &vClients)
{
	
	
	for (sClient &c : vClients)
	{

		if (c.accountNumber == accountNumber)
		{

			
			c.accountBalance += amount; 
			saveClientDataToFile(clientsFile, vClients);

			return c.accountBalance; 
		}



	}


	return -1; 


}

void Depoist(vector <sClient>& vClients)
{

	int number; 
	string accountNumber; 

	cout << "Enter The Account number you want to depoist in :" << endl;
	cin >> accountNumber; 
	cout << "Enter the amount you want to deposit :" << endl;
	cin >> number; 

	int newBalance =  addDeposit(accountNumber, number, vClients);

	if (newBalance != -1)
	{

		cout << number << "$ Added Succecfully to (" << accountNumber << ") Balance" << endl;
		saveClientDataToFile(clientsFile, vClients);

	}

	

}



int addWithDraw(string accountNumber, int amount, vector <sClient>& vClients)
{
	for (sClient& c : vClients)
	{

		if (c.accountNumber == accountNumber)
		{


			if (c.accountBalance > 0 )
			{

				c.accountBalance -= amount;
				saveClientDataToFile(clientsFile, vClients);

				return c.accountBalance;
			}


			if (c.accountBalance < amount)
			{
				cout << "NO SUCH ENOUGH AMOUNT TO WITH DRAW !" << endl;
				cout << "PRESS ANY KEY TO BACK TO THE MAIN MENU (: " << endl;
			}
			
		
			
		}



	}


	return -1;


}



void WithDraw(vector <sClient>& vClients)
{


	int number;
	string accountNumber;

	cout << "Enter The Account number you want to WithDraw From :" << endl;
	cin >> accountNumber;
	
	
	for (sClient& c : vClients)
	{

		if (c.accountNumber == accountNumber) {


			printClientCard(c);

		}

	}






	cout << "\nEnter the amount you want to WithDraw :" << endl;
	cin >> number;

	int newBalance = addWithDraw(accountNumber, number, vClients);

	if (newBalance != -1)
	{

		cout << number << "$ WithDrawed Succecfully to (" << accountNumber << ") Balance" << endl;
		
		
	}
	
	




}



void printTransactionTable(vector <sClient>& vClients)
{

	PrintAllClientsDataForTransactionMenu(vClients);
	

}




// ==================================================================================











void TranSactionsMenuOperation(vector<sClient>& vClients)
{

	

	


	
	int choice;
	
	do {
		TransactionsMenu();

		cout << "Choose What Do You Want To Do ? [1 to 4]" << endl;
		cin >> choice;

		



		system("cls");

		


		switch (choice)
		{

		case 1 :
			Depoist(vClients);
			system("pause>0");
			system("cls");
			break;
			
		case 2 :
			WithDraw(vClients);
			
			system("pause>0");
			system("cls");
			

		case 3 :

			
			printTransactionTable(vClients);
			system("pause>0");
			system("cls");


		case 4 :
			
			cout << "Returning to Main Menu..." << endl;
			cout <<"Press Any Key To Go Back..."<< endl;
			return;

		}
	



	} while (true);


	










}


void mainOperation()
{
	vector <sClient> vClients = loadClientsDataFromFile(clientsFile);

	int choice;
	do {



		mainMenu();




		cout << "Choose What Do You Want To Do ? [1 to 6]" << endl;
		cin >> choice;
		system("cls");





		switch (choice)
		{

		case 1:

			PrintAllClientsData(vClients);
			cout << "\nPress Any key to back to main menu !" << endl;

			system("pause>0");
			system("cls");


			break;


		case 2:

			AddingNewClient(vClients);
		
			system("pause>0");

			system("cls");
			break;

		case 3 : 


			DeletingClient(vClients);

			system("pause>0");

			system("cls");
			break;
		
		case 4 :
			updatingClient(vClients);

			
			system("pause>0");

			system("cls");
			break;
		
		case 5 :
			findClient();

			system("pause>0");

			

		case 6 :
			TranSactionsMenuOperation(vClients);
			system("pause>0");
			system("cls");
		}

		
	} while (choice != 7);

	cout << "Thank You For Using My Program <3" << endl;
}










	
	


int main()
{
	mainOperation();
	system("pause>0");

}
