
#include <bits/stdc++.h>

using namespace std;


//void IS_BRIDGE(int v,int to); // some function to process the found bridge
long long cantVerticesGPrima; // number of nodes
vector<vector<pair<long long, long long> > > adj; // adjacency list of graph

vector<bool> visited;
vector<long long> tin, low;
long long timer;


bool compDePeso(tuple<long long, long long, long long, long long> &a, tuple<long long, long long, long long, long long> &b){

    if (std::get<2>(a) <= std::get<2>(b))
    {
        return true;
    }else{
        return false;
    }
}


bool compDePosicion(tuple<long long, long long, long long, long long> &a, tuple<long long, long long, long long, long long> &b){

    if (std::get<3>(a) <= std::get<3>(b))
    {
        return true;
    }else{
        return false;
    }
}


class DisjointSet {

    vector<long long> rank, parent;
public:
    DisjointSet(long long &n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for(long long i = 0; i < n + 1; i++){
            parent[i] = i;
        }
    }

    //Find implementado con path compression
    long long findSet(long long &node){

        // En caso que nodo sea el representante
        if (node == parent[node]) return node;

        // Hago path compression
        //En c++ return de una asignacion devuelve una referencia a lo que esta a la izquiereda del =
        //Es decir esto retorna una referencia al padre del nodo actual
        return parent[node] = findSet(parent[node]);
    }

    void unionByRank(long long &u, long long &v) {
        long long uRepresentative = findSet(u);
        long long vRepresentative = findSet(v);

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



void dfs(long long v, long long p, vector<tuple<long long, long long, long long, long long>> &E, long long &k, long long &aristas) {

    visited[v] = true;

    tin[v] = low[v] = timer++;
    
    bool parent_skipped = false;

    for (pair<long long, long long> to : adj[v]) {

        long long u = to.first;

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
                std::get<2>(E[k + to.second]) = -1;  //ANY
            }
        }
    }
}

void find_bridges(vector<tuple<long long, long long, long long, long long> > &E, long long &k, long long &aristas, long long &n) {

    timer = 0;

    visited.assign(n, false);

    tin.assign(n, -1);

    low.assign(n, -1);

    long long cantComConex = 0;

    for (long long i = 0; i < n; ++i) {
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



void crearGPrima(vector<tuple<long long, long long, long long, long long> > &E, long long &k, DisjointSet &disSet, long long &aristas, long long &n){

    long long cantMismoW = 0;
    
    cantVerticesGPrima = 0;

    adj.assign(n, {});

    long long peso = std::get<2>(E[k]);

    while ((k + cantMismoW < E.size()))
    {
        if ((std::get<2>(E[k + cantMismoW]) == peso))
        {
            long long u = std::get<0>(E[k + cantMismoW]);
            long long v = std::get<1>(E[k + cantMismoW]);

            //G' tiene como nodos a los representantes de los nodos del grafo original
            long long repreU = disSet.findSet(u);
            long long repreV = disSet.findSet(v);

            //Si tienen el mismo representante
            if (repreU == repreV)
            {
                std::get<2>(E[k + cantMismoW]) = -3;  //NONE

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

    for (long long j = 0; j < cantMismoW; j++)
    {
        //Si no son ni any ni none tienen que ser at least one
        if ((std::get<2>(E[k + j]) != -1) && (std::get<2>(E[k + j]) != -3))
        {
            std::get<2>(E[k + j])= -2;
        }

        //Si son at least one y unen componentes conexas distintas entonces union by rank
        if (std::get<2>(E[k + j]) == -2)
        {
            long long u = std::get<0>(E[k + j]);
            long long v = std::get<1>(E[k + j]);

            long long repreU = disSet.findSet(u);
            long long repreV = disSet.findSet(v);

            if (repreU != repreV)
            {
                disSet.unionByRank(u, v);
            }
        }

        //Si son any union by rank
        if (std::get<2>(E[k + j]) == -1)
        {
            long long u = std::get<0>(E[k + j]);
            long long v = std::get<1>(E[k + j]);
            disSet.unionByRank(u, v);
        }
        
        
    }
    
    
    k = k + cantMismoW - 1;
}


void kruskal(vector<tuple<long long, long long, long long, long long>> &E, long long &n){

    long long res = 0;

    sort(E.begin(), E.end(), compDePeso);

    DisjointSet dsu = DisjointSet(n);

    long long aristas = 0;
    
    long long i;

    for(i = 0; i < E.size(); i++){
        
        long long u1 = std::get<0>(E[i]);
        long long v1 = std::get<1>(E[i]);
        long long w1 = std::get<2>(E[i]);

        if (i < (E.size() - 1))
        {
            long long u2 = std::get<0>(E[(i + 1)]);
            long long v2 = std::get<1>(E[(i + 1)]);
            long long w2 = std::get<2>(E[(i + 1)]);

            //u y v estan en distinta componente conexa y la arista tiene peso distinto a la siguiente?
            if( (dsu.findSet(u1) != dsu.findSet(v1)) && (w1 != w2) ){
                dsu.unionByRank(u1, v1);
                res += w1;
                aristas++;
                std::get<2>(E[i]) = -1;  //ANY

            //u y v estan en distinta componente conexa y la arista tiene igual peso a la siguiente
            }else if( (dsu.findSet(u1) != dsu.findSet(v1)) && (w1 == w2)){
                //crear G'
                crearGPrima(E, i, dsu, aristas, n);
                // tiene que poder contar cuantas aristas van a ir en el arbol  
                //aristas++;
                //correr puentes en G'
            }
        }else{
            //u y v estan en distinta componente conexa?
            if(dsu.findSet(u1) != dsu.findSet(v1)){
                dsu.unionByRank(u1, v1);
                res += w1;
                aristas++;
                std::get<2>(E[i]) = -1;  //ANY
            }
        }

        if(aristas == (n - 1)) break;
    }

    i++; //Aumento i para que apunte al la primer arista que Kruscal no recorio

    //Seteo todas las aristas que Kruscal no recorrio como none
    while (i < E.size())
    {
        std::get<2>(E[i]) = -3; //NONE
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

    long long n, m, u, v, w;

    cin >> n >> m;

    //             u,  v, peso, orden original en el que se metio
    vector<tuple<long long, long long, long long, long long> > lAristas(m);
    tuple<long long, long long, long long, long long> aux;

    for (long long i = 0; i < m; i++)
    {
        cin >> u >>  v >> w;
        aux = make_tuple(u, v, w, i);
        lAristas[i] = aux;
    }

    kruskal(lAristas, n);

    sort(lAristas.begin(), lAristas.end(), compDePosicion);
    
    //EN LA COMPONENTE CORRESPONDIENTE AL PESO -1 == ANY; -2 == AT LEAST ONE; -3 == NONE
    for (long long i = 0; i < m; i++)
    {
        if (std::get<2>(lAristas[i]) == -1)
        {
            cout << "any" << "\n";
        }else if(std::get<2>(lAristas[i]) == -2){
            cout << "at least one" << "\n";
        }else if(std::get<2>(lAristas[i]) == -3){
            cout << "none" << "\n";
        }else{
            cout << "AAAA" << "\n";
        }
    }
}