/**
 * Description: Interface for BinarySearchTree
 * @author: Shubham Kamboj 
 * @version date: December 3, 2020
 * */

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include "Account.h"
#pragma once
using namespace std;


class BinarySearchTree{

    friend ostream& operator<<(ostream& output, const BinarySearchTree& myTree); //ostream overload 
    //declare a node class that holds left, right and account 
    struct Node{
        Account *account;
        Node *right;
        Node* left;
    };
    private:
    Node *root; //beginning of tree 
    //helper methods that use recursion 
    Account* searchRecur(Node *input, const Account &toFind) const; 
	void insertRecur(Node *&input, Account *toFind);
	void printRecur(Node* input);

    public:
    BinarySearchTree(); //constructor 
    ~BinarySearchTree(); //destructor 
    
    bool Insert(Account *myAccount); //inserts the account in the tree 
    bool Retrieve(const Account& toFind, Account* &myAccount) const; //retrievs the account in the tree 
    void Display() const; //displays the tree 
    bool isEmpty() const;  //checks to see if the tree is empty 
    void Empty();  //empties the tree 
    void print();  //prints the tree 
};

#endif