//***************************************************************
// File: Hamiltonian_Path.cc
// Author: David W. Juedes
// Modified by: D. Neco Lubuguin
// Class: CS 4000 Parallel computing
// Assignment 2: This program is a modified version of David Juede's Hamiltonian_Path.cc where I attempted to speed it up by utilizing parallelization.
// Purpose: This code finds whether there exists a Hamiltonian Path 
// from one vertex to another in a graph.
//****************************************************************
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <list>
#include <omp.h>
using namespace std;

//utility factorial function
int fact(int n){
	if (n > 1)
	return n*fact(n-1);
	else
		return 1;
	
}


bool valid_tour(vector<list<int> >&adj_list,
                vector<int> &tour) {
  // Tests whether the tour is valid
  // Returns the total distance

  int start = tour[0];
  bool valid = true;
  for (int i=1;i<tour.size();i++) {
    bool found = false;
    // Is there an edge from tour[i-1] to tour[i]
    for (list<int >::iterator p = adj_list[tour[i-1]].begin();
	 p!=adj_list[tour[i-1]].end();++p) {
      if (*p == tour[i]) {
	found = true;
	break;
      }
    }
    if (!found) valid = false;
  }
  return valid;
}


vector<int> Hamiltonian_tour(vector<list<int> >&adj_list, int i1, int j1, bool &found_it) {


  int n = adj_list.size();
  vector<int> perm, result;
  

  bool first_succ = true;
  std::cout<<fact(5);
  for (size_t i=0;i<n;i++) {
    if ((i!=i1)&&(i!=j1)) {
      perm.push_back(i);
    }
  }
 
  bool t_found = false;
  int c = 0;
  #pragma omp parallel for
  //driver parallel for loop which divies up the work to i threads to examine a certain amount of permutations
  for (int i = 0;i < omp_get_num_threads();i++){
	//have each thread i examine permutations only ((n−2)!/p) permutations
	for (int k = i*(fact(n-2)/omp_get_num_threads());k < (i+1)*(fact(n-2)/omp_get_num_threads());k++){
		vector<int> tour;
		vector<int> perm2;
		vector<int> opt;
		perm2.resize(n);
		opt.reserve(n);
		perm2 = perm;
		int f, i, temp;
		temp = k;
		//algorithm to determine kth permutation
		while (!perm2.empty()){
			f = fact(perm2.size()-1);
			i = temp/f;
			temp = temp%f;
			opt.push_back(perm2[i]);
			perm2.erase(perm2.begin()+i);
		}
		tour.resize(n);
		tour[0] = i1;
		tour[n-1] = j1;
		//I modified this i loop to a j since it's more comfortable to have the main parallel driver loop be using i as a label
		for (int j=0;j<n-2;j++) {
		  tour[j+1] = opt[j];
		}
		bool found;
		found = valid_tour(adj_list,tour);
		#pragma omp critical
		{
		if (found && first_succ){
			found_it = true;
			result = tour;
			first_succ = false;
			//break does not work with parallel divied work!
			//break; 
		}
		}
	}
  }
  if (found_it == true || !first_succ){
	  return result;
  }
  else {
  found_it = false;
  return perm;
  }
}

int main() {
  int n;
  int i1;
  int j1;
  cin >> n;
  cin >> i1;
  cin >> j1;
  string line;
  getline(cin,line); // Get the newline
  vector<list<int> > adj_list;
  adj_list.resize(n);

  while (!cin.eof()) {
    getline(cin,line);
    if (!cin.fail()) {
      istringstream in(line);

      int j;
      in >> j;
      char c;
      in >> c;
      assert(c==':');
      while (!in.eof()) {
	int i;
	in >> i;
	if (!in.fail()) {
	  adj_list[j].push_back(i);
	}
      }
    }
  }
  bool found=false;
  vector<int> opt;
  opt = Hamiltonian_tour(adj_list,i1,j1,found);
  if (found) {
    cout << "Tour = ";
    for (int i=0;i<opt.size();i++) {
      cout << opt[i] << " ";
    }
    cout << endl;
  } else {
    cout << "No Hamiltonian Tour" << endl;
  }

}
