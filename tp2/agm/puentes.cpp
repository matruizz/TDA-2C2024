
#include <bits/stdc++.h>

using namespace std;



vector<vector<int>> ady;
vector<int> estado;
vector<int> memo;
vector<int> padre;
vector<vector<int>> tree_edges;
vector<int> back_edges_con_extremo_inferior_en;
vector<int> back_edges_con_extremo_superior_en;
int NO_LO_VI = 0, EMPECE_A_VER = 1, TERMINE_DE_VER = 2;


int cubren(int v, int p) {

    if (memo[v] != -1) return memo[v];
    
    int res = 0;

    for (int hijo : tree_edges[v]) {
        if (hijo != p && ) {
            res += cubren(hijo, v);
        }
    }

    res += back_edges_con_extremo_superior_en[v];
    
    res -= back_edges_con_extremo_inferior_en[v];

    memo[v] = res;
    
    return res;
}


void dfs(int v, int p = -1) {

    estado[v] = EMPECE_A_VER;

    for (int u : ady[v]) {

        if (estado[u] == NO_LO_VI) {
            tree_edges[v].push_back(u);
            padre[u] = v;
            dfs(u, v);
        }
        else if (u != padre[v]) {
            if (estado[u] == EMPECE_A_VER) {
                back_edges_con_extremo_superior_en[v]++;
            }
            else // estado[u] == TERMINE_DE_VER
                back_edges_con_extremo_inferior_en[v]++;
        }
    }

    estado[v] = TERMINE_DE_VER;
}

int main(){

    int n, m, u, v;

    cin >> n >> m;

    for (int i = 0; i < (n + 1); i++)
    {
        estado.push_back(0);
        memo.push_back(-1);
        padre.push_back(0);
        vector<int> aux;
        back_edges_con_extremo_inferior_en.push_back(0);
        back_edges_con_extremo_superior_en.push_back(0);

        tree_edges.push_back(aux);
        ady.push_back(aux);
    }

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        ady[u].push_back(v);
        ady[v].push_back(u);
    }

    int cantConexas = 0;

    for (int i = 1; i <= n; i++)
    {
        if (estado[i] == 0)
        {
            dfs(i);
            cantConexas++;
        }
    }

    vector<int> c(n);

    int cantPuentes = 0;

    for (int i = 1; i <= n; i++)
    {
        cout << cubren(i, padre[i]) << '\n';
        if (cubren(i, padre[i]) == 0)
        {
            cantPuentes++;
        }
    }
    cout << "la cantidad de aristas puentes es: " << cantPuentes - cantConexas;

    



    


    return 0;
}