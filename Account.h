/**
 * Description: Interface for Account
 * @author: Shubham Kamboj 
 * @version date: December 3, 2020
 * */

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <vector>
#include "Fund.h"
#include <string>
#pragma once
using namespace std;

class Account{

    friend ostream& operator<<(ostream& output, const Account& myAccount);

    private:
    string first; // stores the first name 
    string last; //stores the last name 
    int ID; //stores the id of the account 

    //helper methods for adding and subtracting funds 
    bool helpAddFund(int myFund, int amount);
    bool helpSubtractFund(int myFund, int amount);
    bool helpSubtractFund1(int myFund, int amount);
    bool FundAdjustment(int myFund, int amount);
    Fund *myFunds[10]; //stores the different types of funds 
    vector<string> allTransactions; //stores the transaction history in a vector 


    public: 

    Account(string first, string last, int ID); //constructor 
    ~Account(); //destructor 
    bool addFund(int fundID, int amount); //adds funds to a fund 
    bool subtractFund(int fundID, int amount); //withdraws from a fund 
    void getAllTransactions(int ID, int fundType); //prints the history of the account 
    bool sendTransaction(int fundWithdraw, int amount, int fundID, int fundDeposit); //subtract transaction from one fund to another
    bool getTransaction(int fundDeposit, int amount, int fundID, int fundWithdraw); //add transaction from one fund to another 
    string getFirst() const; //returns the first name 
    string getLast() const; //returns the last name 
    int getID() const; //gets the id of the account 
    bool operator<(const Account &otherAcc) const; //overload for less than operator for account 
    bool operator==(const Account &otherAcc) const; //overload for equal to operator for account 
};

#endif
