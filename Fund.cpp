/**
 * Description: Implementation for Fund
 * @author: Shubham Kamboj 
 * @version date: December 3, 2020
 * */

#include "Fund.h"

//constructor for fund 
Fund::Fund(string fundType){
    this->fundType = fundType;
    this->amount = 0;
}

//destructor for fund 
Fund::~Fund(){}

//adds the fund 
bool Fund::addFund(int a){
    this->amount += a;
    return true; 
}

//subtracts the fund 
bool Fund::subtractFund(int s){
    if(s > this->amount){
        return false; 
    }else{
        this->amount = amount - s;
        return true; 
    }
}

//records the transaction for the fund 
bool Fund::recordTrans(string record){
    fundTransactions.push_back(record);
    return true; 
}

//getter for amount 
int Fund::getAmount() const{
    return amount;
}

//getter for type of fund 
string Fund::getFundType() const{
    return this->fundType;
}

//gets all the transactiosn for the fund 
vector<string> Fund::getFundTransactions() const{
    return fundTransactions;
}

//o stream overload for fund 
ostream& operator<<(ostream& output, const Fund& myFund){
    output << myFund.getFundType() << ": $" << myFund.getAmount() << endl;
	for (int i = 0; i < myFund.fundTransactions.size(); i++){
	    output << myFund.fundTransactions[i] << endl;
	}
	return output;
}
