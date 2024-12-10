
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;

vector<pair<uint64_t, uint64_t>> listaDeAristas;

int j;

bool existeJQueNoEstaEnPila(set<int> elementosEnPila, set<int> adyacentesAi, int *orden){

    set<int>::iterator adyacente = adyacentesAi.begin();
    bool res = false;
    //                                                       si esta en la pila                                  ya fue recorrido
    while ((adyacente != adyacentesAi.end()) && ((elementosEnPila.find(*adyacente) != elementosEnPila.end()) || (orden[*adyacente] != -1)))
    {
        adyacente++;
    }

    if (adyacente != adyacentesAi.end() && (elementosEnPila.find(*adyacente) == elementosEnPila.end()) && (orden[*adyacente] == -1))
    {
        j = *adyacente;
        res = true;
    }

    return res;
}


void dfs(map<int, set<int>> &lAdya, int *pred, int *orden, int *desde, int *hasta){

    //Salida: pred[i] = padre de vi , orden[i] = numero asignado a vi
    int next = 1;
    int timer = 0;
    int r = 1;              // Elegir un vertice 1 como raiz
    
    pred[r] = 0;            // El predecesor de la raiz es el 0
    
    orden[r] = next;        // Numero de orden de la raiz
    
    stack<int> pila;        // Defino la pila para hacer DFS
    set<int> copiaPila;     // Creo una copia de la pila para poder encontrar adyacentes a i que no esten en la pila

    pila.push(1);           // Meto la raiz dentro de la pila
    copiaPila.insert(1);    // Hago lo mismo para la copia
    timer++;
    desde[r] = timer;
    
    while (!pila.empty())   // Mientras que la pila no este vacia
    {
        int i = pila.top(); // Elijo un nodo i de la PILA

        //Si existe un arco (i, j) tal que j /∈ PILA entonces
        if (existeJQueNoEstaEnPila(copiaPila, lAdya.at(i), pred))   //Si un j adyacente a i no esta en la pila
        {
            timer++;
            desde[j] = timer;
            pred[j] = i;        //pred[j] ← i (marcar vertice j)

            next++;             //next ← next + 1
            orden[j] = next;    //orden[j] ← next
            pila.push(j);       //LISTA ← LISTA ∪ {j}
            copiaPila.insert(j);
        }else{
            timer++;
            hasta[i] = timer; 
            pila.pop();
            copiaPila.erase(i);
        }
    }
    
    //retornar pred y orden
}


bool existeJQueNoEstaEnCola(set<int> elementosEnCola, set<int> adyacentesAi, int *orden){

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

void bfs(map<int, set<int>> &lAdya, int *pred, int *orden){

    //Salida: pred[i] = padre de vi , orden[i] = numero asignado a vi
    int ord = 1;
    
    int r = 1;              // Elegir un vertice 1 como raiz
    
    pred[r] = 0;            // El predecesor de la raiz es el 0
    
    orden[r] = ord;        // Numero de orden de la raiz
    
    queue<int> cola;        // Defino la cola para hacer DFS
    set<int> copiaCola;     // Creo una copia de la cola para poder encontrar adyacentes a i que no esten en la cola

    cola.push(1);           // Meto la raiz dentro de la cola
    copiaCola.insert(1);    // Hago lo mismo para la copia
    
    while (!cola.empty())   // Mientras que la cola no este vacia
    {
        int i = cola.front(); // Elijo un nodo i de la cola

        //Si existe un arco (i, j) tal que j /∈ cola entonces
        if (existeJQueNoEstaEnCola(copiaCola, lAdya.at(i), pred))   //Si un j adyacente a i no esta en la cola
        {
            pred[j] = i;        //pred[j] ← i (marcar vertice j)
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

    cout << "Ingrese cantidad de nodos:";
    cin >> n;

    vector<pair<uint64_t,uint64_t>> listaDeAristas(n);
    
    map<int, set<int>> listaAdyacencias;
    for (int i = 0; i < n; i++)
    {
        listaAdyacencias.insert(make_pair<int, set<int>>((i+1), {}));
    }
    
    int pred [(n + 1)];
    int orden [(n + 1)];
    int predBFS [(n + 1)];
    int ordenBFS [(n + 1)];
    int desde[(n + 1)];
    int hasta[(n + 1)];
    for (int i = 0; i < (n + 1); i++)
    {
        pred[i] = -1;
        orden[i] = -1;
        predBFS[i] = -1;
        ordenBFS[i] = -1;
        desde[i] = -1;
        hasta[i] = -1;
    }
    
    cout << "Solo funciona para arboles, por lo tanto solo recibe (n - 1) aristas." << endl;

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
        dfs(listaAdyacencias, pred, orden, desde, hasta);
        bfs(listaAdyacencias, predBFS, ordenBFS);


        //Predecesores
        cout << "Predecesores DFS: ";
        for (int i = 1; i < (n + 1); i++)
        {
            cout << pred[i];
            if (i != n)
            {
                cout << ", ";
            }else{
                cout << ".";
            }
        }
        cout << endl;
        //Orden
        cout << "Orden DFS: ";
        for (int i = 1; i < (n + 1); i++)
        {
            cout << orden[i];
            if (i != n)
            {
                cout << ", ";
            }else{
                cout << ".";
            }
        }
        cout << endl;
        //Predecesores BFS
        cout << "Predecesores BFS: ";
        for (int i = 1; i < (n + 1); i++)
        {
            cout << predBFS[i];
            if (i != n)
            {
                cout << ", ";
            }else{
                cout << ".";
            }
        }
        cout << endl;
        //Orden BFS
        cout << "Orden BFS: ";
        for (int i = 1; i < (n + 1); i++)
        {
            cout << ordenBFS[i];
            if (i != n)
            {
                cout << ", ";
            }else{
                cout << ".";
            }
        }
        cout << endl;

    }
}