#include <bits/stdc++.h>
using namespace std;

struct arista {
    int idxDestino;
    int peso;
    arista *sgteArista;
};
typedef arista *parista;

struct vertice {
    int idx;
    int datoOrigen;
    arista *adyacente;
    vertice *sgteVertice;
};
typedef vertice *pvertice;

vector<pvertice> g(1000);
vector<int> ord(1000, -1);

class grafo {
    private:
        pvertice pGrafo;
    public:
        grafo();
        ~grafo();
        void insertarVertice(int);
        void insertarArista(int, int, int);
        void imprimirGrafo();
        void dijkstra(int,int);
};

grafo::grafo() {
    pGrafo = NULL;
}

grafo::~grafo() {
    pvertice p, rp;
    parista r, ra;
    p = pGrafo;
    while (p != NULL) {
        r = p->adyacente;
        while (r != NULL) {
            ra = r;
            r = r->sgteArista;
            delete ra;
        }
        rp = p;
        p = p->sgteVertice;
        delete rp;
    }
}

void grafo::insertarVertice(int idx) {
    if (g[idx] != nullptr) {
        cout << "Identificador ya ocupado" << endl;
        return;
    }
    pvertice aux;
    aux = new vertice;
    aux->idx = idx;
    aux->adyacente = NULL;
    aux->sgteVertice = pGrafo;
    pGrafo = aux;
    g[idx] = aux;
}

void grafo::insertarArista(int idx, int idy, int peso) {
    pvertice p1, p2;
    parista a;
    p1 = g[idx];
    p2 = g[idy];
    if (p1 != NULL && p2 != NULL) {
        a = new arista;
        a->idxDestino = p2->idx;
        a->peso = peso;
        a->sgteArista = p1->adyacente;
        p1->adyacente = a;
    }
}

void grafo::dijkstra(int origen,int num) {
    vector<int> dist(1000, INT_MAX);
    vector<bool> visitado(1000, false);
    dist[origen] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0,dist[origen]});
    int costo = 0;
    while(!pq.empty()){
        int v = pq.top().first;
        pq.pop();
        if(visitado[v]) continue;
        cout<<"La distancia minima al nodo: "<<v<<" es "<<dist[v]<<endl;
        visitado[v] = true;
        parista ady = g[v]->adyacente;
        while(ady != NULL){
            int w = ady->peso;
            if(!visitado[ady->idxDestino] && dist[ady->idxDestino] > dist[v] + w){
                dist[ady->idxDestino] = dist[v] + w;
                pq.push({ady->idxDestino,dist[ady->idxDestino]});
            }
            ady = ady->sgteArista;
        }
    }
}

int main() {
    grafo g;
    g.insertarVertice(0);
    g.insertarVertice(1);
    g.insertarVertice(2);
    g.insertarVertice(3);
    g.insertarVertice(4);
    g.insertarVertice(5);

    g.insertarArista(0, 1, 41);
    g.insertarArista(0, 5, 29);
    g.insertarArista(1, 2, 51);
    g.insertarArista(1, 4, 32);
    g.insertarArista(2, 3, 50);
    g.insertarArista(3 , 0, 45);
    g.insertarArista(3, 5, 38);
    g.insertarArista(4, 2, 32);
    g.insertarArista(4, 3, 36);
    g.insertarArista(5, 1, 24);
    g.insertarArista(5, 4, 21);

    g.dijkstra(0,6);

    return 0;
}
