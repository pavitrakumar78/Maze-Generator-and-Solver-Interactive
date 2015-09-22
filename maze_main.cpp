#include<stdio.h>
#include<iostream>
#include<windows.h>
#include<cstdlib>
#include<list>
#include<stack>
#include<vector>
#include<algorithm>
#include<time.h>
#include<set>
#include<cstdlib>
#include<stdlib.h>

#include "Maze.h"

using namespace std;
vector<int> solution;

void displayMaze(int **cells,int y,int x,int solv_type,int vx) {
	/// if solv_type = 1 then prints the maze with solution if solution exists/user solves the maze
	/// if solv_type = 0 just prints the maze
	int dotColor =11;//11
	int wallColor = 14;//15 is white
	int i,j,v;
	cout << endl << endl;
	for (i = 0; i < y; i++) {
		/// draw the UP edge
		for (j = 0; j < x; j++) {
			v = x*i+j;
			if(solv_type==1){
				v = x*i+j;
				if(std::find(solution.begin(), solution.end(), v) != solution.end()) {
					if(((cells[i][j])&2)==0){
						cout <<"+ ";
						SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), dotColor|1);
						cout <<"*";//*
						SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0|wallColor);
						cout <<" ";

					}else{
						SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0|wallColor);
						cout << "+---";
					}
				} else {
					SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0|wallColor);
					cout << ((cells[i][j] & 2) == 0 ?"+   ": "+---");
				}
			}else{
				cout << ((cells[i][j] & 2) == 0 ?"+   ": "+---");
			}
		}
		cout << "+" << endl;
		/// draw the LEFT edge
		for (j = 0; j < x; j++) {
			v = x*i+j;
			if(solv_type==1){
				v = x*i+j;
				if(std::find(solution.begin(), solution.end(), v) != solution.end()) {
					if((cells[i][j] & 4) == 0){
						cout <<" ";
						SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), dotColor|1);
						cout <<"*";//*
						SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0|wallColor);
						cout <<"  ";
					}else{
						cout <<"| ";
						SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), dotColor|1);
						cout <<"*";
						SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0|wallColor);
						cout <<" ";

					}
				} else {
					cout << ((cells[i][j] & 4) == 0 ?"    ": "|   ");
				}
			}else{
				cout << ((cells[i][j] & 4) == 0 ?"    ": "|   ");
			}
		}

		cout << ((cells[i][j-1] & 1)==0?"    ":"|");
		cout << endl;
	}
	for (int j = 0; j < x; j++) {
		cout << "+---";
	}
	cout << "+" << endl;
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0|15);

}
void dispVec(vector<int> temp){
	for (vector<int>::iterator iter = temp.begin(); iter != temp.end(); ++iter) {
		cout << *iter <<",";
	}
	cout << endl;
}



void printMazeArray(int **cells,int w,int h){
	for(int i = 0; i < h; i++){
		for(int col = 0;col<w;col++){
			cout << cells[i][col]<<" ";
		}
		cout << endl;
	}
}




int getUnvisited2(bool **visited,int x,int y,int WIDTH,int HEIGHT,int **cells){
	int v = 999;
	vector<int> a;
	if(x<HEIGHT-1){
		if((visited[x+1][y]==false)){
			if((cells[x][y]&8)==0){
				v = (x+1)*WIDTH+y;
				return v;
			}
		}
	}
	if(x>0){
		if(visited[x-1][y]==false){
			if((cells[x][y]&2)==0){
				v = (x-1)*WIDTH+y;
				return v;
			}
		}
	}
	if(y<WIDTH-1){
		if(visited[x][y+1]==false){
			if((cells[x][y]&1)==0){
				v = x*WIDTH+(y+1);
				return v;
			}
		}
	}
	if(y>0){
		if(visited[x][y-1]==false){
			if((cells[x][y]&4)==0){
				v = x*WIDTH+(y-1);
				return v;
			}
		}
	}
	return 999;
}

vector<int> solve2(int **cells,int x1,int y1,int x2,int y2,int WIDTH,int HEIGHT){
	bool **visited;
	int row,col;
	visited = new bool*[HEIGHT];
	int i,j;
	for(i = 0; i < HEIGHT; i++){
		visited[i] = new bool[WIDTH];
		for(j = 0;j<WIDTH;j++){
			visited[i][j] = false;
		}
	}
	visited[x1][y1] = true;
	stack<int> stk;
	vector<int> sol;
	int v = y1*WIDTH+x1;
	stk.push(v);
	while(!stk.empty()){
		int u_n = getUnvisited2(visited,x1,y1,WIDTH,HEIGHT,cells);
		if(u_n!=999){
			row = u_n/WIDTH;
			col = u_n%WIDTH;
			visited[row][col] = true;
			sol.push_back(u_n);
			stk.push(u_n);
			if(row==x2 && col==y2){
				//cout <<"------------------------------------------>sol FOUND"<<endl;
				//for(vector<int>::iterator it = sol.begin();it!=sol.end();it++){
					//cout <<*it<<" ,";
				//}
				return sol;
			}
		}
		int t_v = stk.top();


		if(t_v==0){
			sol.pop_back();
			int c = sol.back();
			stk.push(c);
			x1 = c/WIDTH;
			y1 = c%WIDTH;
		}else{
			stk.pop();
			x1 = t_v/WIDTH;
			y1 = t_v%WIDTH;
		}
	}
	return sol;
}



bool myfunction (int i, int j) {
	return (i==j);
}

vector<int> stacktoVec(stack<int> a){
	stack<int> b = a;
	vector<int> vec;
	while(!b.empty()){
		vec.push_back(b.top());
		b.pop();
	}
	return vec;
}

int removeTurn(char prev,char curr){
	int shouldRemove = 0;
	if(prev=='w'||prev=='W'){
		if(curr == 's'||curr=='S'){
			shouldRemove = 1;
		}
	}
	if(prev=='s'||prev=='S'){
		if(curr == 'W'||curr=='w'){
			shouldRemove = 1;
		}
	}
	if(prev=='a'||prev=='A'){
		if(curr == 'D'||curr=='d'){
			shouldRemove = 1;
		}
	}
	if(prev=='D'||prev=='d'){
		if(curr == 'a'||curr=='A'){
			shouldRemove = 1;
		}
	}
	return shouldRemove;
}
int collisionCheck(int **cells,int x,int y,char dir){
	int canGo = 0;
	if(dir == 'w' || dir == 'W'){
		if((cells[y][x]&2)==2){
			canGo = 1;
		}
	}
	if(dir == 's' || dir == 'S'){
		if((cells[y][x]&8)==8){
			canGo = 1;
		}

	}
	if(dir == 'a' || dir == 'A'){
		if((cells[y][x]&4)==4){
			canGo = 1;
		}
	}
	if(dir == 'd' || dir == 'D'){
		if((cells[y][x]&1)==1){
			canGo = 1;
		}
	}
	return canGo;
}
void playMaze(Maze m){
	stack<int> turns;
	stack<char> t;
	int x = 0;
	int y = 0;
	while(true){
		system("cls");
		cout << "X: "<<x<<"Y: "<<y<<endl;
		if(x==m.HEIGHT-1&&y==m.WIDTH-1){
			SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0|10);
			cout << "You have solved it! Good Job!\n";
			SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0|15);
			cout << "Press 'X' to EXIT"<<endl;
		}
		displayMaze(m.cells,m.WIDTH,m.HEIGHT,1,0);
		cout << "Enter W,S,A,D to move" << endl;
		cout << "Enter x to exit" << endl;
		char c;
		cin >> c;
		bool canMove = true;
		if(c=='x')
			return;
		switch(c){
			case 'w':
			case 'W':
				{
					if(y>0){
						if(collisionCheck(m.cells,x,y,c)==0){
							y = y-1;
						}else{
							canMove = false;
						}
					}else{
						canMove = false;
					}
					break;
				}
			case 's':
			case 'S':
				{
					if(y<m.HEIGHT-1){
						if(collisionCheck(m.cells,x,y,c)==0){
							y = y+1;
						}else{
							canMove = false;
						}
					}else{
						canMove = false;
					}
					break;
				}
			case 'a':
			case 'A':
				{
					if(x>0){
						if(collisionCheck(m.cells,x,y,c)==0){
							x = x-1;
						}else{
							canMove = false;
						}
					}else{
						canMove = false;
					}
					break;
				}
			case 'd':
			case 'D':
				{
					if(x<m.WIDTH-1){
						if(collisionCheck(m.cells,x,y,c)==0){
							x = x+1;
						}else{
							canMove = false;
						}
					}else{
						canMove = false;
					}
					break;
				}
			default:
				cout << "Enter a valid key!" << endl;
		}
		int v = m.WIDTH*y+x;
		if(t.empty() && turns.empty() && canMove){
			t.push(c);
			turns.push(v);
		}else{
			if(canMove){
				char chk = t.top();
				if(removeTurn(chk,c)==1){
					t.pop();
					turns.pop();
				}else{
					t.push(c);
					turns.push(v);
				}
			}
		}
		solution = stacktoVec(turns);

		//displayMaze(m.cells,m.WIDTH,m.HEIGHT,1,0);
	}
	//solution = stacktoVec(turns);
	//displayMaze(m.cells,m.WIDTH,m.HEIGHT,1,5,5,0);
}
void disp_message_1(){
	cout << "\t1.Print Maze.\n";
	cout << "\t2.Print Solved Maze.\n";
	cout << "\t3.Solve the Maze.\n";
	cout << "\t4.Exit/New Session\n";
}
void disp_message_2(){
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0|11);
	cout << "      ___           ___           ___           ___     "<<endl;
	cout << "     /\\  \\         /\\  \\         /\\__\\         /\\__\\    "<<endl;
	cout << "    |::\\  \\       /::\\  \\       /::|  |       /:/ _/_   "<<endl;
	cout << "    |:|:\\  \\     /:/\\:\\  \\     /:/:|  |      /:/ /\\__\\  "<<endl;
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0|12);
	cout << "  __|:|\\:\\  \\   /:/ /::\\  \\   /:/|:|  |__   /:/ /:/ _/_ "<<endl;
	cout << " /::::|_\\:\\__\\ /:/_/:/\\:\\__\\ /:/ |:| /\\__\\ /:/_/:/ /\\__\\"<<endl;
	cout << " \\:\\__\\  \\/__/ \\:\\/:/  \\/__/ \\/__|:|/:/  / \\:\\/:/ /:/  /"<<endl;
	cout << "  \\:\\  \\        \\::/__/          |:/:/  /   \\::/_/:/  / "<<endl;
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0|10);
	cout << "   \\:\\  \\        \\:\\  \\          |::/  /     \\:\\/:/  /  "<<endl;
	cout << "    \\:\\__\\        \\:\\__\\         |:/  /       \\::/  /   "<<endl;
	cout << "     \\/__/         \\/__/         |/__/         \\/__/ "<<endl;
	cout << endl<<endl;
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0|14);
	cout << "\tWelcome to my MAZE Generator/Solver.\n\n";
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0|15);
	cout << "\tEnter SIZE of the MAZE:\n";
	cout << "\tNote: SIZE must be > 2\n";
	cout << "\tPress CTRL+C to exit.\n";
}
int main(){
	/// use this only once in the pgm execution.
	srand(time(NULL));
	//      WxH
	char c;
	int option;
	int ex1 = 0;
	int game = true;
	while(game){
		int width;
		int height;
		disp_message_2();
		bool inp = true;
		while(inp){
			cin >> width ;
			height = width;
			if(width>2){
				inp=false; //break out of loop
			}else{
				cout << "Enter proper values!" << endl;
			}
		}
		Maze mg(height,width);
		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0|14);
		cout << "\t...Generating Maze...\n";
		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0|15);
		displayMaze(mg.cells,height,width,0,0);
		cout << endl;
		while(ex1<1){
			disp_message_1();
			cin >> option;
			switch(option){
				case 1:
					displayMaze(mg.cells,height,width,0,0);
					break;
				case 2:
					solution = solve2(mg.cells,0,0,height-1,width-1,height,width);
					Sleep(100);
					displayMaze(mg.cells,height,width,1,0);
					break;
				case 3:
					system("cls");
					displayMaze(mg.cells,height,width,0,0);
					solution.clear();
					playMaze(mg);
					break;
				case 4:
					ex1+=1;
			}
		}
		ex1 = 0;
		cout << "Press ANY key for a new session OR Press 'X' to exit.\n";
		cin >> c;
		switch(c){
			case 'X':
			case 'x':
				game = false;
				break;
			default:
				cout << "Continuing...\n\n";
		}
	}
}
