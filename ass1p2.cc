#include <iostream>
#include <omp.h>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

void print(vector< vector<int> > matrix,int n);

int find_max(vector< vector< int > > matrix, int p, int n);

int main(){
	int m, q,n = 0, input;
	
	std::cin>>m;
	std::cin>>q;
	vector < vector<int> > matrix;
	vector<int> temp;
	while (std::cin>>input){
		temp.clear();
		temp.push_back(input);
		while (std::cin.peek() != '\n'){
			cin>>input;
			temp.push_back(input);
		}
		matrix.push_back(temp);
		n++;
	}
	print(matrix, n);
	int max = find_max(matrix, m % q, n);
	std::cout<<std::endl<<max<<std::endl;
}

void print(vector< vector<int> > matrix,int n){
	for (int i = 0;i < n;i++){
		for (int j = 0;j< n;j++){
			cout<<matrix[i][j] << "\t";
		}
		cout<<endl;
	}
}

int find_max(vector< vector< int > > matrix, int p, int n){
	int max = INT_MIN;
	int temp;
	cout<<p<<endl;
	for (int i = 0;i < n;i++){
		for (int j = 0; j < n;j++){
			if ((j - p) >= 0){
				temp = 1;
				for (int k = 0;k < p;k++)
					temp *= matrix[i][j-k];
				if (temp > max)
					max = temp;
			}
			if ((i - p) >= 0){
				temp = 1;
				for (int k = 0;k < p;k++)
					temp *= matrix[i-k][j];
				if (temp > max)
					max = temp;
			}
			if ((i - p) >= 0 && (j - p) >= 0)  
            { 
				temp = 1;
				for (int k = 0;k < p;k++){
					temp *= matrix[i-k][j-k];
					cout<<temp<<endl;
				}
				if (temp > max)
					 max = temp;
				
            }
		}
	}
	return max;
}