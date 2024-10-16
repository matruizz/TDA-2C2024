
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;

vector<pair<uint64_t, uint64_t>> listaDeAristas;

int j;


bool existeJQueNoEstaEnCola(set<int> &elementosEnCola, set<int> &adyacentesAi, vector<int> &orden){

    set<int>::iterator adyacente = adyacentesAi.begin();
    bool res = false;
    //                                                       si esta en la cola                                  ya fue recorrido
    while ((adyacente != adyacentesAi.end()) && ((elementosEnCola.find(*adyacente) != elementosEnCola.end()) || (orden[*adyacente] != -1)))
    {
        adyacente++;
    }

    if (adyacente != adyacentesAi.end() && (elementosEnCola.find(*adyacente) == elementosEnCola.end()) && (orden[*adyacente] == -1))
    {
        j = *adyacente;
        res = true;
    }

    return res;
}

void bfs(map<int, set<int>> &lAdya, vector<int> &orden, vector<int> &dist){

    //Salida: pred[i] = padre de vi , orden[i] = numero asignado a vi
    int ord = 1;
    
    int r = 1;              // Elegir un vertice 1 como raiz
    
    orden[r] = ord;        // Numero de orden de la raiz
    
    queue<int> cola;        // Defino la cola para hacer DFS
    set<int> copiaCola;     // Creo una copia de la cola para poder encontrar adyacentes a i que no esten en la cola

    cola.push(1);           // Meto la raiz dentro de la cola
    copiaCola.insert(1);    // Hago lo mismo para la copia
    
    while (!cola.empty())   // Mientras que la cola no este vacia
    {
        int i = cola.front(); // Elijo un nodo i de la cola

        //Si existe un arco (i, j) tal que j /∈ cola entonces
        if (existeJQueNoEstaEnCola(copiaCola, lAdya.at(i), orden))   //Si un j adyacente a i no esta en la cola
        {
            dist[j] = dist[i] + 1;
            ord++;             //ord ← ord + 1
            orden[j] = ord;    //orden[j] ← ord
            cola.push(j);       //LISTA ← LISTA ∪ {j}
            copiaCola.insert(j);
        }else{
            cola.pop();
            copiaCola.erase(i);
        }
    }
}


int main() {

    uint64_t n, u, v;

    cin >> n;

    vector<pair<uint64_t,uint64_t>> listaDeAristas(n);
    
    map<int, set<int>> listaAdyacencias;
    for (int i = 0; i < n; i++)
    {
        listaAdyacencias.insert(make_pair<int, set<int>>((i+1), {}));
    }

    vector<int> orden (n + 1);

    for (int i = 0; i < (n + 1); i++)
    {
        orden[i] = -1;
    }

    vector<int> dist (n + 1);

    for (int i = 1; i < (n + 1); i++)
    {
        if (i != 1)
        {
            dist[i] = -1;
        }else{
            dist[i] = 0;
        }
    }
    

    //Solo funciona para arboles, por lo tanto solo recibe (n - 1) aristas.

    if (n <= 1)
    {
        cout << 0 << "\n";
    }else{
        for (uint64_t i = 0; i < (n - 1); i++)
        {
            cin >> u >> v;
            listaAdyacencias.at(u).insert(v);
            listaAdyacencias.at(v).insert(u);
        }

        //Solo reciben arboles
        bfs(listaAdyacencias, orden, dist);

        int count = 0;

        for (int i = 1; i < (n + 1); i++)
        {
            if((dist[i] % 2) == 0){
                count++;
            }
        }

        cout << ((n - count) * count) - (n - 1);

    }
}