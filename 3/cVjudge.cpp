 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>
#include <limits>
#include <queue>

using namespace std;

typedef long long ll;

//Main
int n, m, u, v, w;

vector<tuple<ll, ll, ll>> lAdj;
ll res;

vector<int> d;
vector<int> p;

const int INF = 1000000000;
vector<vector<pair<int, int>>> adj;
vector<vector<pair<int, int>>> adj1;

void dijkstra1(int s, vector<int> & d, vector<int> & p) {
    int n = adj1.size();
    d.assign(n, INF);
    p.assign(n, -1);

    d[s] = 0;

    using pii = pair<int, int>;
    
    priority_queue<pii, vector<pii>, greater<pii>> q;
    
    q.push({0, s});
    
    while (!q.empty()) {

        int v = q.top().second;
        int d_v = q.top().first;

        q.pop();

        if (d_v != d[v])
            continue;

        for (auto edge : adj1[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }
}

void dijkstra(int s, vector<int> & d, vector<int> & p) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);

    d[s] = 0;

    using pii = pair<int, int>;
    
    priority_queue<pii, vector<pii>, greater<pii>> q;
    
    q.push({0, s});
    
    while (!q.empty()) {

        int v = q.top().second;
        int d_v = q.top().first;

        q.pop();

        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }
}


int main(){

    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);

    vector<ll> resultados;

    while (cin >> n >> m) {
        
        lAdj.assign(m, {});
        res = 0;

        adj.assign(n, {});
        adj1.assign(n, {});

        for (ll i = 0; i < m; i++)
        {
            cin >> u >> v >> w;
            adj[u].push_back(make_pair(v, w));
            adj1[v].push_back(make_pair(u, w));

            if (u < v)
            {
                lAdj[i] = make_tuple(u, v, w);
            }else if(v < u){
                lAdj[i] = make_tuple(v, u, w);
            }else{
                lAdj[i] = make_tuple(u, v, w);
            }
        }

        int v = 0;
        dijkstra(v, d, p);

        vector<int> piDe0AN = d;

        d.clear();
        p.clear();

        v = (n - 1);
        dijkstra(v, d, p);

        for (ll i = 0; i < m; i++)  //O(m)
        {
            if ( ( (piDe0AN[get<0>(lAdj[i])] + get<2>(lAdj[i]) + d[get<1>(lAdj[i])]) == d[0] ) || ( (piDe0AN[get<1>(lAdj[i])] + get<2>(lAdj[i]) + d[get<0>(lAdj[i])]) == d[0] ) )
            {
                res = res + get<2>(lAdj[i]);
            }
        }

        res = res * 2;

        resultados.push_back(res);
    }

    for (ll i = 0; i < resultados.size(); i++)
    {
        cout << resultados[i] << "\n";
    }
    

    return 0;
}