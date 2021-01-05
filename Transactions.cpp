/**
 * Description: Implementation for Transactions 
 * @author: Shubham Kamboj 
 * @version date: December 3, 2020
 * */

#include "Transactions.h"

//constructor for transaction 
Transactions::Transactions(){}

//destructor for transaction 
Transactions::~Transactions(){}

//adds to the fund if account is found
int Transactions::addFund(int ID, int myFund, int amount){
    Account *temp1 = new Account("temp1", "last", ID);
	Account *temp2;

	if (accounts.Retrieve(*temp1, temp2)){ //retrieves account
		temp2->addFund(myFund, amount); //adds to the fund if account exists 
		return true;
	}else{
		cerr << "ERROR: Account " << ID << " not found. Transaction Failed." << endl; //error statement if account is not found 
		return false;
	}
}

//subtracts from the fund if account is found 
int Transactions::subtractFund(int ID, int myFund, int amount){
    Account *temp1 = new Account("temp1", "last", ID);
	Account *temp2;

	if (accounts.Retrieve(*temp1, temp2)){ //retrieves the account 
		temp2->subtractFund(myFund, amount); //subtracts the amount from the fund if account exists 
		return true;
	}else{
		cerr << "ERROR: Account " << ID << " not found. Transaction Failed." << endl; //error statement if account doesnt exist 
		return false;
	}
}

//opens a new account
bool Transactions::openAcc(string first, string last,int ID){
    Account *temp = new Account(first, last, ID);

	if (accounts.Retrieve(*temp, temp)){ //retrieves account 
		cerr << "ERROR: Account " << ID << " is already open. Transaction refused." << endl; //error statement if account is open 
		return false;
	}else{
		accounts.Insert(temp); //makes a new account and inserts into tree if it doesnt exist 
		return true;
	}
}

//prints out the history 
bool Transactions::history(int ID, int myFund){
    Account *temp = new Account("first", "last", ID);
	Account *temp1;

	
	if (accounts.Retrieve(*temp, temp1)){ //retrieves account 
		temp1->getAllTransactions(ID, myFund); //prints the history of each fund 
        cout << endl;  
		return true;
	}else{
		cerr << "ERROR: Account " << ID << " does not exist. Transaction Failed." << endl;
		return false;
	}
	return true;
}

//transfers funds from one account to another 
bool Transactions::transferFunds(int IDwithdraw, int fundWithdraw, int amount, int IDdeposit , int fundDeposit){
    Account *temp1 = new Account("first", "last", IDwithdraw);
	Account *temp2 = new Account("first", "last", IDdeposit);
	Account *from;
	Account *to;

	if(!accounts.Retrieve(*temp1, from))	{ //if account 1 is not found 
		cerr << "ERROR: Account " << IDwithdraw << " not found. Transferal refused." << endl;
		return false;
	}
    
	if (!accounts.Retrieve(*temp2, to)){ ///if account 2 is not found 
		cerr << "ERROR: Account " << IDdeposit << " not found. Transferal refused." << endl;
		return false;
	}

	if (from->sendTransaction(fundWithdraw, amount, IDdeposit, fundDeposit)){ //sends the transaction 
		to->getTransaction(fundDeposit, amount, IDwithdraw, fundWithdraw); //recieves the transaction 
		return true;
    }else{
		to->getTransaction(fundWithdraw, 0, IDwithdraw, fundDeposit); //recieves the transaction 
		return false;
	}
}

//adds string to the transaction vector 
bool Transactions::addQueue(vector<string> trans){
    input.push(trans);
	return true;
}

//processes the input file 
bool Transactions::process(){
    vector<string> inputFile;

	while (!input.empty())
	{
		inputFile = input.front();

		if (inputFile[0] == "O"){ //opens if O is present 
			openAcc(inputFile[2], inputFile[1], stoi(inputFile[3]));
		}else if (inputFile[0] == "D"){ //deposits if D is present 
			addFund(stoi(inputFile[1]), stoi(inputFile[2]), stoi(inputFile[3]));
		}else if (inputFile[0] == "W"){ //withdraws if W is present 
			subtractFund(stoi(inputFile[1]), stoi(inputFile[2]), stoi(inputFile[3]));
		}else if (inputFile[0] == "T"){ //transfers if T is present 
			transferFunds(stoi(inputFile[1]), stoi(inputFile[2]), stoi(inputFile[3]),
				stoi(inputFile[4]), stoi(inputFile[5]));
		}else if (inputFile[0] == "H"){ //prints the history if H is present 
			if ((inputFile[1].length() == 4) && (inputFile.size() == 3)){
				history(stoi(inputFile[1]), stoi(inputFile[2]));
			}else{
				history(stoi(inputFile[1]), -1);
			}
		}

		input.pop(); 
	}

	cout << endl;
	cout << "Processing Done. Final Balances" << endl;
	return true;
}

//prints the accounts 
void Transactions::printAll(){
    accounts.print();
}

//overload ostream for transaction 
ostream& operator<<(ostream& output, const Transactions& transactions){
    output << transactions;

    return output; 
}