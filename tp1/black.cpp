
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;

int n = 0;

int maximo(int a, int b, int c){

    if (a >= b && a >= c)
    {
        return a;
    }else if(b >= a && b >= c ){
        return b;
    }else{
        return c;
    }

}
int f(vector<vector<vector<int> > > &m, vector<int> &v, int i, int inc, int dec){


    if (i == n)
    {
        return 0;

    }else if(m[i][inc + 1][dec + 1] != -1){   //Si el resultado ya fue calculado

        return m[i][inc + 1][dec + 1];

    }else if ((inc == -1) && (dec == -1))//-----//Si los dos estan vacios------------
    {

        m[i][inc + 1][dec + 1] = maximo(f(m, v, i + 1, i, dec) + 1, f(m, v, i + 1, inc, i) + 1, f(m, v, i + 1, inc, dec));
        return m[i][inc + 1][dec + 1];

    }else if ((inc == -1) && (dec != -1))//-----//Si solo inc esta vacio-------------
    {
        if (v[dec] <= v[i])  //No puede entrar en dec
        {
            m[i][inc + 1][dec + 1] = max(f(m, v, i + 1, i, dec) + 1, f(m, v, i + 1, inc, dec));
            return m[i][inc + 1][dec + 1];
        }else{              //Puede entrar en dec

            m[i][inc + 1][dec + 1] = maximo(f(m, v, i + 1, i, dec) + 1, f(m, v, i + 1, inc, i) + 1, f(m, v, i + 1, inc, dec));
            return m[i][inc + 1][dec + 1];
        }
    }else if((inc != -1) && (dec == -1))//------//Si solo dec esta vacio--------------
    {
        if (v[inc] >= v[i]) //No puede entrar en inc
        {
            m[i][inc + 1][dec + 1] = max(f(m, v, i + 1, inc, i) + 1, f(m, v, i + 1, inc, dec));
            return m[i][inc + 1][dec + 1];
        }else{             //Puede entrar en dec

            m[i][inc + 1][dec + 1] = maximo(f(m, v, i + 1, i, dec) + 1, f(m, v, i + 1, inc, i) + 1, f(m, v, i + 1, inc, dec));
            return m[i][inc + 1][dec + 1];
        }
    }else if ((inc != -1) && (dec != -1))//-----//Si ninguno esta vacio---------------
    {
        if((v[inc] < v[i]) && (v[dec] <= v[i])){   //Solo puede entrar en increasing
            
            m[i][inc + 1][dec + 1] = max(f(m, v, i + 1, i, dec) + 1, f(m, v, i + 1, inc, dec));
            return m[i][inc + 1][dec + 1];

        }else if((v[dec] > v[i]) && (v[inc] >= v[i])){   //Solo pude entrar en decreasing
            
            m[i][inc + 1][dec + 1] = max(f(m, v, i + 1, inc, i) + 1, f(m, v, i + 1, inc, dec));
            return m[i][inc + 1][dec + 1];
        
        }else if((v[inc] >= v[i]) && (v[dec] <= v[i])){ //No puede entrar en ninguno

            m[i][inc + 1][dec + 1] = f(m, v, i + 1, inc, dec);
            return m[i][inc + 1][dec + 1];

        }else{
        
            m[i][inc + 1][dec + 1] = maximo(f(m, v, i + 1, i, dec) + 1, f(m, v, i + 1, inc, i) + 1, f(m, v, i + 1, inc, dec));
            return m[i][inc + 1][dec + 1];
        }
    }
}

int main() {

    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);

    vector<int> res;
    int contador = 0;
    int aux = 0;

    cin >> n;

    while (n != (-1))
    {
        
        vector<int> caso(n);

        for (int i = 0; i < n; i++)
        {
            cin >> caso[i];
        }

        vector<vector<vector<int> > > m (caso.size(),  (vector<vector<int> > (caso.size() + 1, vector<int> (caso.size() + 1))));
        
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < (n + 1); j++)
            {
                for (int k = 0; k < (n + 1); k++)
                {
                    m[i][j][k] = -1;
                }
                
            }
        }

        aux = n - f(m, caso, 0, -1, -1);

        res.push_back(aux);

        contador++;

        cin >> n;
    }

    for (int i = 0; i < contador; i++)
    {
        cout << res[i] << endl;
    }    
}