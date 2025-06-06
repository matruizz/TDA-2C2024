
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;

long long int j;


bool existeJQueNoEstaEnqueueYNoFueVisitado(unordered_set<long long int> &elementosEnQueue, set<long long int> &adyacentesAi, vector<long long int> &visitado){

    set<long long int>::iterator adyacente = adyacentesAi.begin();
    bool res = false;

    //  Si no llegue al final de los vecinos de i    y      (si esta en la queue           o         ya fue recorrido)
    while ((adyacente != adyacentesAi.end()) && (res != true))
    {
        if ((elementosEnQueue.find(*adyacente) == elementosEnQueue.end()) && (visitado[*adyacente] == -1))
        {
            j = *adyacente;
            res = true;
        }

        adyacente++;
    }

    return res;
}

void bfs(unordered_map<long long int, set<long long int>> &lAdya, vector<long long int> &visitado, vector<long long int> &dist){
        
    long long int r = 1;                // Elegir un vertice 1 como raiz
    
    visitado[r] = 1;                    // Seteo a la raiz como visitada
    
    queue<long long int> queue;         // Defino la queue para hacer BFS
    unordered_set<long long int> copia;

    queue.push(r);           // Meto la raiz dentro de la queue O(1)
    copia.insert(r);

    while (!queue.empty())   // Mientras que la queue no este vacia
    {
        long long int i = queue.front(); // Elijo un nodo i de la queue   O(1)

        //Si existe un arco (i, j) tal que j /∈ queue entonces
        if (existeJQueNoEstaEnqueueYNoFueVisitado(copia, lAdya.at(i), visitado))   //Si un j adyacente a i no esta en la queue
        {
            dist[j] = dist[i] + 1;
            visitado[j] = 1;        //visitado[j] = 1
            queue.push(j);          //LISTA ← LISTA ∪ {j}
            copia.insert(j);
        }else{
            queue.pop();
            copia.erase(i);
        }
    }
}


int main() {
    
    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);

    long long int n, u, v;

    cin >> n;    

    vector<long long int> visitados (n + 1);
    for (long long int i = 0; i < (n + 1); i++)
    {
        visitados[i] = -1;
    }

    vector<long long int> dist (n + 1);
    for (long long int i = 0; i < (n + 1); i++)
    {
        if (i != 1)
        {
            dist[i] = -1;
        }else{
            dist[i] = 0;
        }
    }

    //Solo funciona para arboles, por lo tanto solo recibe (n - 1) aristas.
    unordered_map<long long int, set<long long int>> listaAdyacencias;

    for (long long int i = 0; i < n; i++)
    {
        listaAdyacencias.insert( make_pair<long long int, set<long long int>>((i + 1), {}));
    }
    

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
        bfs(listaAdyacencias, visitados, dist);

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