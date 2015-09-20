#include "Graph.h"

Graph::Graph(int v){
	V = v;
	no_of_adj = new int[V];
	adj.resize(V, vector<int>(V,0));
	for ( int i = 0 ; i < V ; i++ ){
		adj[i].resize(V);
		no_of_adj[i] = 0;
	}
}

void Graph::addEdge(int v, int w){

	vector<int> temp = adj[v];
	int ix = no_of_adj[v];
	for(int i = 0;i<ix;i++){
		if(w==temp[i])
			return;
	}
	no_of_adj[v]++;
	adj[v][no_of_adj[v]-1] = w;

}

vector<int> Graph::showAdjacents(int V){
	vector<int> temp = adj[V];
	temp.erase(temp.begin()+no_of_adj[V],temp.begin()+temp.size());
	return temp;
}
