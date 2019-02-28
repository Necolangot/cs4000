#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>

using namespace std;
class GameOfLife{

	
	public:
	vector<vector<int> > SimulateLife(vector<vector<int> > &board, int life_cycles);
	GameOfLife();
	private:
	vector<vector<int> > currentboard;
};

GameOfLife::GameOfLife(){
	currentboard.clear();
}

vector<vector<int> > GameOfLife::SimulateLife(vector<vector<int> > &board, int life_cycles){
	int n = board.size();
	currentboard = board;
	vector<vector<int> > nextboard;
	nextboard.resize(n);
	for (int i = 0;i < n;i++){
		nextboard[i].resize(n);	
	}
	for (int i = 0;i < life_cycles;i++){
		for (int x = 0;x < n;x++){
			for (int y = 0;y < n;y++){
				int alive = 0;
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