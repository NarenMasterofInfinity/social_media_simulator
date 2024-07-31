#include <iostream>
#include <map>
#include <list>
#include <algorithm>
#include <limits.h>
using namespace std;

class Graph{
public:
	int nv;
	map<int, list< pair <int , int> >> Edges;
	Graph(){
		nv = 0;
	}
	void addEdge(int u, int v, int w){
		Edges[u-1].push_back({v-1,w});
	}
	void addVertex(){
		nv++;
	}
	void floydWarshall(){
		int distances[nv][nv];
		for(int i = 0; i < nv; i++){
			for(int j = 0;j < nv; j++){
				if(i == j){
					distances[i][j] = 0;
				}
				else{
					distances[i][j] = INT_MAX;
				}
			}
		}
		for(int i = 0; i < nv; i++){
			list< pair <int, int> > :: iterator j;
			for(j = Edges[i].begin(); j != Edges[i].end(); j++){
				pair <int, int> p = *j;
				int u = i, v = p.first, w = p.second;
				distances[u][v] = w;
			}
		}

		for(int k = 0; k < nv; k++){
			for(int u = 0; u < nv; u++){
				for(int v = 0; v < nv; v++){
					if(distances[u][k] != INT_MAX && distances[k][v] != INT_MAX){
						distances[u][v] = min(distances[u][k] + distances[k][v], distances[u][v]);
					}
				}
			}
		}

		for(int i = 0; i < nv;i++){
			for(int j = 0; j < nv;j++){
				cout << "Shortest distance from "<< i+1 << " to " << j+1 << " is "<< distances[i][j] << endl;
			}
		}
	}
};

int main(){
	Graph G;
	for(int i = 0; i  < 4; i++){
		G.addVertex();
	}
	G.addEdge(1,2,3);
	G.addEdge(1,3,4);
	G.addEdge(2,4,6);
	G.addEdge(4,1,3);
	G.addEdge(3,2,1);

	G.floydWarshall();


}