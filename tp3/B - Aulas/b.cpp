
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n, m, aux1, aux2, sumVerificadora;
vector<ll> a, b;
vector<pair<ll, ll>> validos;

void aulas(){

    while(1){
        
    }




}

int main() {

    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    a.assign(n, 0);
    b.assign(n, 0);
    sumVerificadora = 0;

    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
        sumVerificadora += a[i];
    }

    for (ll i = 0; i < n; i++)
    {
        cin >> b[i];
        sumVerificadora -= b[i];
    }    

    for (ll i = 0; i < m; i++)
    {
       
        cin >> aux1 >> aux2;

        if (aux1 > 0)
        {
            validos.assign(n, make_pair(0, 0));
        }

        validos[i] = make_pair(aux1, aux2);
    }

    if (sumVerificadora || (validos.size() == 0))
    {
        cout << "NO" << "\n";
        return 0;
    }

    aulas();

    return 0;
}