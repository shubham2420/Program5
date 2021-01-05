/**
 * Description: Implementation for BinarySearchTree 
 * @author: Shubham Kamboj 
 * @version date: December 4, 2020 
 * */

#include "BinarySearchTree.h"

//constructor for binary search tree 
BinarySearchTree::BinarySearchTree(){
    this->root = NULL; //sets the root to null 
}

//destructor for binary search tree 
BinarySearchTree::~BinarySearchTree(){}

//inserts the account in the tree 
bool BinarySearchTree::Insert(Account *myAccount){
    insertRecur(root, myAccount); //helper method 
    return true; 
}

//retrives the specified account that is asked for 
bool BinarySearchTree::Retrieve(const Account& toFind, Account* &myAccount) const{
    Account *temporary = searchRecur(root, toFind); //helper method 

    if(temporary == NULL){
        return false; 
    }else{
        myAccount = temporary; 
        return true; 
    }
}

//display method- no implementation 
void BinarySearchTree::Display() const{}

//makes the binary search tree empty 
void BinarySearchTree::Empty(){
    root = NULL; 
}

//checks to see if the tree is empty 
bool BinarySearchTree::isEmpty() const{
    if(this->root == NULL){
        return true;
    }

    return false;
}

//searches for the specified account using recursion 
Account* BinarySearchTree::searchRecur(Node *input, const Account &toFind) const{
    if (input == NULL){
		return NULL;
    }else if (toFind == *(input->account)){
		return (input->account);
	}else if (toFind < *(input->account)){
		return searchRecur(input->left, toFind);
	}else{
		return searchRecur(input->right, toFind);
	}
}

//inserts the specified account using recursion 
void BinarySearchTree::insertRecur(Node *&input, Account *toFind){
    if (!input){
		input = new Node();
		input->account = toFind;
		return;
	}else if (*toFind < *input->account){
		insertRecur(input->left, toFind);
	}else{
		insertRecur(input->right, toFind);
	}
}

//prints all the accounts in the tree 
void BinarySearchTree::printRecur(Node* input){
    if(input != NULL){
        printRecur(input->left);
        cout << *input->account << endl;
        printRecur(input->right);
    }
}   

//prints the accounts in the tree 
void BinarySearchTree::print(){
    printRecur(this->root);
}
 
//o stream overload for binary search tree 
ostream& operator<<(ostream& output, const BinarySearchTree& myTree){
    output << myTree.root->account;
	return output; 
}