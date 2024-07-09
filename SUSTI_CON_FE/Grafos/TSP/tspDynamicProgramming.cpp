#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9; // Un valor grande para representar el infinito
int n; // Número de ciudades

int dist[][4] = {
    {  0, 10, 15, 20 },
    {  10, 0, 25, 25 }, { 15, 25, 0, 30 },
    {  20, 25, 30, 0 },
};
 
int tsp() {
    // dp[mask][i] - la distancia mínima para visitar todas las ciudades en 'mask' terminando en la ciudad 'i'
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    dp[1][0] = 0; // Empezar en la ciudad 0 con solo la ciudad 0 visitada tiene una distancia de 0
    
    // Iterar sobre todos los subconjuntos de ciudades
    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) { // Si la ciudad 'i' está en el subconjunto 'mask'
                // Intentar extender el recorrido a una nueva ciudad 'j'
                for (int j = 0; j < n; ++j) {
                    if (!(mask & (1 << j))) { // Si la ciudad 'j' no está en el subconjunto 'mask'
                        dp[mask | (1 << j)][j] = min(dp[mask | (1 << j)][j], dp[mask][i] + dist[i][j]);
                    }
                }
            }
        }
    }
    
    // Encontrar el recorrido óptimo que termina en cualquier ciudad y regresa a la ciudad 0
    int ans = INF;
    for (int i = 1; i < n; ++i) {
        ans = min(ans, dp[(1 << n) - 1][i] + dist[i][0]);
    }
    return ans;
}

int main() {
    cin >> n;

    cout << "La distancia mínima es: " << tsp() << endl;

    return 0;
}
