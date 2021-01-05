#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Account.h"
#include "Transactions.h"

using namespace std; 

Transactions *myTrans = new Transactions(); //creates a transaction object 
void FileInput(string path); //calls the input for file 

int main(){
    FileInput("BankTransIn.txt");
    myTrans->process(); //process transactions 
    myTrans->printAll(); //print all of the transactions 
    return 0; 
}

void FileInput(string path){
    ifstream in;
	string full = "";
	vector<string> info;

	in.open(path); //open file 

	while (!in.eof()){
		in >> full;
		info.push_back(full); //push the commands into a vector 

	//identifies the opearation and splits the substring 
		if (info[0] == "T"){
			
			in >> full;			
			info.push_back(full.substr(0, full.length() - 1));
			
			info.push_back(full.substr(full.length() - 1,		
				full.length() - 1));

			in >> full;			
			info.push_back(full);

			in >> full;		
			info.push_back(full.substr(0, full.length() - 1));

			info.push_back(full.substr(full.length() - 1,			
				full.length() - 1));
		}else if (info[0] == "O"){
			
			in >> full;		
			info.push_back(full);

			in >> full;			
			info.push_back(full);
			
			in >> full;			
			info.push_back(full);
		}else if (info[0] == "H"){
			in >> full;			
			if (full.length() == 5){
				info.push_back(full.substr(0, full.length() - 1));
				info.push_back(full.substr(full.length() - 1,		
					full.length() - 1));
			}else{
				info.push_back(full);
			}
        }else{
			in >> full;
			info.push_back(full.substr(0, full.length() - 1));

			info.push_back(full.substr(full.length() - 1,
				full.length() - 1));

			in >> full;
			info.push_back(full);
		}
		myTrans->addQueue(info);
		info.clear(); //clears the vector 
	}

}
