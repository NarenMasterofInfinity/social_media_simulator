#include "classes.hpp"
#include "user_methods.hpp"
#include <queue>
#include <stack>
#include <limits.h>
#include <list>
#include <vector>

using namespace std;

#ifndef GRAPH
#define GRAPH
void Graph::init_adj()
{
	cout << "Enter edges " << endl;
	char choice;
	int i = 1;
	do
	{
		cout << "Edge " << i << endl;
		int v, u;
		cout << "Enter vertices (space seperated): ";
		cin >> u >> v;
		u--;
		v--;
		adj[u][v] = 1;
		i++;
		cout << "Do you wish to continue? ";
		cin >> choice;
	} while (choice == 'y');
}
void Graph::bfs(User *u)
{
	int n = mui[u->getUsername()];
	bfsutil(n);
}
void Graph::bfsutil(int source)
{
	queue<int> q;
	queue<int> level;
	bool visited[nv];
	for (int i = 0; i < nv; i++)
	{
		visited[i] = false;
	}
	q.push(source);
	visited[source] = true;
	level.push(0);
	while (!q.empty())
	{
		int node = q.front();
		q.pop();
		int l = level.front();
		level.pop();
		string u = miu[node];
		if (u != miu[source])
		{
			cout << u << " at friend level " << l << endl;
		}
		for (int i = 0; i < nv; i++)
		{
			if (adj[node][i] && !visited[i])
			{
				q.push(i);
				level.push(l + 1);
				visited[i] = true;
			}
		}
	}
}



void Graph::addEdge(User *u, User *v)
{
	int ui = mui[u->getUsername()];
	int vi = mui[v->getUsername()];
	this->addEdgeUtil(ui, vi);
}

void Graph::addEdgeComment(Comment *u, Comment *v, Post *p)
{
	int ui = p->CommentToInteger[u];
	int vi = p->CommentToInteger[v];
	int w = v->time_of_creation;
	this->addEdgeUtilComment(ui, vi, w);
}

void Graph::addEdgeUtilComment(int u, int v, int w)
{
	adj.resize(nv);
	for (int i = 0; i < nv; i++)
	{
		adj[i].resize(nv);
	}
	adj[u][v] = w;
}

void Graph::addVertexComment()
{
	nv += 1;
	adj.resize(nv);
	for (int i = 0; i < nv; i++)
	{
		adj[i].resize(nv);
	}
}

void Graph::addEdgeUtil(int u, int v)
{
	adj.resize(nv);
	for (int i = 0; i < nv; i++)
	{
		adj[i].resize(nv);
	}
	adj[u][v] = 1;
}

void Graph::addVertex()
{
	this->nv += 1;
	adj.resize(nv);
	for (int i = 0; i < nv; i++)
	{
		adj[i].resize(nv);
	}
}

void Graph::topologicalSortUtil(int node, vector<bool> &visited, Post *p, vector<int> &topo)
{
	visited[node] = true;

	for (int i = 0; i < nv; i++)
	{
		int m = INT_MAX;
		int idx = 0;
		if (adj[node][i] != 0 and !visited[i])
		{
			m = min(adj[node][i], m);
			if (m == adj[node][i])
			{
				idx = i;
			}
			topologicalSortUtil(idx, visited, p, topo);
		}
	}
	topo.push_back(node);
}

vector<Comment *> Graph::topologicalSort(Post *p)
{
	vector<int> topo;
	vector<bool> visited(nv, false);
	vector<Comment *> result;
	for (int i = 0; i < nv; i++)
	{
		if (!visited[i])
		{
			topologicalSortUtil(i, visited, p, topo);
		}
	}

	for (int i = topo.size() - 1; i >= 0; i--)
	{
		result.push_back(p->IntegerToComment[topo[i]]);
	}
	return result;
}

void Graph::dfsComment(Post *p)
{
	cout << "Displaying all the comments " << endl;
	bool visited[nv];
	for (int i = 0; i < nv; i++)
	{
		visited[i] = false;
	}
	for (int i = 0; i < nv; i++)
	{
		if (!visited[i])
		{
			dfsutilComment(i, visited, p, 0);
		}
	}
}

void Graph::dfsutilComment(int node, bool visited[], Post *p, int level)
{
	visited[node] = true;
	Comment *u = p->IntegerToComment[node];
	u->DisplayComment(level, p);
	for (int i = 0; i < nv; i++)
	{
		int m = INT_MAX;
		int idx = 0;
		if (adj[node][i] != 0 and !visited[i])
		{
			m = min(adj[node][i], m);
			if (m == adj[node][i])
			{
				idx = i;
			}
			dfsutilComment(idx, visited, p, level + 1);
		}
	}
}

void Graph::dfs()
{
	cout << "Displaying all the users " << endl;
	bool visited[nv];
	for (int i = 0; i < nv; i++)
	{
		visited[i] = false;
	}
	for (int i = 0; i < nv; i++)
	{
		if (!visited[i])
		{
			dfsutil(i, visited);
		}
	}
}

void Graph::dfsutil(int source, bool visited[])
{
	stack<int> s;
	static int c = 0;
	s.push(source);
	visited[source] = true;

	while (!s.empty())
	{
		int node = s.top();
		s.pop();
		string u = miu[node];
		cout << "User " << ++c << " : " << u << endl;
		for (int i = 0; i < nv; i++)
		{
			if (adj[node][i] && !visited[i])
			{
				s.push(i);
				visited[i] = true;
			}
		}
	}
}

void Graph::topologicalSortUtilForPost(int node, vector<bool> &visited, vector<int> &topo){
	visited[node] = true;
	for (int i = 0; i < nv; i++)
	{
		int m = INT_MAX;
		int idx = 0;
		if (adj[node][i] != 0 and !visited[i])
		{
		  //cout << node << " "<<i<<endl;
			topologicalSortUtilForPost(i, visited, topo);
		}
	}
	
	topo.push_back(node);
	
}

vector<Post*> Graph::topologicalSortForPost(int idx){
	vector<int> topo;
	vector<bool> visited(nv, false);
	vector<Post*> result;
	for(int i = 0; i < nv;i++){
		if(!visited[i]){
			topologicalSortUtilForPost(i, visited,topo);
		}
	}
	for(int i = topo.size()-1; i >=0 ;i--){
		result.push_back(mip[idx][topo[i]]);
	}
	return result;
}

void Graph::addPostVertex(int idx, Post* p){
	mpi.resize(idx+1);
	mip.resize(idx+1);
	mpi[idx][p] = nv;
	mip[idx][nv] = p;
	this->nv += 1;
	adj.resize(nv);
	for (int i = 0; i < nv; i++)
	{
		adj[i].resize(nv);
	}
}
void Graph::addPostEdge(int idx, Post* p1, Post* p2){
	int ui = mpi[idx][p1];
	int vi = mpi[idx][p2];
	adj[ui][vi] = 1;	
}
#endif
