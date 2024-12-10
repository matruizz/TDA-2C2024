
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;

typedef uint64_t ll;

ll n, aux, sum, hola;
unordered_set<ll> construidos;
vector<ll> ord, res;


void floyd(vector<vector<ll>> &m){

    sum = 0;

    for (ll k = 0; k < n; k++)
    {

        aux = ord[n - k - 1];       //O(1)
        construidos.insert(aux);    //O(1)

        for (ll i = 0; i < n; i++)
        {
            for (ll j = 0; j < n; j++)
            {
                hola = m[i][aux] + m[aux][j];
                if (m[i][j] > hola)
                {
                    m[i][j] = hola;
                }

                if ((construidos.find(i) != construidos.end()) && (construidos.find(j) != construidos.end()))   //O(1)
                {
                    sum = sum + m[i][j];    //O(1)
                }
            }
        }

        res[n - k - 1] = sum;
        
        sum = 0;
    }
}

//WRONG ANSWER IN TEST 30

int main() {

    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    vector<vector<ll>> m(n, vector<ll>(n));     //O(n^2)

    ord.assign(n, 0);   //O(n)
    res.assign(n, 0);   //O(n)

    for (ll i = 0; i < n; i++)  //O(n^2)
    {
        for (ll j = 0; j < n; j++)
        {
            cin >> aux;
            m[i][j] = aux;
        }
    }

    for (ll i = 0; i < n; i++)  //O(n)
    {
        cin >> aux;
        ord[i] = aux - 1;
    }

    floyd(m);

    for (ll i = 0; i < n; i++)
    {
        if (i != (n - 1))
        {
            cout << res[i] << " ";
        }else{
            cout << res[i] << "\n";
        }
    }

    return 0;
}