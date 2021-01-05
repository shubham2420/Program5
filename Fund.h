/**
 * Description: Interface for Fund
 * @author: Shubham Kamboj 
 * @version date: December 3, 2020
 * */

#ifndef Fund_H
#define Fund_H

#include <iostream>
#include <vector>
#pragma once
using namespace std;

class Fund{
    friend ostream& operator<<(ostream& output, const Fund& myFund); //ostream overload 

    private:
    string fundType; //declares the type of fund 
    vector<string> fundTransactions; //stores the transactions for the fund 
    int amount; //store steh fund amount 

    public:
    Fund(string fundType); //constructor 
    ~Fund(); //destructor 
    int getAmount() const; //getter for amount
    bool addFund(int amount); //adds amount to fund 
    bool subtractFund(int amount); //subtracts amount from fund 
    bool recordTrans(string record); //records the transaction for the fund
    string getFundType() const; //gets the type of fund 
    vector<string> getFundTransactions() const; //gets the total transactions for the fund 
};

#endif