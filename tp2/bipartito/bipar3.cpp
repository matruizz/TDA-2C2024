
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;

long long int j;


bool existeJQueNoEstaEnqueue(unordered_set<long long int> &elementosEnQueue, set<long long int> &adyacentesAi, vector<long long int> &orden){

    set<long long int>::iterator adyacente = adyacentesAi.begin();
    bool res = false;
    //  Si no llegue al final de los vecinos de i    y      (si esta en la queue           o         ya fue recorrido)
    while ((adyacente != adyacentesAi.end()) && ((elementosEnQueue.count(*adyacente) != 0) || (orden[*adyacente] != -1)))
    {
        adyacente++;
    }

    if ((adyacente != adyacentesAi.end()) && (elementosEnQueue.count(*adyacente) == 0) && (orden[*adyacente] == -1))
    {
        j = *adyacente;
        res = true;
    }

    return res;
}

void bfs(unordered_map<long long int, set<long long int>> &lAdya, vector<long long int> &orden, vector<long long int> &dist){

    //Salida: pred[i] = padre de vi , orden[i] = numero asignado a vi
    long long int ord = 1;
    
    long long int r = 1;              // Elegir un vertice 1 como raiz
    
    orden[r] = ord;         // Numero de orden de la raiz
    
    queue<long long int> queue;        // Defino la queue para hacer BFS
    unordered_set<long long int> copiaQueue;     // Creo una copia de la queue para poder encontrar adyacentes a i que no esten en la queue

    queue.push(r);           // Meto la raiz dentro de la queue O(1)
    copiaQueue.insert(r);    // Hago lo mismo para la copia     O(1)
    
    while (!queue.empty())   // Mientras que la queue no este vacia
    {
        long long int i = queue.front(); // Elijo un nodo i de la queue   O(1)

        //Si existe un arco (i, j) tal que j /∈ queue entonces
        if (existeJQueNoEstaEnqueue(copiaQueue, lAdya.at(i), orden))   //Si un j adyacente a i no esta en la queue
        {
            dist[j] = dist[i] + 1;
            ord++;             //ord ← ord + 1
            orden[j] = ord;    //orden[j] ← ord
            queue.push(j);       //LISTA ← LISTA ∪ {j}
            copiaQueue.insert(j);
        }else{
            queue.pop();
            copiaQueue.erase(i);
        }
    }
}


int main() {

    long long int n, u, v;

    cin >> n;    
    
    unordered_map<long long int, set<long long int>> listaAdyacencias;
    for (long long int i = 0; i < n; i++)                                         //O(n.log(n))
    {
        listaAdyacencias.insert(make_pair<long long int, set<long long int>>((i+1), {}));   //O(log(n))
    }

    vector<long long int> orden (n + 1);
    for (long long int i = 0; i < (n + 1); i++)
    {
        orden[i] = -1;
    }

    vector<long long int> dist (n + 1);
    for (long long int i = 1; i < (n + 1); i++)
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
        for (long long int i = 0; i < (n - 1); i++)       //O(n.log(n))
        {
            cin >> u >> v;
            listaAdyacencias.at(u).insert(v);
            listaAdyacencias.at(v).insert(u);
        }

        //Solo reciben arboles
        bfs(listaAdyacencias, orden, dist);

        long long int count = 0;

        for (long long int i = 1; i < (n + 1); i++)
        {
            if((dist[i] % 2) == 0){
                count++;
            }
        }

        cout << ((n - count) * count) - (n - 1);

    }
}