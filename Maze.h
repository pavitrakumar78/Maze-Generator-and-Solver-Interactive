#include<stdio.h>
#include<iostream>
#include<windows.h>
#include<cstdlib>
#include<list>
#include<stack>
#include<vector>
#include <algorithm>
#include <time.h>
#include <set>
#include <cstdlib>
#include <stdlib.h>

#include "Graph.h"

using namespace std;

class Maze{
	public:
		Graph* m_g;
		int HEIGHT;
		int WIDTH;
		int noVertex;
		int *spanning_tree;
		int **cells;
	public:
		Maze(int w,int h);
		void init();
		void mazeDFS();
		void drawMaze();
		void n_check();
		int unvisited_nb(bool* visit,vector<int> adj_list);
};
