/**
 * Description: Interface for Transactions 
 * @author: Shubham Kamboj 
 * @version date: December 3, 2020
 * */

#ifndef Transactions_H
#define Transactions_H

#include <string>
#include <iostream>
#include <queue>
#include "BinarySearchTree.h"
#include "Account.h"
#pragma once

using namespace std; 

class Transactions{

    friend ostream& operator<<(ostream& output, const Transactions& transactions); //ostream overload for transaction
    private: 
        BinarySearchTree accounts;  //tree that holds all the variables 
        queue<vector<string>> input;  //queue of vectors that stores the input 

    public: 
        Transactions(); //constructor 
        ~Transactions(); //destructor 

        int addFund(int ID, int myFund, int amount); //adds the funds 
        int subtractFund(int ID, int myFund, int amount); //subtracts the funds 
        bool openAcc(string first, string last,int ID); //opens a new account 
        bool history(int ID, int myFund); //prints the history of the accounts 
        bool transferFunds(int IDwithdraw, int fundWithdraw, int amount, int IDdeposit , int fundDeposit);// transfers funds from one
                                                                                                            //account to the other 
        bool addQueue(vector<string> trans);//adds the vector to the queue
        bool process(); //processes the transactions 
        void printAll(); //prints the transactions 

};
#endif