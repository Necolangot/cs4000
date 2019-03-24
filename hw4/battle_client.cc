using namespace std;

public enum state{
	vertical,
	dright,
	horizontal,
	dleft,
}
struct boardstate{
	void left_state(int cur_row, int cur_col, vector<vector<int> >& board);
	void right_state(int cur_row, int cur_col, vector<vector<int> >& board);
	state cstate;
};

void left_state(int cur_row, int cur_col, vector<vector<int> >& board){
	switch(cstate){
		case vertical:
			if ((cur_row - 1) < 0 && (cur_col - 1) < 0){
				board[3][3] = 0;
				board[cur_row+1][cur_col+1] = 0;
			}
			if ((cur_row-1) < 0 && (cur_col)
			break;
		case dright:
			if ((cur_row - 1) < 0){
				board[3][cur_col] = 0;
				board[cur_row+1][cur_col] = 0;
			}
			else if ((cur_row + 1) > 3){
				board[0][cur_col] = 0;
				board[cur_row-1][cur_col] = 0;
			}
			else{ 
				board[cur_row+1][cur_col] = 0;
				board[cur_row-1][cur_col] = 0;
			}
			cstate = vertical;
			break;
		case horizontal:

			break;
		case dleft:

			break;
	}
}


void draw_top_matrix(vector<vector<int> > &board,
		     int cur_row,
		     int cur_col) {

  for (int j=0;j<4;j++) {
      move(0,2*j);
      printw("+-");
    }
    move(0,2*4);
    printw("+");
  for (int i=0;i<4;i++) {
    for (int j=0;j<4;j++) {
      move(2*i+1,2*j);
      printw("|");
      move(2*i+1,2*j+1);
      if (board[i][j] == 1) {
	printw(" ");
      } 
	  else if (board[i][j] == 0) {
		printw("X");
      }
	  else if (board[i][j] == 2) {
		printw("H");
      }
	  else if (board[i][j] == 3) {
		printw("M");
      }
	  
    }
    move(2*i+1,2*4);
    printw("|");
    for (int j=0;j<4;j++) {
      move(2*i+2,2*j);
      printw("+-");
    }
    move(2*i+2,2*4);
    printw("+");
  }
  move(2*cur_row+1,2*cur_col+1);
}
      
      


int main(int argc,char *argv[1]) {
	cout << "X args" << argc << endl;
	cout << "Rsp choice = " << argv[1] << endl;
	cout << "server" << argv[2] << endl;
	cout << "port" << argv[3] << endl;
	int portno = atoi(argv[3]);
	boost::asio::io_service my_service;
	tcp::resolver resolver(my_service);
	
	tcp::socket socket(my_service);
  
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(argv[2]),portno));
  std::cout<<"Place your 3x1 Ship: \n";
  int rows;
  int cols;
  int cur_row=0;
  int cur_col=0;
  int ch;
	
  board board1;  
  
  // Screen initialization

  initscr();
  // Clear the screen

  clear();

  // Get the size of the window!
  getmaxyx(stdscr,rows,cols);

  
  cbreak();  // Pass all characters to this program!

  keypad(stdscr, TRUE); // Grab the special keys, arrow keys, etc.
  vector<vector<int> > board;
  	for (int i=0;i<4;i++) {
    vector<int> t;
    for (int j=0;j<4;j++) {
      t.push_back(1);
    }
    board.push_back(t);
  }
  // Paint the row and column markers.
  //paint_markers(rows,cols,10,0,0);
  // Redraw the screen.
  refresh();
	

  draw_top_matrix(board1.getb(),0,0);
  

  // I/O Loop....
  // Stop when the q Key is hit.
  //
  boardstate bs;
  bool placed = false;
  bool finished = false;
	while ((ch = getch())!='q' && !finished) {
		if placed {
			switch(ch){
				case KEY_LEFT:
					bs.left_state(cur_row, cur_col, board);
					break;
				case KEY_RIGHT:
					bs.right_state(cur_row, cur_col, board);
					break;
				case ' ':
					finished = true;
					break;
				case 'q':
				placed = false;
				break;
			}
		}
		else{
			switch (ch) {
			case ' ':  
				board[cur_row][cur_col]=0;
				bs.cstate = vertical;
				if ((cur_row - 1) < 0){
					board[3][cur_col] = 0;
					board[cur_row+1][cur_col] = 0;
				}
				else if ((cur_row + 1) > 3){
					board[0][cur_col] = 0;
					board[cur_row-1][cur_col] = 0;
				}
				else{ 
					board[cur_row+1][cur_col] = 0;
					board[cur_row-1][cur_col] = 0;
				}
			  	draw_top_matrix(board,cur_row,cur_col);
			  	// Redraw the screen.
			  	refresh();
			  	placed = true;
			  	break;
			case KEY_RIGHT:
			  cur_col++;
			  cur_col%=4;
			  draw_top_matrix(board,cur_row,cur_col);
			  // Redraw the screen.
			  refresh();
			  break;
			case KEY_LEFT:
			  cur_col--;
			  cur_col = (4+cur_col)%4;
			  draw_top_matrix(board,cur_row,cur_col);
			  // Redraw the screen.
			  refresh();
			  break;
			case KEY_UP:
			  cur_row--;
			  cur_row=(4+cur_row) % 4;
			  draw_top_matrix(board,cur_row,cur_col);
			  
			  //      paint_markers(rows,cols,10,cur_row,cur_col);
			  // Redraw the screen.
			  refresh();
			  break;
			case KEY_DOWN:
			  cur_row++;
			  cur_row%=4;
			  draw_top_matrix(board,cur_row,cur_col);
					//paint_markers(rows,cols,10,cur_row,cur_col);
			  // Redraw the screen.
			  refresh();
			  break;


		}
 }
  

  


  endwin();
}
