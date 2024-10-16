
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;


int dec(vector<int> v, int i, int anterior){



    return 0;
}
int increasing(vector<int> v, int i, int anterior, vector<int> noPintados){

    if (i == v.size())
    {
        return 0; //dec(noPintados, 0, 100);
    }else if ((v[i] <= anterior))
    {
        return increasing(v, (i + 1), anterior, noPintados);
    }else{

        vector<int> aux = noPintados;
        
        aux.push_back(v[i]);
        
        return max(increasing(v, (i + 1), v[i], aux) + 1, increasing(v, (i + 1), anterior, noPintados));
    }
}

/*
int increasing(vector<pair<int, int>> &v, int i, int anterior){

    if (i == v.size())
    {
        return 0;//dec(noPintados, 0, 100);
    }else if ((v[i].first <= anterior) || (v[i].second == 1))
    {
        return increasing(v, (i + 1), anterior);
    }else{
        //i++;            //INCREMENTO I PORQUE PASO POR PARAMETRO
        vector<pair<int, int>> copia = v;
        int noPinto = increasing(v, (i + 1), anterior);// i == i + 1

        v[i].second = 1;
        int pinto = increasing(v, (i + 1), v[i].first) + 1;
        
        if (noPinto > pinto)
        {
            v[i].second = 0;
            return noPinto;
        }
        return pinto;
    }
}

int black(vector<pair<int, int>> v){

    int inc = increasing(v, 0, -1);
    cout << inc << endl;

    return 0;
}
*/



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
    //black(datos[0]);
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