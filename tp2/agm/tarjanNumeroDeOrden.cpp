
#include <bits/stdc++.h>

using namespace std;


//void IS_BRIDGE(int v,int to); // some function to process the found bridge
int n; // number of nodes
vector<vector<pair<int, int> > > adj; // adjacency list of graph

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {

    visited[v] = true;

    tin[v] = low[v] = timer++;
    
    bool parent_skipped = false;

    for (pair<int, int> to : adj[v]) {
        int aux = to.first;
        
        if ((aux == p) && (!parent_skipped)) {
            parent_skipped = true;
            continue;
        }

        if (visited[aux]) {
            low[v] = min(low[v], tin[aux]);
        } else {
            dfs(aux, v);

            low[v] = min(low[v], low[aux]);

            if (low[aux] > tin[v])
                //IS_BRIDGE(v, aux);
                cout << (v + 1) << " " << (aux + 1) << " Orden " << to.second << "\n";
                //Conseguir E por referencia y poner at least one
                //std::get<2>(E[k + aux.second()]) = 1;  //AT LEAST ONE
        }
    }
}

void find_bridges() {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
    }
}

int main(){

    int m, u, v;

    cin >> n >> m;
    
    //vector<int> aux;
    adj.assign(n, {});

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        
        pair<int, int> aux = make_pair(v - 1, i);
        adj[u - 1].push_back(aux);

        aux = make_pair(u - 1, i);
        adj[v - 1].push_back(aux);
    }

    find_bridges();

    return 0;
}