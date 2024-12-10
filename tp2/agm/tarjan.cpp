
#include <bits/stdc++.h>

using namespace std;


//void IS_BRIDGE(int v,int to); // some function to process the found bridge
int n; // number of nodes
vector<vector<int>> adj; // adjacency list of graph

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    
    visited[v] = true;
    
    tin[v] = low[v] = timer++;
    
    bool parent_skipped = false;
    
    for (int to : adj[v]) {
    
    
        if (to == p && !parent_skipped) {
            parent_skipped = true;
            continue;
        }
    
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
    
            low[v] = min(low[v], low[to]);
    
            if (low[to] > tin[v])
                //IS_BRIDGE(v, to);
                cout << (v + 1) << (to + 1) << "\n";
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
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }

    find_bridges();
    
/*
4 5
1 2
1 3
2 3
2 4
3 4
*/
    return 0;
}