#include <iostream>
#include <vector>


class GameOfLife{
	
	
	public:
	vector<vector<int> > SimulateLife(vector<vector<int> > &board, int life_cycles)
	GameOfLife();
}

vector<vector<int> > SimulateLife(vector<vector<int> > &board, int life_cycles){
	int n = vector.size();
	int rounds = 0;
	vector<vector<int> > nextboard;
	nextboard.resize(n);
	for (int i = 0;i < n;i++){
		nextboard.resize(n, 0);	
	}
	do{
		for (int x = 0;x < n;x++){
			for int y = 0;y < n;y++){
					int alive = 0;
					
					if (board[(x+1)%n][y] > 0)
						alive++;
					if (board[(x+1)%n][(y+1)%n] > 0)
						alive++;
					if (board[x][[(y+1)%n] > 0)
						alive++;
					if (x >= 1){
						if (board[(x-1)%n][y] > 0)
							alive++;
						if (board[(x-1)%n][(y+1)%n] > 0)
							alive++;
						if (y >= 1)
							if (board[x-1%n][(y-1)%n] > 0)
								alive++;
						else 
							if (board[x-1%n][(n+(y-1)%n] > 0)
								alive++;
					}
					else{
						if (board[(n+(x-1))%n][y] > 0)
							alive++;
						if (board[(n+(x-1))%n][(y+1)%n] > 0)
							alive++;
						if (y >= 1)
							if (board[(n+(x-1))%n][(y-1)%n] > 0)
								alive++;
						else
							if (board[(n+(x-1))%n][(n+(y-1))%n] > 0)
								alive++;
					}
					if (y >= 1){
						if (board[(x+1)%n][(y-1)%n] > 0)
							alive++;
						if (board[x][(y-1)%n] > 0)
							alive++
					}
					else{
						if (board[(x+1)%n][(n+(y-1))%n] > 0)
							alive++;
						if (board[x][(n+(y-1))%n] > 0)
							alive++;
					}
					
				}
				else if (board[x][y] == 1){
					
				}
				else if (board[x][y] == 2){
						nextboard[x][y] == 2;
				}
				else{
					std::cout<<"\nError with board! Exiting."<<std::endl;
					exit();
				}
		}
		rounds++;
	}while (rounds < life_cycles);
}	