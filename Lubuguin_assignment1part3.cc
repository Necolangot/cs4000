//********************************************************
//File: Assignment1Part3.cc
//By D. Neco Lubuguin
// Using Professor Juedes' Read_Input.cc
// This file takes an input of a matrix alongside a modulo factor and finds the greatest product after
//***********************************************************
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cassert>
#include <climits>
using namespace std;

int find_max(vector< vector< int > > matrix, int m, int n, int q);

//***************************************************************
// Function read_q(istream &in) 
// Parameters: istream in --- 
// Return value: q
// Purpose: Read the value q (the modulus for the assigment)
//****************************************************************
int read_q(istream &in) {
  int q;
  in >> q;
  return q;
}
//***************************************************************
// Function read_m(istream &in) 
// Parameters: istream in --- 
// Return value: m
// Purpose: Read the value m (the number of values in the product)
//****************************************************************
int read_m(istream &in) {
  int m;
  in >> m;
  return m;
}
//***************************************************************
// Function read_M(istream &in) 
// Parameters: istream in --- 
// Return value: vector<vector<int> > M
// Purpose: Read the value M, the matrix, which exists to the end of the 
// input.
// Assumption: each row of the matrix is stored on a line by itself.
//****************************************************************
vector<vector<int> > read_M(istream &in) {
  string line;
  vector<vector<int> > M;
  
  while (!in.eof()) {
    getline(in,line);
    if (!in.fail()) {
      istringstream in1(line);
      vector<int> row;
      while (!in1.eof()) {
	int x;
	in1 >> x;
	if (!in1.fail()) {
	  row.push_back(x);
	}
      }
      M.push_back(row);
    }
  }


  return M;
}
 
int main() {
  int q;
  int m;
  vector<vector<int> > M;
  m = read_m(cin);
  q = read_q(cin);
  string line;
  getline(cin,line);
  assert(line == "");
	M = read_M(cin);
  cout<<find_max(M, m, M.size(), q)<<endl;
  cout << M.size() << endl;
}
  
  
 
//***************************************************************
// Function find_max(vector< vector< int > > matrix, int m, int n, int q)
// Parameters: a vector of vectors matrix, int m, n, and q used to determine loop iterations --- 
// Return value: int max
// Purpose: Find the largest product of m items in a row of matrix modulo q
//****************************************************************  
int find_max(vector< vector< int > > matrix, int m, int n, int q){
	int max = INT_MIN;
	int temp = 1;
	//parallel for loop to run this in parallel
	#pragma omp parallel for
	for (int i = 0;i < n;i++){
		for (int j = 0; j < n;j++){
			//check horizontal
			if ((j - m) >= -1){		
				//critical to prevent racing problems
				#pragma omp critical
				{
				temp = 1;
				for (int k = 0;k < m;k++)
					temp *= matrix[i][j-k];
				temp %= q;
				if (temp> max)
					max = temp;
				}
			}
			//check vertical 
			if ((i - m) >= -1){
				#pragma omp critical
				{
				temp = 1;
				for (int k = 0;k < m;k++)
					temp *= matrix[i-k][j];
				temp %= q;
				if (temp> max)
					max = temp;
				}
			}
			//check diagonal
			if ((i - m) >= -1 && (j - m) >= -1)  
            { 
				#pragma omp critical
				{
				temp = 1;
				for (int k = 0;k < m;k++){
					temp *= matrix[i-k][j-k];
				}
				temp %= q;
				if (temp> max)
					max = temp;
				}
            }
			//check anti-diagonal
			if ((i - m) >= -1 && (j + m) <= n)
			{
				#pragma omp critical
				{
				temp = 1;
				for (int k = 0;k < m;k++)
					temp *= matrix[i-k][j+k];
				temp %= q;
				if (temp> max)
					max = temp;
				}
			}
			
		}
	}
	return max;
}
