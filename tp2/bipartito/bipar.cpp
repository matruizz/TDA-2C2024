
 //Incluye la libreria standar completa... iostream, algorithm, vector
#include <bits/stdc++.h>

using namespace std;

int main() {

    uint64_t n = 1;
    uint64_t u, v;
    uint64_t cantA = 0;
    uint64_t cantB = 0;

    cin >> n;

    if (n <= 1)
    {
        cout << 0 << "\n";
    }else{
        vector<uint64_t> A((n + 1), 0);
        vector<uint64_t> B((n + 1), 0);

        for (uint64_t i = 0; i < (n - 1); i++)
        {
            cin >> u >> v;

            if ( ((A[u] == 0) && (B[u] == 0) && (A[v] == 0) && (B[v] == 0)) || (A[u] != 0) || (B[v] != 0))
            {
                A[u]++;
                B[v]++;
            }else{
                A[v]++;
                B[u]++;
            }
        }

        for (uint64_t i = 1; i < (n + 1); i++){
            if (A[i] != 0)
            {
                cantA++;
            }

            if (B[i] != 0)
            {
                cantB++;
            }
        }

        uint64_t res = ((cantA * cantB) - (n - 1));

        cout << res << "\n";
    }
}