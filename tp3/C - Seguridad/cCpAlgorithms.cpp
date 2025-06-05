 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>
#include <limits>
#include <queue>

using namespace std;

typedef long long ll;

//Main
ll n, m, u, v, w;
vector<tuple<ll, ll, ll>> lAdj;
ll res;

//Dijkstra
ll INF = std::numeric_limits<ll>::max();
vector<ll> d;
vector<ll> p;
vector<vector<pair<ll, ll>>> adj;


void dijkstra(ll &s, vector<ll> & d, vector<ll> & p) {
    ll n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);

    d[s] = 0;

    using pii = pair<ll, ll>;
    
    priority_queue<pii, vector<pii>, greater<pii>> q;
    
    q.push({0, s});
    
    while (!q.empty()) {

        ll v = q.top().second;
        ll d_v = q.top().first;

        q.pop();

        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            ll to = edge.first;
            ll len = edge.second;

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

    cin >> n >> m;
    
    lAdj.assign(m, {});
    res = 0;

    adj.assign(n, {});

    for (ll i = 0; i < m; i++)
    {
        cin >> u >> v >> w;

        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));

        lAdj[i] = make_tuple(u, v, w);
    }

    v = 0;

    //Implementacion de Dikstra extraida de CP-Algorithms
    dijkstra(v, d, p);

    vector<ll> piDe0AN = d;
 
    d.clear();
    p.clear();

    v = (n - 1);
    dijkstra(v, d, p);

    for (ll i = 0; i < m; i++)  //O(m)
    {
        if ( ( (piDe0AN[get<0>(lAdj[i])] + get<2>(lAdj[i]) + d[get<1>(lAdj[i])]) == d[0] ) || ( (piDe0AN[get<1>(lAdj[i])] + get<2>(lAdj[i]) + d[get<0>(lAdj[i])]) == d[0] ))
        {
            res = res + get<2>(lAdj[i]);
        }
    }

    res = res * 2;
    
    cout << res << "\n";

    return 0;
}