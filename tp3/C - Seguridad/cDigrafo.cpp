
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>
#include <limits>

using namespace std;

typedef long long ll;

//Main
ll n, m, u, v, w;
long long int inf = std::numeric_limits<long long int>::max();

//             u,              v,  w
unordered_map<ll, vector<pair<ll, ll> > > adj1;
unordered_map<ll, vector<pair<ll, ll> > > adj2;
vector<tuple<ll, ll, ll>> lAdj;
unordered_set<ll> s;
unordered_set<ll> V;
vector<ll> pi;
vector<ll> pred;
ll cantCaminMin = 1;
ll res;

void dijktra2(ll &v){

    pi.assign(n, inf);      //Vector de distancias de camino minimo por vertice
    pred.assign(n, inf);    //Predecesores
    s.insert(v);            //Conjunto de vertices visitados

    pi[v] = 0;
    pred[v] = v;
    w = v;  //Vertice que no esta en s y es el indice del minimo valor en pi

    for (pair<ll, ll> e: adj2[v])    //Recorro los adyacentes a v    O(vecinos de v)
    {
        //Si es una arista multiple escribo en pi solo si tiene un peso menor que la anterior
        if ((pi[e.first] > e.second) && (e.first != v))
        {
            pi[e.first] = e.second;
            pred[e.first] = v;
        }
    }

    //&& (pi[w] < inf) Guarda por si el grafo sea disconexo CREO!
    while ((s.size() < n) && (pi[w] < inf)) //O(N)
    {
        ll piw = inf;

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

        for (pair<ll, ll> e: adj2[w])    //O(vecinosDe(w))
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

void dijktra1(ll &v){

    pi.assign(n, inf);      //Vector de distancias de camino minimo por vertice
    pred.assign(n, inf);    //Predecesores
    s.insert(v);            //Conjunto de vertices visitados

    pi[v] = 0;
    pred[v] = v;
    w = v;  //Vertice que no esta en s y es el indice del minimo valor en pi

    for (pair<ll, ll> e: adj1[v])    //Recorro los adyacentes a v    O(vecinos de v)
    {
        //Si es una arista multiple escribo en pi solo si tiene un peso menor que la anterior
        if ((pi[e.first] > e.second) && (e.first != v))
        {
            pi[e.first] = e.second;
            pred[e.first] = v;
        }
    }

    //&& (pi[w] < inf) Guarda por si el grafo sea disconexo CREO!
    while ((s.size() < n) && (pi[w] < inf)) //O(N)
    {
        ll piw = inf;

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

        for (pair<ll, ll> e: adj1[w])    //O(vecinosDe(w))
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

int main() {

    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    lAdj.assign(m, {});
    res = 0;

    for (ll i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        adj1[u].push_back(make_pair(v, w));
        adj2[v].push_back(make_pair(u, w));
        lAdj[i] = make_tuple(u, v, w);
        /*
        if (u < v)
        {
            lAdj[i] = make_tuple(u, v, w);
        }else if(v < u){
            lAdj[i] = make_tuple(v, u, w);
        }else{
            lAdj[i] = make_tuple(u, v, w);
        }
        */
    }

    v = 0;
    dijktra1(v);

    vector<ll> piDe0AN = pi;

    v = (n - 1);
    dijktra2(v);

    for (ll i = 0; i < m; i++)  //O(m)
    {
        if ( ( get<0>(lAdj[i]) != get<1>(lAdj[i]) ) && ( (piDe0AN[get<0>(lAdj[i])] + get<2>(lAdj[i]) + pi[get<1>(lAdj[i])]) == pi[0] ) )
        {
            res = res + get<2>(lAdj[i]);
        }
    }

    res = res * 2;
    
    cout << res << "\n";
    
}