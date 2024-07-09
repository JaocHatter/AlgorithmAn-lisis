#include <bits/stdc++.h>
using namespace std;

class Graph {
    int V; // Número de vértices
    vector<vector<int>> graph; // Lista de adyacencia para almacenar el grafo

    // Función para encontrar el conjunto de un elemento i (con compresión de caminos)
    int find(vector<int>& parent, int i){
        if(parent[i] == i){
            return i;
        }
        return find(parent,i);
    }

    // Función para unir dos conjuntos de x e y (usando unión por rango)
    void unionSet(vector<int>& parent, vector<int>& rank, int x, int y) {
        int xroot = find(parent, x);
        int yroot = find(parent, y);
        
        // Adjuntar el árbol de menor rango bajo la raíz del árbol de mayor rango (Unión por rango)
        if (rank[xroot] < rank[yroot]) {
            parent[xroot] = yroot;
        } else if (rank[xroot] > rank[yroot]) {
            parent[yroot] = xroot;
        } else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }

public:
    Graph(int vertices) {
        V = vertices;
        graph = vector<vector<int>>();
    }

    // Función para añadir una arista al grafo
    void addEdge(int u, int v, int w) {
        graph.push_back({ u, v, w });
    }

    void boruvkaMST() {
        vector<int> parent(V);
        vector<int> rank(V, 0);
        vector<vector<int>> cheapest(V, vector<int>(3, -1));
        int numTrees = V;
        int MSTweight = 0;

        for (int node = 0; node < V; node++) {
            parent[node] = node;
        }
        while(numTrees > 1){
            for(int a = 0; a < graph.size(); a++){
                int u = graph[a][0],v = graph[a][1] , w = graph[a][2];
                int p1 = find(parent, u), p2 = find(parent, v);
                if(p1 != p2){
                    if(cheapest[p1][2] == -1 || cheapest[p1][2] > w) cheapest[p1] ={u,v,w} ;
                    if(cheapest[p2][2] == -1 || cheapest[p2][2] > w) cheapest[p2] = {u,v,w};
                }
            }
            for(int i=0;i<V;i++){
                //si es que i es un nodo padre
                if(cheapest[i][2] != -1){
                    
                    int u = cheapest[i][0], v = cheapest[i][1], w = cheapest[i][2];
                    int p1 = find(parent, u), p2 = find(parent, v);
                    if(p1 != p2){
                        MSTweight += w;
                        cout << "Edge " << u << "-" << v << " with weight " << w << " included in MST" << endl;
                        unionSet(parent,rank,p1,p2);
                        numTrees--;
                    }
                }
            }
            //reiniciamos el array de aristas minimas
            for(int k = 0;k < V; k++){
                cheapest[k][2] = -1;
            }
        }
        cout << "Weight of MST is " << MSTweight << endl;
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    g.boruvkaMST();
    return 0;
}
