 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>
#include <limits>
#include <queue>

using namespace std;

typedef long long ll;

//Main
ll n, m, u, v, w, res;
long long int INF = std::numeric_limits<long long int>::max();
vector<ll> piDe0AN;
//             u,              v,  w
unordered_map<ll, vector<pair<ll, ll> > > adj;
vector<tuple<ll, ll, ll>> lAdj;
unordered_set<ll> s;
vector<ll> pi;
vector<ll> pred;
unordered_set<ll> aux;

void dijkstra(ll &v){

    pi.assign(n, INF);      //Vector de distancias de camino minimo por vertice
    pred.assign(n, -1);    //Predecesores
    s.insert(v);            //Conjunto de vertices visitados

    pi[v] = 0;
    pred[v] = v;
    w = v;  //Vertice que no esta en s y es el indice del minimo valor en pi

    for (pair<ll, ll> e: adj[v])    //Recorro los adyacentes a v    O(vecinos de v)
    {
        //Si es una arista multiple escribo en pi solo si tiene un peso menor que la anterior
        if ((pi[e.first] > e.second) && (e.first != v))
        {
            pi[e.first] = e.second;
            pred[e.first] = v;
        }
    }

    //&& (pi[w] < INF) Guarda por si el grafo sea disconexo CREO!
    while ((s != aux) && (pi[w] < INF)) //O(N)
    {
        ll piw = INF;

        //Busco el indice i de pi que minimice pi[i] y el indice no este en s
        for (ll i = 0; i < n; i++)  //O(N)
        {
            if ((s.find(i) == s.end()) && (pi[i] < piw))
            {
                piw = pi[i];    //Menor distancia de un nodo que aun no fue procesado a la raiz 
                w = i;          //Nodo de menor que aun no fue procesado de menor distancia a la raiz
            }
        }

        s.insert(w);    //O(1)  Meto al nodo al conjunto de procesados

        for (pair<ll, ll> e: adj[w])    //O(vecinosDe(w))
        {
            //Si no es un loop y la distancia del adyacante a w es mayor que la distancia si se viniera de w
            if ((e.first != w) && (pi[e.first] > pi[w] + e.second))
            {
                pi[e.first] = pi[w] + e.second;
                pred[e.first] = w;
            }
        }
    }
    
    s.clear();  //O(n)

    return;
}


int main(){

    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);

    vector<ll> resultados;

    while (cin >> n >> m) {

        lAdj.assign(m, {});
        res = 0;

        for (ll i = 0; i < n; i++)
        {
            aux.insert(i);
        }


        for (ll i = 0; i < m; i++)
        {
            cin >> u >> v >> w;
            adj[u].push_back(make_pair(v, w));
            adj[v].push_back(make_pair(u, w));
            lAdj[i] = make_tuple(u, v, w);
        }

        v = 0;
        dijkstra(v);

        piDe0AN = pi;

        pi.clear();
        pred.clear();

        v = (n - 1);
        dijkstra(v);

        for (ll i = 0; i < m; i++)  //O(m)
        {
            if ( ( (piDe0AN[get<0>(lAdj[i])] + get<2>(lAdj[i]) + pi[get<1>(lAdj[i])]) == pi[0] ) || ( (piDe0AN[get<1>(lAdj[i])] + get<2>(lAdj[i]) + pi[get<0>(lAdj[i])]) == pi[0] ) )
            {
                res = res + get<2>(lAdj[i]);
            }
        }

        pi.clear();
        pred.clear();

        res = res * 2;

        resultados.push_back(res);
    }

    for (ll i = 0; i < resultados.size(); i++)
    {
        cout << resultados[i] << "\n";
    }
    

    return 0;
}