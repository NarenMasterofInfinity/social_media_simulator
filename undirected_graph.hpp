#include "classes.hpp"
#include <algorithm>
#include <queue>

#ifndef UGRAPH
#define UGRAPH
#define THRESHOLD 2

void UndirectedGraph::addEdges()
{

    vector<Edge> Er;

    for (int i = 1; i <= nv; i++)
    {
        for (int j = 1; j <= nv; j++)
        {

            int m1 = i < j ? i : j;
            int m2 = m1 == i ? j : i;

            if (i != j)
            {
                bool stop = false;
                for (int l = 0; l < Er.size(); l++)
                {
                    Edge e = Er[l];
                    if ((e.u == i || e.v == j) && (e.u == j || e.v == i))
                    {
                        stop = true;
                    }
                }
                if (!stop)
                {
                    string uname = miuUG[i];
                    string vname = miuUG[j];
                    Edge temp(i, j, 1 / (count_convs(uname, vname) + epsilon));
                    Er.push_back(temp);
                }
            }
        }
    }

    E.clear();
    for (int i = 0; i < Er.size(); i++)
    {
        E.push_back(Er[i]);
    }
}

bool mindouble(double a, double b){
    return (a < b) ? a : b;
}
void UndirectedGraph::floydWarshall(){
        distances.resize(nv);
        for(int i = 0; i < nv; i++){
            distances[i].resize(nv);
        }
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
        
        list< Edge > :: iterator j;
        for(j = E.begin(); j != E.end(); j++){
            Edge e = *j;
            int u = e.u, v = e.v, w = e.weight;
            if (w != 1){
                distances[u][v] = w;
                distances[v][u] = w;
            }
              //  cout << "Distances "<<u << " "<< v << " " << distances[{u,v}] << endl; 
               // cout << "At the fifth: " << micUGComm[5]->getCommunityDescription() << endl;          
        }
       // cout << "At 0: " << micUGComm[0]->getCommunityName() << endl;
        for(int m = 0; m < nv; m++){
            for(int u = 0; u < nv; u++){
                for(int v = 0; v < nv; v++){
                    if(distances[u][m] != INT_MAX && distances[m][v] != INT_MAX){
                        // cout << "For " << m << endl;
                        // cout << "Distance from " << u << " to " <<v <<" " << distances[u][v] << endl;
                        // cout << "Distance from " << u << " to " << m <<" " << distances[u][m] << endl;
                        // cout << "Distance from " << m << " to " << v << " " << distances[m][v] << endl;
                        distances[u][v] = min(distances[u][m] + distances[m][v], distances[u][v]);
                        // cout << "Distance from " << u << " to " <<v <<" " << distances[u][v] << endl;
                        // cout << "Distance from " << u << " to " << m <<" " << distances[u][m] << endl;
                        // cout << "Distance from " << m << " to " << v << " " << distances[m][v] << endl;

                    }
                }
            }
        } 
       
    

}

void UndirectedGraph::updateWeight(string uname, string vname)
{
    int u = muiUG[uname];
    int v = muiUG[vname];
    for (Edge &e : E)
    {
        if (e.u == u && e.v == v)
        {
            e.weight = 1 / (count_convs(uname, vname) + epsilon);
            break;
        }
    }
}

string UndirectedGraph::preprocess(string s)
{
    string res = "";
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        if (s[i] == ' ')
        {
            continue;
        }
        if (s[i] == '.' || s[i] == ',' || s[i] == '!')
        {
            continue;
        }
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            res += s[i] - 'A' + 'a';
        }
        else
        {
            res += s[i];
        }
    }
    return res;
}

int UndirectedGraph::edit_distance(string s1, string s2)
{
    int m = s1.length();
    int n = s2.length();
    int dp[m + 1][n + 1];
    for (int i = 0; i <= n; i++)
    {
        dp[0][i] = i;
    }
    for (int i = 0; i <= m; i++)
    {
        dp[i][0] = i;
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                vector<int> v = {dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]};
                int m = INT_MAX;
                for (int vi : v)
                {
                    m = min(vi, m);
                }
                dp[i][j] = m + 1;
            }
        }
    }
    return dp[m][n];
}

int UndirectedGraph::lcs(string s1, string s2){
    int m = s1.length();
    int n = s2.length();
    int dp[m+1][n+1];
    for(int i = 0; i < m+1; i++){
        dp[i][0] = 0;
    }
    for(int i = 0; i < n+1; i++){
        dp[0][i] = 0;
    }

    for(int i= 1; i < m+1;i++){
        for(int j = 1; j < n+1;j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else{
                dp[i][j] = max(dp[i-1][j] , dp[i][j-1]);
            }
        }
    }
    return dp[m][n];
}

void UndirectedGraph::convWeights()
{
    vector<Edge> Er;
    vector<vector<int>> un; // i'm crying
    set<pair<int, int>> s;
    for (int i = 0; i < nv; i++)
    {
        for (int j = 0; j < nv; j++)
        {
            pair<int, int> p;
            int m1 = i < j ? i : j;
            int m2 = m1 == i ? j : i;

            if (i != j)
            {
                bool stop = false;
                for (int l = 0; l < Er.size(); l++)
                {
                    Edge e = Er[l];
                    if ((e.u == i || e.v == j) && (e.u == j || e.v == i))
                    {
                        stop = true;
                    }
                }
                if (!stop)
                {
                    Conversation *conv1ug = micUGComm[i];
                    Conversation *conv2ug = micUGComm[j];
                    string conv1desp = conv1ug->getCommunityDescription();
                    string conv2desp = conv2ug->getCommunityDescription();
                   // double w = ((double)edit_distance(conv1desp, conv2desp)) / max(conv1desp.length(), conv2desp.length());
                    double m = max(conv1desp.length(), conv2desp.length());
                    double l = min(edit_distance(conv1desp, conv2desp), lcs(conv1desp, conv2desp));
                    
                    double tempw = l / m;
                    
                    double w = 1/(tempw + epsilon);
                 
                    w *= 100;
                    
                    Er.push_back(Edge(i, j, w));
                }
                // Er.push_back(temp); //no clue how this solved it
            }
        }
    }

    E.clear();
    for (int i = 0; i < Er.size(); i++)
    {
        E.push_back(Er[i]);
    }
    floydWarshall();
}

int extractMin(vector<double> distances, vector<bool> done)
{
    double m = INT_MAX;
    int idx = -1;
    for (int i = 0; i < distances.size(); i++)
    {
        if (distances[i] < m and !done[i])
        {
            m = distances[i];
            idx = i;
        }
    }
    return idx;
}

bool alldone(vector<bool> done)
{
    bool res = true;
    for (int i = 0; i < done.size(); i++)
    {
        res &= done[i];
    }
    return res;
}

void UndirectedGraph::relax_vertices(int vertex, vector<double> &distances, vector<bool> done)
{
    // find all the adjacent vertexes
    // vector<bool> visited(nv, false);
    // visited[vertex] = true;
    for (int i = 0; i < nv; i++)
    {
        double w ;

        if (i != vertex)
        {
            
            for (list<Edge>::iterator edge = E.begin(); edge != E.end(); edge++)
            {
                Edge e = *edge;
                if ((e.u == vertex && e.v == i) || (e.u == i && e.v == vertex))
                {
                    w = e.weight;
            
                }
            }
            
            if (distances[i] > distances[vertex] + w)
            {
                distances[i] = distances[vertex] + w;
                
                
            }
        }
    }
    
}

// pair < index, distance >
vector<double> UndirectedGraph::dijkstrautil(int source)
{

    vector<double> distances(nv, INT_MAX);
    vector<bool> done(nv, false);
    distances[source] = 0;

    while (!alldone(done))
    {
        int vertex = extractMin(distances, done);
        done[vertex] = true;

        relax_vertices(vertex, distances, done);
     
    }
    return distances;
}

list<pair<Conversation *, double>> UndirectedGraph::dijkstra(Conversation *source)
{

    int s = mciUGComm[source];

    vector<double> distances = dijkstrautil(s);
    list<pair<Conversation *, double>> thepairing;
    for (int i = 0; i < nv; i++)
    {
        pair<Conversation *, double> p = {micUGComm[i], distances[i]};
        // cout << distances[i] << " " << micUGComm[i]->getCommunityName() << endl;
        thepairing.push_back(p);
    }
    return thepairing;
}

bool comparefnpair(pair<Conversation *, double> one, pair<Conversation *, double> two)
{
    return one.second < two.second;
}

vector<Conversation *> UndirectedGraph::suggestConvs(Conversation *c)
{

    this->addVertex(c);
    this->convWeights();
    vector<Conversation *> suggestions;

    list<pair<Conversation *, double>> allsuggestions = dijkstra(c);
    allsuggestions.sort(comparefnpair);

    int times = 0;
    for (list<pair<Conversation *, double>>::iterator i = allsuggestions.begin(); times < THRESHOLD + 1 && i != allsuggestions.end(); i++, times++)
    {
        if (times != 0)
        {
            //cout << i->first->getCommunityDescription() << " " << i->second<<endl;
            suggestions.push_back(i->first);
        }
    }
    return suggestions;
}

bool sortfnforsuggestions(pair<double, Conversation*> p1, pair<double, Conversation*> p2){
    return p1.first < p2.first;
}

vector<Conversation*> UndirectedGraph::suggestConvsFloyd(Conversation* c){
   // this->addVertex(c);
    //extra vertex need not be added, can keep the graph clean.
    // this->convWeights(); //this part is optimisefloydw
    //Don't ever forget to resize vectors

    distances.resize(nv+1);
    for(int i= 0; i < nv+1; i++){
        distances[i].resize(nv+1);
    }
    vector<double> alldistances;
    //updates distances
    alldistances.resize(nv);
    for(int i = 0 ; i < nv; i++){
        alldistances[i] = INT_MAX;
    }
    for(int i = 0; i < nv; i++){
        Conversation *conv1ug = micUGComm[i];
        string conv1desp = conv1ug->getCommunityDescription();
        string conv2desp = c->getCommunityDescription();
        // double w = ((double)edit_distance(conv1desp, conv2desp)) / max(conv1desp.length(), conv2desp.length());
        double m = max(conv1desp.length(), conv2desp.length());
        double l = min(edit_distance(conv1desp, conv2desp), lcs(conv1desp, conv2desp));
                    
        double tempw = l / m;
                    
        double w = 1/(tempw + epsilon);
                 
        w *= 100;
        distances[nv][i] = w;
        distances[i][nv] = w;
    }

    for(int intermediate = 0; intermediate < nv; intermediate++){
        for(int endvertex = 0; endvertex < nv; endvertex++){
            distances[nv][endvertex] = min(distances[nv][intermediate] + distances[intermediate][endvertex], distances[nv][endvertex]);
        }
    }

    for(int i = 0 ; i < nv; i++){
        alldistances[i] = distances[nv][i];
    }

    // for(int i = 0 ; i < nv; i++){
    //     cout << i+1 << " " << alldistances[i] << endl;
    // }

    list<pair < double, Conversation *> > presuggestions;

    for(int i = 0; i < nv; i++){
       // cout << micUGComm[i]->getCommunityName() << " " << alldistances[i] <<endl;
        presuggestions.push_back({alldistances[i],micUGComm[i]});
    }

    //list<pair<Conversation *, double>> allsuggestions = dijkstra(c); //optimised
    presuggestions.sort(sortfnforsuggestions);

    vector<Conversation*> suggestions;

    int times = 0;
    for (list<pair<double, Conversation*>>::iterator i = presuggestions.begin(); times < THRESHOLD  && i != presuggestions.end(); i++, times++)
    {
       
            suggestions.push_back(i->second);
        
    }
    return suggestions;
}
bool bellsortfn(pair<int, double> p1, pair<int, double> p2){
    return p1.second < p2.second;
}
vector<Conversation*> UndirectedGraph::suggestConvsBellmanFord(Conversation* source){

    this->addVertex(source);
    this->convWeights();

    vector<double> allsuggestions = bellmanFord(source);

    list < pair< int, double > > suggwithidx;
    for(int i = 0; i < nv;i++){
        if(allsuggestions[i] != 0){
            cout << i << " " << allsuggestions[i] << endl;
        suggwithidx.push_back({i, allsuggestions[i]});
    }

    }
    suggwithidx.sort(bellsortfn);
    vector<Conversation*> suggestions;
    int times = 0;
    for(auto i : suggwithidx){
        if(times >= THRESHOLD){
            break;
        }
        suggestions.push_back(micUGComm[i.first]);
        times++;
    }
    return suggestions;
}
vector<double> UndirectedGraph::bellmanFord(Conversation* source){
    vector <double> shortestpaths;
    shortestpaths.resize(nv);
    for(int i = 0; i < nv; i++){
        shortestpaths[i] = INT_MAX;
    }
    int src = mciUGComm[source];
    shortestpaths[src] = 0;
    bellmanFordutil(shortestpaths, src);
    return shortestpaths;
}

void UndirectedGraph::bellmanFordutil(vector<double>& shortestpaths,int source){
    list<double> weights;
    for(list<Edge>::iterator i = E.begin(); i != E.end(); i++){
        if(i->weight != INT_MAX ){
        weights.push_back(i->weight);
    }
    }

    weights.sort();
    vector<double> lazyv;

    for(auto i : weights){
        lazyv.push_back(i);
    }
    int midx = nv/2;

    double middle = lazyv[midx];
    cout << "middle "<<middle<<endl;
    list<Edge> updated_edges;
    for(list<Edge>::iterator i = E.begin(); i != E.end(); i++){
        if(i->u > i->v){
            if(i->weight <= middle){
                Edge e{i->u, i->v, i->weight};
                updated_edges.push_back(e);
            }
            else{
                Edge e{i->u, i->v,i->weight};
                updated_edges.push_back(e);
            }
        }
    }
    
    shortestpaths[source] = 0;
     
    for(int y = 0; y < nv-1; y++){
        for(list<Edge>::iterator i = updated_edges.begin(); i != updated_edges.end(); i++){
            int u = i->u, v = i->v;
            double w = i->weight;
            //cout << v << " " << shortestpaths[u] +w << " "  << w <<endl;
            shortestpaths[v]  = min(shortestpaths[u] + w, shortestpaths[v]);
        }
    }

}
#endif
