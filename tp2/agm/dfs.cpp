
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;

vector<pair<uint64_t, uint64_t>> listaDeAristas;

uint64_t n, m, u, v, j;


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


void dfs(map<int, set<int>> &lAdya, int *pred, int *orden, int *desde, int *hasta, int r){

    //Salida: pred[i] = padre de vi , orden[i] = numero asignado a vi
    int next = 1;
    int timer = 0;
    
    pred[r] = 0;            // El predecesor de la raiz es el 0
    
    orden[r] = next;        // Numero de orden de la raiz
    
    stack<int> pila;        // Defino la pila para hacer DFS
    set<int> copiaPila;     // Creo una copia de la pila para poder encontrar adyacentes a i que no esten en la pila

    pila.push(1);           // Meto la raiz dentro de la pila
    copiaPila.insert(1);    // Hago lo mismo para la copia
    timer++;
    desde[r] = timer;
    
    int iterador = 0;

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

    for (int i = 1; i < (n + 1); i++)
    {
        if (orden[i] == -1)
        {
            dfs(lAdya, pred, orden, desde, hasta, i);
        }
        
    }
    


}


int main() {

    cout << "Ingrese cantidad de nodos:";
    cin >> n;

    cout << "Ingrese cantidad de aristas:";
    cin >> m;

    vector<pair<uint64_t,uint64_t>> listaDeAristas(n);
    
    map<int, set<int>> listaAdyacencias;
    for (int i = 0; i < n; i++)
    {
        listaAdyacencias.insert(make_pair<int, set<int>>((i+1), {}));
    }
    
    int pred [(n + 1)];
    int orden [(n + 1)];
    int desde[(n + 1)];
    int hasta[(n + 1)];

    for (int i = 0; i < (n + 1); i++)
    {
        pred[i] = -1;
        orden[i] = -1;
        desde[i] = -1;
        hasta[i] = -1;
    }
    

    if (n <= 1)
    {
        cout << 0 << "\n";
    }else{
        for (uint64_t i = 0; i < m; i++)
        {
            cin >> u >> v;
            listaAdyacencias.at(u).insert(v);
            listaAdyacencias.at(v).insert(u);
        }

        int r = 1;
        dfs(listaAdyacencias, pred, orden, desde, hasta, r);


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
    }
}