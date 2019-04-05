#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h>
using namespace std;
bool find_password(string to_crack, vector<string> dictionary){
	
	
}


int main(int argv, char* argc[]){
	ifstream file_1;
	ifstream file_2;
	file_1.open(argc[1]);
	file_2.open(argc[2]);
	vector<string> passwords;
	vector<string> dictionary;
	string temp;
	while (getline(file_1, temp)){
			passwords.push_back(temp);
	}
	while (getline(file_2, temp)){
			dictionary.push_back(temp);
	}
	for(int i = 0;i < passwords.size();i++){
			string dumb_password;
			bool found = find_password(passwords[i], 
	}
	file_1.close();
	file_2.close();
}


