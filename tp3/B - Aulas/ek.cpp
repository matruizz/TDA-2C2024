 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>
#include <limits>

using namespace std;

typedef long long ll;


//Main
ll n, m, aux1, aux2, sumAlumnos, sumCapacidades, res;
vector<ll> a, b;
vector<pair<ll, ll>> validos;
ll INFINITO = std::numeric_limits<ll>::max();

//EK
vector<vector<ll>> capacity;
vector<vector<ll>> adj;
vector<vector<ll>> flujo;


ll minimo(ll a, ll b){
    if (a < b)
    {
        return a;
    }else{
        return b;
    }
}


ll bfs(ll s, ll t, vector<ll>& parent, vector<vector<ll>> &adj, vector<vector<ll>> &capacity) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<ll, ll>> q;
    q.push({s, INFINITO});

    while (!q.empty()) {
        ll cur = q.front().first;
        ll flow = q.front().second;
        q.pop();

        for (ll next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                ll new_flow = minimo(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

ll maxflow(ll s, ll t, vector<vector<ll>> &adj, vector<vector<ll>> &capacity) {
    ll flow = 0;
    vector<ll> parent((2*n) + 2);
    ll new_flow;

    while (new_flow = bfs(s, t, parent, adj, capacity)) {
        flow += new_flow;
        ll cur = t;
        while (cur != s) {
            ll prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            //flujo[prev][cur] += 1;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main(){

    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    adj.assign((2*n) + 2, {});
    capacity.assign((2*n) + 2, vector<ll>((2*n) + 2, 0));   //Seteo todas las capacidades a 0
    //flujo

    a.assign(n, 0);
    b.assign(n, 0);
    validos.assign(m, make_pair(0, 0));
    sumAlumnos = 0;
    sumCapacidades = 0;

    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
        sumAlumnos += a[i];
    }

    for (ll i = 0; i < n; i++)
    {
        cin >> b[i];
        sumCapacidades += b[i];
    }    

    for (ll i = 0; i < m; i++)
    {
        cin >> aux1 >> aux2;
        validos[i] = make_pair(aux1, aux2);
    }

    if (sumAlumnos != sumCapacidades)
    {
        cout << "NO" << "\n";
        return 0;
    }

    //Matriz de adyacencia y matriz de capacidades
    for (ll i = 0; i < n; i++)
    {
        adj[2 * n].push_back(i);     //(S -> ai)
        adj[i].push_back(2 * n);     //(ai -> S)

        capacity[2 * n][i] = a[i];
        //capacity[i][2 * n] = a[i];
    }

    for (ll i = 0; i < n; i++)
    {
        adj[(2 * n) + 1].push_back(n + i);   //(T -> bi)
        adj[n + i].push_back((2 * n) + 1);   //(bi -> T)

        //capacity[(2 * n) + 1][n + i] = b[i];
        capacity[n + i][(2 * n) + 1] = b[i];
    }

    for (ll i = 0; i < n; i++)
    {
        adj[i].push_back(n + i);            //(ai -> bi)
        adj[n + i].push_back(i);            //(bi -> ai)
        capacity[i][i + n] = INFINITO;      //c(bi -> ai) = infinito
        //capacity[i + n][i] = INFINITO;
    }
    

    for (ll i = 0; i < m; i++)
    {
        adj[validos[i].first - 1].push_back(validos[i].second - 1 + n);     //(ai -> bj)
        adj[validos[i].second - 1].push_back(validos[i].first - 1 + n);     //(aj -> bi)

        adj[validos[i].first - 1 + n].push_back(validos[i].second - 1);     //(ai <- bj)
        adj[validos[i].second - 1 + n].push_back(validos[i].first - 1);     //(aj <- ai)

        capacity[validos[i].first - 1][validos[i].second - 1 + n] = INFINITO;
        capacity[validos[i].second - 1][validos[i].first - 1 + n] = INFINITO;
    }


    ll s = (2*n);
    ll t = (2*n) + 1;

    //Implementación de Edmons y Karp sacada de: https://cp-algorithms.com/graph/edmonds_karp.html
    res = maxflow(s, t, adj, capacity);

    if (res != sumAlumnos)
    {
        cout << "NO" << "\n";
    }else{
        //Imprimir matriz de flujos de ai a bi
        cout << "YES" << "\n";
        for (ll i = 0; i < n; i++)
        {
            for (ll j = n; j < (n + n); j++)
            {
                if (j == (n + n - 1))
                {
                    cout << capacity[j][i] << "\n";
                }else{
                    cout << capacity[j][i] << " ";
                }
            }
        }
        
    }
    

    return 0;
}