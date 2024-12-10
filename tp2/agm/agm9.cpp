
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


bool compDePeso(vector<ll> &a, vector<ll> &b){

    //Si el peso de a es menor o igualque el peso de b
    if (a[2] <= b[2])
    {
        return true;
    }else{
        return false;
    }
}


bool compDePosicion(vector<ll> &a, vector<ll> &b){

    //Si el numero de orden de a es menor que el numero de orden de b
    if (a[3] <= b[3])
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



void dfs(ll v, ll p, vector<vector<ll> > &E, ll &k, ll &aristas) {

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
                E[k + to.second][2] = -1;  //ANY

            }
        }
    }
}

void find_bridges(vector<vector<ll> > &E, ll &k, ll &aristas, ll &n) {

    timer = 0;

    visited.assign(n, false);

    tin.assign(n, -1);

    low.assign(n, -1);

    ll cantComConex = 0;
    cantVerticesGPrima = 0;

    for (ll i = 0; i < n; ++i) {

        if ((!visited[i]) && (adj[i].size() > 0)){
            dfs(i, -1, E, k, aristas);
            cantComConex++;
        }

        if (adj[i].size() > 0)
        {
            cantVerticesGPrima++;
        }
    }

    aristas =  aristas + (cantVerticesGPrima - cantComConex);
}



void crearGPrima(vector<vector<ll> > &E, ll &k, DisjointSet &disSet, ll &aristas, ll &n){

    ll cantMismoW = 0;

    adj.assign(n, {});

    ll peso = E[k][2];

    while ((k + cantMismoW < E.size()))
    {
        if (E[k + cantMismoW][2] == peso)
        {
            ll u = E[k + cantMismoW][0];
            ll v = E[k + cantMismoW][1];

            //G' tiene como nodos a los representantes de los nodos del grafo original
            ll repreU = disSet.findSet(u);
            ll repreV = disSet.findSet(v);

            //Si tienen el mismo representante
            if (repreU == repreV)
            {
                E[k + cantMismoW][2] = -3;  //NONE

            }else{//Si tienen representantes distintos, meto sus representantes como nodos en el G'

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
        //Si no son ni ANY y tampoco NONE tienen que ser AT LEAST ONE
        if ((E[k + j][2] != -1) && (E[k + j][2] != -3))
        {
            E[k + j][2]= -2;
        }

        //Si son AT LEAST ONE y unen componentes conexas distintas entonces union by rank
        if (E[k + j][2] == -2)
        {
            ll u = E[k + j][0];
            ll v = E[k + j][1];

            ll repreU = disSet.findSet(u);
            ll repreV = disSet.findSet(v);

            if (repreU != repreV)
            {
                disSet.unionByRank(u, v);
            }
        }

        //Si son any union by rank
        if (E[k + j][2] == -1)
        {
            ll u = E[k + j][0];
            ll v = E[k + j][1];
            disSet.unionByRank(u, v);
        }        
    }

    k = k + cantMismoW - 1;
}


void kruskal(vector<vector<ll> > &E, ll &n){

    sort(E.begin(), E.end(), compDePeso);

    DisjointSet dsu = DisjointSet(n);

    ll aristas = 0;
    
    ll i;

    for(i = 0; i < E.size(); i++){
        
        ll u1 = E[i][0];
        ll v1 = E[i][1];
        ll w1 = E[i][2];

        if (i < (E.size() - 1))
        {
            ll u2 = E[(i + 1)][0];
            ll v2 = E[(i + 1)][1];
            ll w2 = E[(i + 1)][2];

            //u y v estan en distinta componente conexa y la arista tiene peso distinto a la siguiente?
            if( (dsu.findSet(u1) != dsu.findSet(v1)) && (w1 != w2) ){
                
                dsu.unionByRank(u1, v1);
                
                aristas++;

                E[i][2] = -1;  //ANY

            //u y v estan en distinta componente conexa y la arista tiene igual peso a la siguiente
            }else if( (dsu.findSet(u1) != dsu.findSet(v1)) && (w1 == w2)){
                //crear G'
                crearGPrima(E, i, dsu, aristas, n);
                //tiene que poder contar cuantas aristas van a ir en el arbol  
                //correr puentes en G'
            }
        }else{
            //u y v estan en distinta componente conexa?
            if(dsu.findSet(u1) != dsu.findSet(v1)){
                dsu.unionByRank(u1, v1);
                aristas++;
                E[i][2] = -1;  //ANY
            }
        }

        if(aristas == (n - 1)) break;
    }

    i++; //Aumento i para que apunte al la primer arista que Kruscal no recorio

    //Seteo todas las aristas que Kruscal no recorrio como none
    while (i < E.size())
    {
        E[i][2] = -3; //NONE
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
    vector<vector<ll> > lAristas(m);

    vector<ll>  aux;
    aux.assign(4, 0);

    for (ll i = 0; i < m; i++)
    {
        cin >> u >>  v >> w;

        aux[0] = u;
        aux[1] = v;
        aux[2] = w;
        aux[3] = i;

        lAristas[i] = aux;
    }

    kruskal(lAristas, n);

    sort(lAristas.begin(), lAristas.end(), compDePosicion);
    
    //EN LA COMPONENTE CORRESPONDIENTE AL PESO -1 == ANY; -2 == AT LEAST ONE; -3 == NONE
    for (ll i = 0; i < m; i++)
    {
        if (lAristas[i][2] == -1)
        {
            cout << "any" << "\n";
        }else if(lAristas[i][2] == -2){

            cout << "at least one" << "\n";
        }else if(lAristas[i][2] == -3){

            cout << "none" << "\n";
        }else{
            cout << "AAAA" << "\n";
        }
    }
}