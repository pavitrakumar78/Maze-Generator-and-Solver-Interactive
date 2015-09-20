#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <list>
#include <stack>
#include <vector>
#include <algorithm>
#include <time.h>
#include <set>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

class Graph{
	public:
		int V;
		vector<vector<int> > adj;
		int* no_of_adj;
	public:
		Graph(int V);
		void addEdge(int v, int w);
		vector<int> showAdjacents(int V);
};
