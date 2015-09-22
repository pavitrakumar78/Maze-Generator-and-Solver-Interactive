#include "Maze.h"

Maze::Maze(int w,int h){
	WIDTH = w;
	HEIGHT = h;
	m_g = new Graph(w*h);
	noVertex = HEIGHT*WIDTH;
	spanning_tree = new int[noVertex];
	cells = new int*[HEIGHT];

	init();
	mazeDFS();

	for(int i = 0; i < HEIGHT; i++){
		cells[i] = new int[WIDTH];
		for(int col = 0;col<WIDTH;col++){
			cells[i][col] = 0xF; /// 1111
		}
	}
	drawMaze();
}

int Maze::unvisited_nb(bool* visited,vector<int> adj_list){
	int s = adj_list.size();

	set<int> rand_set;
	while(rand_set.size()<s){
		int r = rand()%s;
		rand_set.insert(r);
		if(!visited[adj_list[r]]){
			return adj_list[r];
		}
	}
	return -9;
}

void Maze::n_check(){
	for(int i = 0;i<noVertex;i++){
		m_g->showAdjacents(i);
	}
}

void Maze::init(){
	for(int row = 0;row<HEIGHT;row++){
		for(int col = 0;col<WIDTH;col++){
			int v = row*WIDTH+col;
			if(row>0){
				int v_top = (row-1)*WIDTH+(col);
				m_g->addEdge(v,v_top);
				m_g->addEdge(v_top,v);
			}
			if(col>0){
				int v_left = row*WIDTH+(col-1);
				m_g->addEdge(v,v_left);
				m_g->addEdge(v_left,v);
			}
			if(row<HEIGHT-1){
				int v_bottom = (row+1)*WIDTH+(col);
				m_g->addEdge(v,v_bottom);
				m_g->addEdge(v_bottom,v);

			}
			if(col<WIDTH-1){
				int v_right = (row)*WIDTH+(col+1);
				m_g->addEdge(v,v_right);
				m_g->addEdge(v_right,v);
			}
		}
	}
	int v_temp = (0+1)*WIDTH+(0);
	m_g->addEdge(0,v_temp);
	m_g->addEdge(v_temp,0);
	v_temp = (0)*WIDTH+(0+1);
	m_g->addEdge(0,v_temp);
	m_g->addEdge(v_temp,0);
}

void Maze::mazeDFS(){
	int s_v = 0;
	stack<int> temp;
	int no_of_vertex = noVertex;
	bool visited[no_of_vertex];
	int visitCount = 1;
	int i;
	for(i = 0;i<no_of_vertex;i++){
		visited[i] = false;
	}
	visited[s_v] = true;
	spanning_tree[s_v] = -1;
	while(visitCount<no_of_vertex){
		vector<int> adj_list = m_g->showAdjacents(s_v);
		random_shuffle ( adj_list.begin(), adj_list.end() );
		int adj_count = m_g->no_of_adj[s_v];
		int next_cell = unvisited_nb(visited,adj_list);
		if(next_cell!=-9){
			int w = next_cell;
			visited[w] = true;
			spanning_tree[w] = s_v;
			temp.push(w);
			s_v = w;
			visitCount++;
		}else{
			if(!temp.empty()){
				s_v = temp.top();
				temp.pop();
			}
		}
	}
}

void Maze::drawMaze(){
	int v,r0,c0,v0;
	int RIGHT = 1;  /// 0001    1 = wall, 0 = path
	int UP = 2;     /// 0010
	int LEFT = 4;   /// 0100
	int DOWN = 8;   /// 1000
	for(int row = 0;row<HEIGHT;row++){
		for(int col = 0;col<WIDTH;col++){
			v = row*WIDTH+col;
			int w = spanning_tree[v]; // cell connected to 'v'
			if(w>=0){
				r0 = w/WIDTH;
				c0 = w%WIDTH;
			}
			v0 = r0*WIDTH+c0;
			if(col+1==c0){
				cells[row][col] &= ~RIGHT;
				cells[r0][c0] &= ~LEFT;
			}
			if(row+1==r0){
				cells[row][col] &= ~DOWN;
				cells[r0][c0] &= ~UP;
			}
			if(row-1==r0){
				cells[row][col] &= ~UP;
				cells[r0][c0] &= ~DOWN;
			}
			if(col-1==c0){
				cells[row][col] &= ~LEFT;
				cells[r0][c0] &= ~RIGHT;
			}
		}
	}

	cells[0][0] &= ~LEFT;
	cells[HEIGHT-1][WIDTH-1] &= ~RIGHT;

//	for(int i = 0; i < HEIGHT; i++){
//		for(int col = 0;col<WIDTH;col++){
			//cells[i][col] = 0xF; //-> 1111
			// cout << cells[i][col]<<" ";
//		}
//		cout << endl;
//	}
}
