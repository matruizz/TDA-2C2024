
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


void crearGPrima(vector<tuple<int, int, int, int> > &E, int &k, DisjointSet &disSet, int &aristas){

    //it es cantidad de aristas con el mismo peso
    int it = 0;

    while (std::get<2>(E[k]) == std::get<2>(E[k + it]))
    {
        it++;
    }

    //   u        v  indice
    map<int, map<int, int>> lAdyacencias;


    for (int i = 0; i < it; i++)
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
            map<int, int> aux1, aux2;

            //   Si U todavia no esta en el grafo
            if (lAdyacencias.find(repreU) == lAdyacencias.end())
            {
                aux1.insert(make_pair(repreV, (k + i)));
                lAdyacencias.insert(make_pair(repreU, aux1));

                aux2.insert(make_pair(repreU, (k + i)));
                lAdyacencias.insert(make_pair(repreV, aux2));

            }else{
                //                           Si U no es adyacente a V
                if (lAdyacencias.at(repreU).find(repreV) == lAdyacencias.at(repreU).end())
                {
                    aux1.insert(make_pair(repreV, (k + i)));
                    lAdyacencias.insert(make_pair(repreU, aux1));

                    aux2.insert(make_pair(repreU, (k + i)));
                    lAdyacencias.insert(make_pair(repreV, aux2));

                }else{
                    //seteo a esta arista como AT LEAST ONE
                    std::get<2>(E[k + i]) = 1;
                    int aux = ((lAdyacencias.at(repreU)).at(repreV));
                    std::get<2>(E[aux]) = 1;

                }
            }
        }
    }
    
    k = k + it - 1;
}


void kruskal(vector<tuple<int, int, int, int>> &E, int &n){

    long long res = 0;

    sort(E.begin(), E.end(), compDePeso);

    DisjointSet dsu = DisjointSet(n);

    int aristas = 0;
    
    for(int i = 0; i < E.size(); i++){
        
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
                //std::get<2>(E[i]) = 0;  //ANY

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
                //std::get<2>(E[i]) = 0;  //AT LEAST ONE
            }
        }

        if(aristas == (n - 1)) break;
    }
    
    cout << aristas << '\n';
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