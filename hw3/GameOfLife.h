/* Name: Daniel Lubuguin
   Assignment: CS4000 Assignment 3
   File: GameOfLife.h
   Function: Provides a class, GameOfLife, that takes a board of live and dead cells and iterates through the game of life
*/


#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <thread>
using namespace std;
//this structure is just a simple way to store the coordinates of the current item
class Matrixlocation{
	int x;
	int y;
	public:
	Matrixlocation(int i,int j){x = i;y = j;}
	Matrixlocation(){x = 0;y=0;}
	int getx(){return x;}
	int gety(){return y;}
	void next(int n);
};

//basically an iterator for the matrix
void Matrixlocation::next(int n){
	if (x < n-1){
		x += 1;
	}
	else if (y < n-1){
		x = 0; 
		y += 1;
	}
	else{
		x = -1000000;
		y = -1000000;
	}
}


//This class hopes to store two board states, one current and one next, one modifiable and then the modifiable one is pushed onto the old one.
class GameOfLife{
	public:
	vector<vector<int> > SimulateLife(vector<vector<int> > &board, int life_cycles);
	GameOfLife();
	private:
	int n;
	vector<vector<int> > currentboard;
	vector<vector<int> > nextboard;
	void aliveneighbors(Matrixlocation m);
};

GameOfLife::GameOfLife(){
	currentboard.clear();
}


//Function: SimulateLife 
//Purpose: Takes an argument of a matrix which has integers that represent alive and dead cells
//uses Conway's rules with game of life to iterate through generation by generation, 
//where life_cycles is the amount of generations to run through
//Return: A finished GameOfLife board
vector<vector<int> > GameOfLife::SimulateLife(vector<vector<int> > &board, int life_cycles){
	n = board.size();
	currentboard = board;
	nextboard.resize(n);
	for (int i = 0;i < n;i++){
		nextboard[i].resize(n);	
	}
	//loop for how many life cycles need to happen
	for (int i = 0;i < life_cycles;i++){
		Matrixlocation cursor;
		//loop that divides the amount of iterations by four and does four threads of work.
		for (int j = 0;j < (n/4)+1;j++){
			std::thread first(&GameOfLife::aliveneighbors, this,  cursor);
			first.join();
			cursor.next(n);
			std::thread second(&GameOfLife::aliveneighbors, this, cursor);
			second.join();
			cursor.next(n);
			std::thread third(&GameOfLife::aliveneighbors, this, cursor);
			third.join();
			cursor.next(n);
			std::thread fourth(&GameOfLife::aliveneighbors, this, cursor);
			fourth.join();
			cursor.next(n);
		}
		currentboard = nextboard;
	}
	ofstream fout;
	fout.open("output.out");
	for (int i=0;i<n;i++) {
    for (int j=0;j<n;j++) {
      fout << currentboard[i][j] << " ";
    }
    fout << endl;
  }
	return currentboard;
}	


//this function checks how many neighbors are alive and kills or births a new cell depending on conway's rules.
void GameOfLife::aliveneighbors(Matrixlocation m){
	int x = m.getx();
	int y = m.gety();
	if (x < 0 || y < 0 || x > n || y > n)
		return;
	int alive = 0;
	if (currentboard[x][y] == 2)
		nextboard[x][y] = 2;
	else{
		if (currentboard[(n+x+1)%n][y] > 0)
			alive++;
		if (currentboard[(n+x-1)%n][y] > 0)
			alive++;
		if (currentboard[(n+x-1)%n][(n+y+1)%n] > 0)					
			alive++;
		if (currentboard[(n+x-1)%n][(n+y-1)%n] > 0)
			alive++;
		if (currentboard[(n+x+1)%n][(n+y+1)%n] > 0)
			alive++;
		if (currentboard[(n+x+1)%n][(n+y-1)%n] > 0)
			alive++;
		if (currentboard[x][(n+y+1)%n] > 0)
			alive++;
		if (currentboard[x][(n+y-1)%n] > 0)
			alive++;
		switch(currentboard[x][y]){
			case 2:
				nextboard[x][y] = 2;
				break;
			case 1:
				if (alive >= 4)
					nextboard[x][y] = 0;
				else if (alive <= 1)
						nextboard[x][y] = 0;
				else 
						nextboard[x][y] = 1;
				break;
			case 0:
				if (alive == 3)
					nextboard[x][y] = 1;
				else
					nextboard[x][y] = 0;
					break;
			default:
					std::cout<<"Error in board!"<<endl;
					std::exit(EXIT_FAILURE);
					break;
			}
		}
}