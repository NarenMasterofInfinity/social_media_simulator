#include "classes.hpp"


#ifndef KRUSKAL
#define KRUSKAL

#define k 5

void makeset(int v, vector<int> &parent)
{
    parent.resize(v + 1);
    parent[v] = v;
}

int findset(int v, vector<int> &parent)
{

    if (parent[v] == v)
    {
        return v;
    }
    return findset(parent[v], parent);
}

void unionset(int v, int u, vector<int> &parent)
{
    int a = findset(v, parent);
    int b = findset(u, parent);
    if (a != b)
    {
        parent[b] = a;
    }
}

bool fn(Edge e1, Edge e2)
{
    return e1.weight <= e2.weight;
}



map<int, list<int>> clusters(UndirectedGraph G, vector<int> &parent)
{
    map<int, list<int>> m;

    for (int v : G.V)
    {
        int root = findset(v, parent);
        m[root].push_back(v);
    }
    return m;
}

pair<list<Edge>, map<int, list<int>>> kruskalUtil(UndirectedGraph G, vector<int> &parent)
{
    int vertices = G.nv;
    list<Edge> E = G.E;
    list<Edge> T;
    for (int v : G.V)
    {
        makeset(v, parent);
    }
    E.sort(fn);
    int num_edges = 0;
    map<int, list<int>> m;
    for (Edge e : E)
    {
        int u = e.u;
        int v = e.v;
        num_edges += 1;
        if (findset(u, parent) != findset(v, parent))
        {
            T.push_back(e);
            unionset(u, v, parent);
        }
        if (num_edges == vertices - k + 2 )
        {
            m = clusters(G, parent);
            return {T, m};
        }
    }
 
    m = clusters(G, parent);
    return {T, m};
}

pair<list<Edge>, map<int, list<int>>> kruskal(UndirectedGraph G){
    vector<int> parent;
    return kruskalUtil(G, parent);
}

#endif