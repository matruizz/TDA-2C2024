//Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>
 
using namespace std;
 
int t = 0, n = 0, c = 0, minDistance = 1000000001, maxDistance = -1;
 
bool stallsForAllCowsWithThisMaxMin(vector<int> &stallsPositions, int &cows, int &maxMinDistance){


    int vacas = cows;

    vacas--;

    int ult = 0, act = 0;

    while ((act < stallsPositions.size()) && (vacas > 0))
    {
        if ((stallsPositions[act] - stallsPositions[ult]) >= maxMinDistance)
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
 
int aggresive(vector<int> &stallsPositions, int &cows){
    //Hay que elegir la distancia media como la maxima distancia media porque en este problema eso equivale a
    //empezar la busqueda binaria por el valor medio, si en cambio eligieramos la distancia entre el maximo y 
    //el minimo como la maxima distancia minima eso equivaldria a empezar la busqueda binaria por el maximo 
    //del conjunto de elementos a buscar en lugar de empezar a buscar por el valor medio lo cual empeora la
    //complejidad temporal de la busqueda binaria.
    int maxMinDistance = (int) std::round(((minDistance + maxDistance) * 1.0) / 2);
 
    while((minDistance + 1 ) < maxDistance) {
 
        if (stallsForAllCowsWithThisMaxMin(stallsPositions, cows, maxMinDistance))
        {
            minDistance = maxMinDistance;
        }else{
            maxDistance = maxMinDistance;
        }
 
        maxMinDistance = (int) std::round(((minDistance + maxDistance) * 1.0) / 2);
    }
    
    if (stallsForAllCowsWithThisMaxMin(stallsPositions, cows, minDistance))
    {
        return minDistance;
    }else{
        return minDistance - 1;
    }
}
 
 
int main() {
 
    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    cin >> t;
 
    vector<int> res (t);
 
    for (int i = 0; i < t; i++)
    {
        cin >> n >> c;  //n: number of stalls; c: number of cows
 
        vector<int> stallsPositions(n);
 
        for (int j = 0; j < n; j++)
        {
            cin >> stallsPositions[j];
 
            if (stallsPositions[j] > maxDistance)
            {
                maxDistance = stallsPositions[j];
            }
            if(stallsPositions[j] < minDistance){
                minDistance = stallsPositions[j];
            }
        }

        vector<int>::iterator start = stallsPositions.begin();
        vector<int>::iterator finish = stallsPositions.end();
        sort(start, finish);
 
        res[i] = aggresive(stallsPositions, c);
 
        minDistance = 1000000001;
        maxDistance = -1;
    }
    for (int i = 0; i < t; i++)
    {
        cout << res[i] << "\n";
    }
    
} 