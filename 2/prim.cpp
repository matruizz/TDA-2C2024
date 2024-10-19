
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;


set<ll> vertices;
set<pair<pair<ll, ll>, ll>> aristas;


void elegirAristaPrim(vector<vector<ll>> &mAdyacencias, set<ll> &vertices, set<pair<pair<ll, ll>, ll>> &aristas, ll &pesoMin, ll &uMin, ll &vMin){

    set<ll>::iterator itVertices = vertices.begin();

    while(itVertices != vertices.end()){

        for (ll i = 0; i < mAdyacencias.size(); i++)
        {
            if ((mAdyacencias[*itVertices][i] < pesoMin) && (vertices.find(i) == vertices.end()))
            {
                pesoMin = mAdyacencias[*itVertices][i];
                uMin = *itVertices;
                vMin = i;
            }
        }

        itVertices++;
    }

}


//Prim implementado con matriz de adyacencia
void prim(vector<vector<ll>> &mAdyacencias){

    vertices.insert(0);

    int i = 0;

    while (i < (mAdyacencias.size() - 1))
    {
        ll pesoMin = 10000000, uMin = 0, vMin = 0;
        //Elegir arista con peso minimo de entre las que son incidentes a u y un vertice que no fue visitado
        elegirAristaPrim(mAdyacencias, vertices, aristas, pesoMin, uMin, vMin);
        vertices.insert(vMin);                                      //Agrego vertice
        aristas.insert(make_pair(make_pair(uMin, vMin), pesoMin));  //Agrego arista
        i++;
    }
    int a = 0;
}


int main() {

    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);

    //n: vertices, m: aristas
    int n, m, a, b, w;
    cin >> n >> m;

    vector<vector<ll>> mAdyacencias(n, vector<ll>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mAdyacencias[i][j] = 1000000;
        }
        
    }

    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> w;
        
        mAdyacencias[a - 1][b - 1] = w;
        mAdyacencias[b - 1][a - 1] = w;
    }

    prim(mAdyacencias);

    set<pair<pair<ll, ll>, ll>>::iterator it = aristas.begin();

    while (it != aristas.end())
    {
        if (it == --aristas.end())
        {
            cout << (*it).second << endl;
        }else{
            cout << (*it).second << " ";
        }
        it++;
    }

    return 0;
}