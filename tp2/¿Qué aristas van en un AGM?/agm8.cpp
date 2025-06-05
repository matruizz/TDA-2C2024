
//TIME LIMIT EXCEDED IN TEST 16!!!!!!!!!!!!!!!!!!!!!!!
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

//void IS_BRIDGE(int v,int to); // some function to process the found bridge
ll cantVerticesGPrima; // number of nodes

//primer elemento del par el el nodo adyacente, el segundo elemento es el orden en que fue agregado 
vector<vector<pair<ll, ll> > > adj; // adjacency list of graph

vector<bool> visited;
vector<ll> tin, low;
ll timer;

ll aristas;

bool compDePosicion(tuple<ll, ll, ll, ll> &a, tuple<ll, ll, ll, ll> &b){

    if (std::get<3>(a) <= std::get<3>(b))
    {
        return true;
    }else{
        return false;
    }
}


class DisjointSet {

    vector<ll> rank, parent;
public:
    DisjointSet(ll &n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for(ll i = 0; i < n + 1; i++){
            parent[i] = i;
        }
    }

    //Find implementado con path compression
    ll findSet(ll &node){

        // En caso que nodo sea el representante
        if (node == parent[node]) return node;

        // Hago path compression
        //En c++ return de una asignacion devuelve una referencia a lo que esta a la izquiereda del =
        //Es decir esto retorna una referencia al padre del nodo actual
        return parent[node] = findSet(parent[node]);
    }

    void unionByRank(ll &u, ll &v) {
        ll uRepresentative = findSet(u);
        ll vRepresentative = findSet(v);

        // Si tienen el mismo representante, entonces pertenece al
        // mismo conjunto
        if (uRepresentative == vRepresentative) return;

        // Actualizamos el representante segun el caso del rank
        if (rank[uRepresentative] < rank[vRepresentative]) {
            parent[uRepresentative] = vRepresentative;
        } else if(rank[uRepresentative] > rank[vRepresentative]) {
            parent[vRepresentative] = uRepresentative;
        } else {
            parent[vRepresentative] = uRepresentative;
            rank[uRepresentative]++;
        }
    }
};



void dfs(ll &v, ll &p, vector<tuple<ll, ll, ll, ll>> &E, ll &k, ll &aristas) {

    visited[v] = true;

    tin[v] = low[v] = timer++;
    
    bool parent_skipped = false;

    for (pair<ll, ll> to : adj[v]) {

        ll u = to.first;

        if ((u == p) && (!parent_skipped)) {
            parent_skipped = true;
            continue;
        }

        if (visited[u]) {
            low[v] = min(low[v], tin[u]);
        } else {
            dfs(u, v, E, k, aristas);

            low[v] = min(low[v], low[u]);

            if (low[u] > tin[v]){
                //IS_BRIDGE(v, aux);
                
                /*
                cout << (v + 1) << " " << (u + 1) << " Orden " << to.second << "\n";
                */
                
                //Conseguir E por referencia y poner at least one
                std::get<0>(E[k + to.second]) = -1;  //ANY

            }
        }
    }
}

void find_bridges(vector<tuple<ll, ll, ll, ll> > &E, ll &k, ll &aristas, ll &n) {

    timer = 0;

    visited.assign(n, false);

    tin.assign(n, -1);

    low.assign(n, -1);

    ll cantComConex = 0;
    cantVerticesGPrima = 0;

    for (ll i = 0; i < n; ++i) {

        if ((!visited[i]) && (adj[i].size() > 0)){
            ll uno = -1;
            dfs(i, uno, E, k, aristas);
            cantComConex++;
        }

        if (adj[i].size() > 0)
        {
            cantVerticesGPrima++;
        }
    }

    aristas =  aristas + (cantVerticesGPrima - cantComConex);
}



void crearGPrima(vector<tuple<ll, ll, ll, ll> > &E, ll &k, DisjointSet &disSet, ll &aristas, ll &n){

    ll cantMismoW = 0;

    adj.assign(n, {});

    ll peso = std::get<0>(E[k]);

    while ((k + cantMismoW < E.size()))
    {   
        //Si el peso de la arista actual es igual al peso que se repite
        if ((std::get<0>(E[k + cantMismoW]) == peso))
        {
            ll u = std::get<1>(E[k + cantMismoW]);
            ll v = std::get<2>(E[k + cantMismoW]);

            //G' tiene como nodos a los representantes de los nodos del grafo original
            ll repreU = disSet.findSet(u);
            ll repreV = disSet.findSet(v);

            //Si tienen el mismo representante
            if (repreU == repreV)
            {
                std::get<0>(E[k + cantMismoW]) = -3;  //NONE

            }else{//Si tienen representantes distintos, meto sus representantes como nodos en el G'

                //cantVerticesGPrima++;

                adj[repreU - 1].push_back(make_pair(repreV - 1, cantMismoW));
                adj[repreV - 1].push_back(make_pair(repreU - 1, cantMismoW));
            }

            cantMismoW++;
        }else{

            break;
        }
    }

    find_bridges(E, k, aristas, n);

    for (ll j = 0; j < cantMismoW; j++)
    {
        //Si no son ni ANY ni NONE tienen que ser AT LEAST ONE
        if ((std::get<0>(E[k + j]) != -1) && (std::get<0>(E[k + j]) != -3))
        {
            std::get<0>(E[k + j])= -2;
        }

        //Si son at least one y unen componentes conexas distintas entonces union by rank
        if (std::get<0>(E[k + j]) == -2)
        {
            ll u = std::get<1>(E[k + j]);
            ll v = std::get<2>(E[k + j]);

            ll repreU = disSet.findSet(u);
            ll repreV = disSet.findSet(v);

            if (repreU != repreV)
            {
                disSet.unionByRank(u, v);
            }
        }

        //Si son any union by rank
        if (std::get<0>(E[k + j]) == -1)
        {
            ll u = std::get<1>(E[k + j]);
            ll v = std::get<2>(E[k + j]);
            disSet.unionByRank(u, v);
        }        
    }

    k = k + cantMismoW - 1;
}


void kruskal(vector<tuple<ll, ll, ll, ll>> &E, ll &n){

    sort(E.begin(), E.end());

    DisjointSet dsu = DisjointSet(n);

    aristas = 0;
    
    ll i;

    for(i = 0; i < E.size(); i++){

        ll w1 = std::get<0>(E[i]);
        ll u1 = std::get<1>(E[i]);
        ll v1 = std::get<2>(E[i]);


        if (i < (E.size() - 1))
        {
            ll w2 = std::get<0>(E[(i + 1)]);
            ll u2 = std::get<1>(E[(i + 1)]);
            ll v2 = std::get<2>(E[(i + 1)]);

            //La arista actual y la siguiente tienen el mismo peso
            if (w1 == w2)
            {
                crearGPrima(E, i, dsu, aristas, n);
            }else//La arista actual y la siguiente tienen pesos distintos
            {
                //Si la arista actual une componentes conexas distinas
                if (dsu.findSet(u1) != dsu.findSet(v1))
                {
                    dsu.unionByRank(u1, v1);
                
                    aristas++;

                    std::get<0>(E[i]) = -1;  //ANY
                }else
                {   //Si no
                    std::get<0>(E[i]) = -3;  //NONE
                }
                
            }

        }else{
            //u y v estan en distinta componente conexa?
            if(dsu.findSet(u1) != dsu.findSet(v1)){
                dsu.unionByRank(u1, v1);
                aristas++;
                std::get<0>(E[i]) = -1;   //ANY
            }else{
                std::get<0>(E[i]) = -3;   //NONE
            }
        }

        if(aristas == (n - 1)) break;
    }

    i++; //Aumento i para que apunte al la primer arista que Kruscal no recorio

    //Seteo todas las aristas que Kruscal no recorrio como NONE
    while (i < E.size())
    {
        std::get<0>(E[i]) = -3; //NONE
        i++;
    }
    
    /*
    if(aristas == (n - 1)) {
        cout << "Peso " << res << " Cant aristas " << aristas << '\n';
    }else{
        cout<<"IMPOSSIBLE\n";
    }*/
}

int main() {

    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll n, m, u, v, w;

    cin >> n >> m;

    //             u,  v, peso, orden original en el que se metio
    vector<tuple<ll, ll, ll, ll> > lAristas(m);
    tuple<ll, ll, ll, ll> aux;

    for (ll i = 0; i < m; i++)
    {
        cin >> u >>  v >> w;
        aux = make_tuple(w, u, v, i);
        lAristas[i] = aux;
    }

    kruskal(lAristas, n);

    sort(lAristas.begin(), lAristas.end(), compDePosicion);
    
    //EN LA COMPONENTE CORRESPONDIENTE AL PESO -1 == ANY; -2 == AT LEAST ONE; -3 == NONE
    for (ll i = 0; i < m; i++)
    {
        if (std::get<0>(lAristas[i]) == -1)
        {
            cout << "any" << "\n";
        }else if(std::get<0>(lAristas[i]) == -2){
            cout << "at least one" << "\n";
        }else if(std::get<0>(lAristas[i]) == -3){
            cout << "none" << "\n";
        }else{
            cout << "AAAA" << "\n";
        }
    }
}