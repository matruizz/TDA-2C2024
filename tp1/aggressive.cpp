
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;

int t = 0, n = 0, c = 0, minDistance = 1000000000, maxDistance = 0;

bool cow(vector<int> &stalls, int &cows, int &minMaxDistance){

    int vacas = cows;

    vacas--;

    int ult = 0, act = 0;

    while ((act < stalls.size()) && (vacas > 0))
    {
        if ((stalls[act] - stalls[ult]) >= minMaxDistance)
        {
            ult = act;
            vacas--;
        }
        act++;
    }
    if (vacas == 0)
    {
        return true;
    }
    
    return false;
}

int aggresive(vector<int> &stalls, int &cows){

    int aux = 1;

    while(cow(stalls, cows, aux)) {
        aux++;
    }
    aux--;
    return aux;
}


int main() {

    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;
    
    vector<int> res (t);

    for (int i = 0; i < t; i++)
    {
        cin >> n >> c;

        vector<int> stalls(n);

        for (int j = 0; j < n; j++)
        {
            cin >> stalls[j];

            if (stalls[j] > maxDistance)
            {
                maxDistance = stalls[j];
            }
            if(stalls[j] < minDistance){
                minDistance = stalls[j];
            }
        }
        vector<int>::iterator start = stalls.begin();
        vector<int>::iterator finish = stalls.end();
        sort(start, finish);

        res[i] = aggresive(stalls, c);

        minDistance = 1000000000;
        maxDistance = 0;
    }
    for (int i = 0; i < t; i++)
    {
        cout << res[i] << endl;
    }
    
}