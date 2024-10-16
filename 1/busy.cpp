
 //jncluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;


bool comp(pair<int, int> x, pair<int, int> y){
    return (x.second < y.second);
}


int busy(vector<pair<int, int> > v){

    int res = 1;
    int ult = 0;    //Indice del ultimo intervalo que se conto

    for (int i = 1; i < v.size(); i++)
    {
        if (v[ult].second <= v[i].first)
        {
            ult = i;
            res++;
        }
    }

    return res;
}


int main() {

    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 0, n = 0;
    
    cin >> t;   //# Tests cases 1 <= t <= 10

    vector<vector<pair<int, int> > > testCase(t);

    for (int i = 0; i < t; i++)
    {

        cin >> n;   //# Actividades del test case 1 <= N <= 100000

        for (int j = 0; j < n; j++)
        {
            //0 <= start < end <= 1000000
            int s, f;
            cin >> s >> f;

            testCase[i].push_back(make_pair(s,f));
        }

        vector<pair<int, int> >::iterator inicio = testCase[i].begin();
        vector<pair<int, int> >::iterator fin = testCase[i].end();

        sort(inicio, fin, comp);
    }

    cout << endl;

    for (int i = 0; i < testCase.size(); i++)
    {
        cout << busy(testCase[i]) << endl;
    }



    /*for (int i = 0; i < testCase.size(); i++)
    {
        for (int j = 0; j < testCase[i].size(); j++)
        {
            cout << testCase[i][j].first << ", " << testCase[i][j].second << endl;
        }
        cout << endl;
    }*/
}