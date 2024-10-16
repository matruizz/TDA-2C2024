
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;

int main() {

    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    /*
    Para recibir todo un string entero, con espacios incluidos
    si recibe un string que tiene espacios normalmente los toma 
    como strings separados pero en este caso no.*/
    string s;
    getline(cin, s);
    
    //Recibe una cantidad indeterminada de enteros y sale del while
    //cuando recibe algo que no es un entero
    int x, res = 0;
    while (cin >> x) {
        res = res + x;
    }

    cout << res << " " << s << "\n";

    //Manera correcta de comparar dos numeros flotantes entre si
    double a, b;
    long double e = 1e-9;
    if (abs(a-b) < e) {
        // a and b are equal
    }
}
/*
COMO COMPILAR

g++ -std=c++11 -O2 -Wall test.cpp -o test

Compila el programa con g++ siguiendo el standar c++11, lo optimiza,
muestra todos los warnings del codigo fuente en test.cpp y genera un
ejecutable llamado test.
*/