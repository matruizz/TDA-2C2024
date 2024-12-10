
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;


int dec(vector<int> v, int i, int anterior){

    if (i == v.size())
    {
        return 0;
    }else if (v[i] >= anterior)
    {
        return dec(v, (i + 1), anterior);
    }else{
        return max(dec(v, i + 1, v[i]) + 1, dec(v, i + 1, v[i]));
    }
    
    

    return 0;
}
int increasing(vector<int> v, int i, int anterior, vector<int> noPintados){

    if (i == v.size())
    {
        return dec(noPintados, 0, 100);
    }else if ((v[i] <= anterior))
    {
        return increasing(v, (i + 1), anterior, noPintados);
    }else{

        vector<int> aux = noPintados;
        
        aux.push_back(v[i]);
        
        return max(increasing(v, (i + 1), v[i], aux) + 1, increasing(v, (i + 1), anterior, noPintados));
    }
}




int main() {

    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n = 0;

    cin >> n;

    vector<vector<pair<int, int>>> datos;

    while (n != (-1))
    {
        vector<pair<int, int>> caso(n);
        for (int i = 0; i < n; i++)
        {
            int aux = 0;
            cin >> aux;
            caso[i] = make_pair(aux, 0);
        }
        
        datos.push_back(caso);
        
        //int res = black(caso);
        //cout << res;

        cin >> n;
    }


    vector<int> v = {2, 3, 4, 10, 5, 6, 1};
    vector<int> vacio;
    int res = increasing(v, 0, -1, vacio);
    cout << res << endl;


    for (int i = 0; i < datos.size(); i++)
    {
        for (int j = 0; j < datos[i].size(); j++)
        {
            cout << datos[i][j].first << ", " << datos[i][j].second << endl;
        }
        cout << endl;
    }
    
    
}