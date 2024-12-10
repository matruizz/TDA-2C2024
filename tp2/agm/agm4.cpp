
#include <bits/stdc++.h>

using namespace std;


bool compDePeso(tuple<int, int, int, int> &a, tuple<int, int, int, int> &b){

    if (std::get<2>(a) <= std::get<2>(b))
    {
        return true;
    }else{
        return false;
    }
}


bool compDePosicion(tuple<int, int, int, int> &a, tuple<int, int, int, int> &b){

    if (std::get<3>(a) <= std::get<3>(b))
    {
        return true;
    }else{
        return false;
    }
}


class DisjointSet {

    vector<int> rank, parent;
public:
    DisjointSet(int &n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for(int i = 0; i < n + 1; i++){
            parent[i] = i;
        }
    }

    //Find implementado con path compression
    int findSet(int &node){

        // En caso que nodo sea el representante
        if (node == parent[node]) return node;

        // Hago path compression
        //En c++ return de una asignacion devuelve una referencia a lo que esta a la izquiereda del =
        //Es decir esto retorna una referencia al padre del nodo actual
        return parent[node] = findSet(parent[node]);
    }

    void unionByRank(int &u, int &v) {
        int uRepresentative = findSet(u);
        int vRepresentative = findSet(v);

        // Si tienen el mismo representante, entonces pertenece al
        // mismo conjunto
        if (uRepresentative == vRepresentative) return;

        // Actualizamos el representante segun el caso del rank
        if (rank[uRepresentative] < rank[vRepresentative]) {
            parent[vRepresentative] = uRepresentative;
        } else if(rank[uRepresentative] > rank[vRepresentative]) {
            parent[uRepresentative] = vRepresentative;
        } else {
            parent[vRepresentative] = uRepresentative;
            rank[uRepresentative]++;
        }
    }
};



//void IS_BRIDGE(int v,int to); // some function to process the found bridge
int cantVerticesGPrima; // number of nodes
vector<vector<pair<int, int> > > adj; // adjacency list of graph

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p, vector<tuple<int, int, int, int>> &E, int &k) {

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
            dfs(aux, v, E, k);

            low[v] = min(low[v], low[aux]);

            if (low[aux] > tin[v])
                //IS_BRIDGE(v, aux);
                cout << (v + 1) << " " << (aux + 1) << " Orden " << to.second << "\n";

                //Conseguir E por referencia y poner at least one
                std::get<2>(E[k + to.second]) = 1;  //AT LEAST ONE
        }
    }
}

void find_bridges(vector<tuple<int, int, int, int> > &E, int &k, int &aristas) {
    timer = 0;
    visited.assign(cantVerticesGPrima, false);
    tin.assign(cantVerticesGPrima, -1);
    low.assign(cantVerticesGPrima, -1);
    int cantComConex = 0;
    for (int i = 0; i < cantVerticesGPrima; ++i) {
        if (!visited[i])
            dfs(i, -1, E, k);
            cantComConex++;
    }
    aristas =  aristas + (cantVerticesGPrima - cantComConex);
}



void crearGPrima(vector<tuple<int, int, int, int> > &E, int &k, DisjointSet &disSet, int &aristas){

    //cantMismoW es cantidad de aristas con el mismo peso
    int cantMismoW = 0;
    unordered_set<int> reprePresentesGPrima;

    //Aca se cuentan la cantidad de aristas del mismo peso y cuantas componentes conexas unen
    //Es decir cuento la cantidad de aristas a recorrer en E y la cantidad de vertices de G'
    while (std::get<2>(E[k]) == std::get<2>(E[k + cantMismoW])) //O(CANT ARISTAS DEL MISMO PESO * 2) peor caso O(n)
    {
        //Cant de aristas en E con el mismo peso
        cantMismoW++;

        //u y v son vertices de G
        int u = std::get<0>(E[k + cantMismoW]);
        int v = std::get<1>(E[k + cantMismoW]);

        //Estos van a ser los vertices de G'
        int repreU = disSet.findSet(u);
        int repreV = disSet.findSet(v);

        //En g' solo voy a tener aristas que unan comp Conex distintas, por lo tanto
        //si una arista une dos vertices de la misma comp conex no lo voy a meter a g'
        //entonces no cuento a esa comp conex como vertice de g'
        if (repreU != repreV)
        {
            //Si todavia no meti a esta comp conex a g' la cuento
            if (reprePresentesGPrima.count(repreU) == 0)
            {
                reprePresentesGPrima.insert(repreU);
            }

            //Si todavia no meti a esta comp conex a g' la cuento
            if (reprePresentesGPrima.count(repreV) == 0)
            {
                reprePresentesGPrima.insert(repreU);
            }
        }
    }


    cantVerticesGPrima = reprePresentesGPrima.size();   //O(1)
    //Armo G'
    adj.assign(cantVerticesGPrima, {}); //O(n)


    for (int i = 0; i < cantMismoW; i++)
    {
        int u = std::get<0>(E[k + i]);
        int v = std::get<1>(E[k + i]);

        //G' tiene como nodos a los representantes de los nodos del grafo original
        int repreU = disSet.findSet(u);
        int repreV = disSet.findSet(v);

        //Si tienen el mismo representante
        if (repreU == repreV)
        {
            std::get<2>(E[k + i]) = 2;  //NONE

        }else{//Si tienen representantes distintos, meto sus representantes como nodos en el G'

            pair<int, int> aux = make_pair(repreV - 1, i);
            adj[repreU - 1].push_back(aux);

            aux = make_pair(repreU - 1, i);
            adj[repreV - 1].push_back(aux);

            //adj[repreU - 1].push_back(repreV - 1);
            //adj[repreV - 1].push_back(repreU - 1);
        }
    }

    find_bridges(E, k, aristas);

    
    k = k + cantMismoW - 1;
}


void kruskal(vector<tuple<int, int, int, int>> &E, int &n){

    long long res = 0;

    sort(E.begin(), E.end(), compDePeso);

    DisjointSet dsu = DisjointSet(n);

    int aristas = 0;
    
    int i;
    for(i = 0; i < E.size(); i++){
        
        int u1 = std::get<0>(E[i]);
        int v1 = std::get<1>(E[i]);
        int w1 = std::get<2>(E[i]);

        if (i < (E.size() - 1))
        {
            int u2 = std::get<0>(E[(i + 1)]);
            int v2 = std::get<1>(E[(i + 1)]);
            int w2 = std::get<2>(E[(i + 1)]);

            //u y v estan en distinta componente conexa y la arista tiene peso distinto a la siguiente?
            if( (dsu.findSet(u1) != dsu.findSet(v1)) && (w1 != w2) ){
                dsu.unionByRank(u1, v1);
                res += w1;
                aristas++;
                std::get<2>(E[i]) = 0;  //ANY

            //u y v estan en distinta componente conexa y la arista tiene igual peso a la siguiente
            }else if( (dsu.findSet(u1) != dsu.findSet(v1)) && (w1 == w2)){
                //crear G'
                crearGPrima(E, i, dsu, aristas);
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
                std::get<2>(E[i]) = 0;  //ANY
            }
        }

        if(aristas == (n - 1)) break;
    }

    i++; //Aumento i para que apunte al la primer arista que Kruscal no recorio

    //Seteo todas las aristas que Kruscal no recorrio como none
    while (i < E.size())
    {
        std::get<2>(E[i]) = 2; //NONE
    }
    
    if(aristas == n-1) cout << "Peso" << res << "Cant aristas " << aristas << '\n';
    else cout<<"IMPOSSIBLE\n";
}

int main() {

    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, u, v, w;

    cin >> n >> m;

                //u, v, peso, orden original en el que se metio
    vector<tuple<int, int, int, int> > lAristas(m);
    tuple<int, int, int, int> aux;

    for (int i = 0; i < m; i++)
    {
        cin >> u >>  v >> w;
        aux = make_tuple(u, v, w, i);
        lAristas[i] = aux;
    }

    kruskal(lAristas, n);

    sort(lAristas.begin(), lAristas.end(), compDePosicion);
    
    //EN LA COMPONENTE CORRESPONDIENTE AL PESO 0 == ANY; 1 == AT LEAST ONE; 2 == NONE
    for (int i = 0; i < m; i++)
    {
        if (std::get<2>(lAristas[i]) == 0)
        {
            cout << "any" << "\n";
        }else if(std::get<2>(lAristas[i]) == 1){
            cout << "at least one" << "\n";
        }else if(std::get<2>(lAristas[i]) == 2){
            cout << "none" << "\n";
        }else{
            cout << "w" << "\n";
        }
    }
}