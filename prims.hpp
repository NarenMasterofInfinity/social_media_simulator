#include "classes.hpp"

#ifndef PRIMS
#define PRIMS

#define depth 2

list<Edge> primsUtil(UndirectedGraph G, int selected_vertex)
{
    
    int num_vertices = G.nv;
    bool visited[num_vertices];
    int shortest_dists[num_vertices];

    list<Edge> T;

    list<Edge> Es = G.E;

    for (int i = 0; i < num_vertices; i++)
    {
        visited[i] = false;
    }

    visited[selected_vertex] = true;


    while (T.size() < depth)
    {
        double m = INT_MAX;
        Edge min_edge;
        for (Edge e : Es)
        {
            if (e.u == selected_vertex || e.v == selected_vertex)
            {
                int other  = (selected_vertex == e.u) ? e.v : e.u;
                
                if (m > e.weight && !visited[other])
                {
                    min_edge = e;
                    m = e.weight;
                }
            }
        }
        selected_vertex = (selected_vertex == min_edge.u) ? min_edge.v : min_edge.u;
        visited[min_edge.u] = true;
        visited[min_edge.v] = true;
        T.push_back(min_edge);
    }

    return T;
}

list<int> prims(UndirectedGraph G, Conversation *c){
    list<Edge> T = primsUtil(G, mciUGComm[c]);
    set<int> s;
    list<int> l;
    for(Edge e : T){
        s.insert(e.u);
        s.insert(e.v);
    }
    for(int si : s){
        l.push_back(si);
    }
    return l;
}

#endif