
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;

bool comp(pair<int, int> x, pair<int, int> y){
    return (x<y);
}

int main() {

    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<pair<int, int>> a = {make_pair(3, 3), make_pair(1, 1), make_pair(2, 2)}; 
    
    vector<pair<int, int>>::iterator i = a.begin();
    vector<pair<int, int>>::iterator j = a.end();

    sort(i, j, comp);
    int x = 0;
}