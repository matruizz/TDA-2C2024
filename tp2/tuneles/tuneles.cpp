
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;

int j;


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

    int n;
    cin >> n;

    vector<int> atajos(n);

    for (int i = 0; i < n; i++)
    {
        cin >> atajos[i];
    }

    vector<set<long long int>> lAdyacencias(n);

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            lAdyacencias[i].insert(i + 1);
            if (atajos[i] - 1 != i)
            {
                lAdyacencias[i].insert(atajos[i] - 1);
            }
            
        }else if (i == (n - 1))
        {
            lAdyacencias[i].insert(i - 1);
        }else{
            if (atajos[i] - 1 != i)
            {
                lAdyacencias[i].insert(atajos[i] - 1);
            }
            lAdyacencias[i].insert(i - 1);
            lAdyacencias[i].insert(i + 1);
            
        }
    }

    vector<long long int> visitados(n);
    vector<long long int> dist(n);
    
    for (int i = 0; i < n; i++)
    {
        visitados[i] = -1;
        dist[i] = -1;
    }
    dist[0] = 0;
    
    bfs(lAdyacencias, visitados, dist);

    for (int i = 0; i < n; i++)
    {
        if (i == (n - 1))
        {
            cout << dist[i];
        }else{
            cout << dist[i] << " ";
        }
        
    }

    return 0;
}