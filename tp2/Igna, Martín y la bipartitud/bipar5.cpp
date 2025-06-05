
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;

long long int j;


bool existeJ(set<long long int> &adyacentesAi, vector<long long int> &elementosEnQueue, vector<long long int> &visitado){

    set<long long int>::iterator it = adyacentesAi.begin();
    bool res = false;

    //Recorro adyacentesAi mientras que res sea false 
    while ((it != adyacentesAi.end()) && (res == false))
    {   //  Si no esta en la lista        y     no fue visitado
        if ((elementosEnQueue[*it] == -1) && (visitado[*it] == -1))
        {
            j = *it;
            res = true;
        }
        it++;
    }

    if (res == true)
    {
        it--;
        adyacentesAi.erase(it);
    }
    

    return res;
}

void bfs(vector<set<long long int>> &lAdyacencias, vector<long long int> &visitados, vector<long long int> &dist){
    
    visitados[0] = 1;                    // Seteo a la raiz como visitada

    queue<long long int> lista;         // Defino la lista para hacer BFS

    vector<long long int> copiaLista(dist.size());
    
    for (int i = 0; i < copiaLista.size(); i++)
    {
        copiaLista[i] = -1;
    }
    
    lista.push(0);           // Meto la raiz dentro de la lista O(1)
    copiaLista[0] = 1;

    while (!lista.empty())   // Mientras que la lista no este vacia
    {
        long long int i = lista.front(); // Elijo un nodo i de la lista   O(1)

        //Si existe un arco (i, j) tal que j /∈ lista entonces
        if (existeJ(lAdyacencias[i], copiaLista, visitados))   //Si un j adyacente a i no esta en la lista
        {
            dist[j] = dist[i] + 1;
            visitados[j] = 1;        //visitado[j] = 1
            lista.push(j);          //LISTA ← LISTA ∪ {j}
            copiaLista[j] = 1;
        }else{
            lista.pop();
            copiaLista[i] = -1;
        }
    }
}


int main() {

    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);

    long long int n, u, v;

    cin >> n;


    if (n <= 1)
    {
        cout << 0 << "\n";
    }else{
        
        vector<set<long long int>> lAdyacencias(n);

        for (long long int i = 0; i < (n - 1); i++)       //O(n.log(n))
        {
            cin >> u >> v;
            lAdyacencias[u - 1].insert(v - 1);
            lAdyacencias[v - 1].insert(u - 1);
        }


        vector<long long int> visitados (n);

        for (long long int i = 0; i < n; i++)
        {
            visitados[i] = -1;
        }


        vector<long long int> dist (n);

        for (long long int i = 1; i < n; i++)   //dist[0] = 0
        {
            dist[i] = -1;
        }

        //Solo reciben arboles
        bfs(lAdyacencias, visitados, dist);

        long long int count = 0;

        for (long long int i = 0; i < n; i++)
        {
            if((dist[i] % 2) == 0){
                count++;
            }
        }

        cout << ((n - count) * count) - (n - 1);

    }
}