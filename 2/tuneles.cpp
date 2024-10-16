
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;


void tuneles(vector<int> &atajos){

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

    tuneles(atajos);

    return 0;
}