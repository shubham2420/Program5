/**
 * Description: Implementation for Account
 * @author: Shubham Kamboj 
 * @version date: December 4, 2020 
 * */

#include "Account.h"

//constructor for account that assigns the first and last name while populating fund array 
Account::Account(string first, string last, int ID){
    this->first = first;
    this->last = last; 
    this->ID = ID; 
    Fund* moneyMarket = new Fund("Money Market");
    Fund* primeMoneyMarket = new Fund("Prime Money Market");
    Fund* longTermBond = new Fund("Long-Term Bond");
    Fund* shortTermBond = new Fund("Short Term Bond");
    Fund* IndexFund500 = new Fund("500 Index Fund");
    Fund* capitalValueFund = new Fund("Capital Value Fund");
    Fund* growthEquityFund = new Fund("Growth Equity Fund");
    Fund* growthIndexFund = new Fund("Growth Index Fund");
    Fund* valueFund = new Fund("Value Fund");
    Fund* valueStockIndex = new Fund("Value Stock Index");
	//put funds into the array 
    myFunds[0] = moneyMarket;
    myFunds[1] = primeMoneyMarket;
    myFunds[2] = longTermBond; 
    myFunds[3] = shortTermBond;
    myFunds[4] = IndexFund500;
    myFunds[5] = capitalValueFund;
    myFunds[6] = growthEquityFund;
    myFunds[7] = growthIndexFund;
    myFunds[8] = valueFund;
    myFunds[9] = valueStockIndex; 
}

//destructor for account
Account::~Account(){};

//adds the money to the fund and records the transaction 
bool Account::addFund(int fundID, int amount){
	//string to be recorded 
    string toRecord = "D " + to_string(ID) + to_string(fundID) + " " + to_string(amount);
    if (helpAddFund(fundID, amount)){
		myFunds[fundID]->recordTrans(toRecord); //records the transaction 
        return true;
	}else{
        myFunds[fundID]->recordTrans(toRecord + " (Failed)");
		return false;
	}
}

//subtracts the amount from money from the fund and records the transaction 
bool Account::subtractFund(int fundID, int amount){
	//string to be recorded 
	string toRecord = "W " + to_string(ID) + to_string(fundID) + " " + to_string(amount);
    if (helpSubtractFund(fundID, amount)){ 
        return true;
	}else{
        cerr << "ERROR: Not enough funds to withdraw " << amount << " from " << this->first << " " << this->last << " " << 
        myFunds[fundID]->getFundType() << endl;
        myFunds[fundID]->recordTrans(toRecord + " (Failed)");
		return false;
	}
}

//get for first name 
string Account::getFirst() const{
    return this->first;
}

//getter for last name 
string Account::getLast() const{
    return this->last;
}

//getter for ID 
int Account:: getID() const{
    return this->ID;
}

//sends the transaction from one fund to another and records the transaction 
bool Account::sendTransaction(int fundWithdraw, int amount, int fundID, int fundDeposit){
	//string to be recorded 
    string toRecord = "T " + to_string(ID) + to_string(fundWithdraw) + " " + to_string(amount) + " " + to_string(fundID) + to_string(fundDeposit);
    if (helpSubtractFund1(fundWithdraw, amount)){
		myFunds[fundWithdraw]->recordTrans(toRecord); //records the transaction 
        return true;
	}else{
		myFunds[fundWithdraw]->recordTrans(toRecord + " (Failed)");
        cerr << "ERROR: Not enough funds to withdraw " << amount << " from " << this->first << " " << this->last << " " <<
        myFunds[fundWithdraw]->getFundType() << endl;
		return false;
	}
}

//adds the transaction to the specific fund and records the transaction 
bool Account::getTransaction(int fundDeposit, int amount, int fundID, int fundWithdraw){
	//string to be recorded 
    string toRecord = "T " + to_string(ID) + to_string(fundWithdraw) + " " + to_string(amount) + " " + to_string(fundID) + to_string(fundDeposit);
    if (helpAddFund(fundDeposit, amount)){
		myFunds[fundDeposit]->recordTrans(toRecord); //records teh transaction 
        return true;
	}else{
		myFunds[fundDeposit]->recordTrans(toRecord + " (Failed)");
        cerr << "ERROR: Not enough funds to withdraw " << amount << " from " << this->first << " " << this->last << " " <<
        myFunds[fundDeposit]->getFundType() << endl;
		return false;
	}
}

//prints out all the transaction history for the account 
void Account::getAllTransactions(int ID, int fundType){
    vector<string> output; //dummy vector 

	if (fundType == -1){
		cout << "Transaction History for " << getFirst() << " " << getLast() << " by fund." << endl;
		for (int i = 0; i <= 9; i++){
			output = myFunds[i]->getFundTransactions();
			if (output.size() != 0)
			{
				cout << myFunds[i]->getFundType() << ": $"; //prints the individual fund transactions 
				cout << myFunds[i]->getAmount() << endl;

				for (auto go = output.begin(); go < output.end(); go++)
				{
					cout << "  " + *go << endl;
				}
			}
		}
	}else{
		cout << "Transaction History for " + getFirst() +  " " + getLast();
		cout << " " << myFunds[fundType]->getFundType() << ": $" << myFunds[fundType]->getAmount() << endl;

		output = myFunds[fundType]->getFundTransactions();
		for (auto go = output.begin(); go < output.end(); go++)
		{
			cout << "  " + *go << endl;
		}

	}
}

//implementation to see if one account is less than the other
bool Account::operator<(const Account &otherAcc) const{
    if (this->getID() < otherAcc.getID()){
		return true;
	}else{
		return false;
	}
}

//implementation to see if one account is equal to the other 
bool Account::operator==(const Account &otherAcc) const{
    if (this->getID() == otherAcc.getID()){
		return true;
	}else{
		return false;
	}
}

//takes out from the other corresponding fund if one fund doesnt have enough money 
bool Account::FundAdjustment(int myFund, int amount){
    int otherFund;
	string toRecord = "W " + to_string(ID) + to_string(myFund) + " ";

	switch (myFund)
	{
	case 0:
		otherFund = 1;
		break;
	case 1:
		otherFund = 0;
		break;
	case 2:
		otherFund = 3;
		break;
	case 3:
		otherFund = 2;
		break;
	default:
		return false;
	}

	string toRecord1 = "W " + to_string(ID) + to_string(otherFund) + " ";
	
	int total = myFunds[myFund]->getAmount() - amount;
	if (total < 0)	
	{
		if (myFunds[otherFund]->getAmount() >= abs(total))	
		{
			if (myFunds[otherFund]->subtractFund(abs(total))){
				myFunds[myFund]->recordTrans(toRecord + to_string(myFunds[myFund]->getAmount()));
				myFunds[myFund]->addFund(abs(total));
				myFunds[otherFund]->recordTrans(toRecord1 + to_string(abs(total)));
			}else{
				return false;
			}
			return myFunds[myFund]->subtractFund(amount);
		}
	}else{
		myFunds[myFund]->recordTrans(toRecord + to_string(amount));
		return myFunds[myFund]->subtractFund(amount);
	}
	return true;
}

//helper method for adding funds 
bool Account::helpAddFund(int myFund,int amount){
    if (myFund >= 0 && myFund <= 9){
		myFunds[myFund]->addFund(amount);
		return true;
	}else{
		return false;
	}
}

//helper method for subtracting funds 
bool Account::helpSubtractFund(int myFund, int amount){
	string toRecord = "W " + to_string(ID) + to_string(myFund) + " " + to_string(amount);
    if (myFund < 0 || myFund > 9){
		cerr << "ERROR: " << myFund <<  " not a valid input" << endl;
		return false;
	}

	for (int i = 0; i< 10;i++){

	}
	if (myFund == 0){
		FundAdjustment(myFund, amount);
	}
	else if (myFund == 1){
		FundAdjustment(myFund, amount);
	}else if (myFund == 2){
		FundAdjustment(myFund, amount);
	}else if (myFund == 3){
		FundAdjustment(myFund, amount);
	}else
		if (myFunds[myFund]->subtractFund(amount)){
			myFunds[myFund]->recordTrans(toRecord);
			return true;
		}else{
			return false;
		}

	return true;
}

//helper method for subtracting funds for transaction method 
bool Account::helpSubtractFund1(int myFund, int amount){
	string toRecord = "W " + to_string(ID) + to_string(myFund) + " " + to_string(amount);
    if (myFund < 0 || myFund > 9){
		cerr << "ERROR: " << myFund <<  " not a valid input" << endl;
		return false;
	}

	for (int i = 0; i< 10;i++){

	}
	if (myFund == 0){
		FundAdjustment(myFund, amount);
	}
	else if (myFund == 1){
		FundAdjustment(myFund, amount);
	}else if (myFund == 2){
		FundAdjustment(myFund, amount);
	}else if (myFund == 3){
		FundAdjustment(myFund, amount);
	}else
		if (myFunds[myFund]->subtractFund(amount)){
			return true;
		}else{
			return false;
		}

	return true;
}

//output overload for account class 
ostream& operator<<(ostream& output, const Account& myAccount){
	output << myAccount.getFirst() << " " << myAccount.getLast() << " Account ID: " << myAccount.getID() << endl;

	for (int i = 0; i <= 9; i++)
	{	
		vector<string> tempR = myAccount.myFunds[i]->getFundTransactions();
		string temp1 = myAccount.myFunds[i]->getFundType();
		int temp2 = myAccount.myFunds[i]->getAmount();

		output << temp1 << ": $" << temp2 << endl;
	}
	return output;
}