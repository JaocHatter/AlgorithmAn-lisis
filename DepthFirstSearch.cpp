#include <bits/stdc++.h>
using namespace std;
struct arista{
    int idxDestino;
    int peso;
    arista *sgteArista;
};
typedef arista *parista;
struct vertice{
    int idx;
    int datoOrigen;
    arista *adyacente;
    vertice *sgteVertice;
};
typedef vertice *pvertice;

vector<pvertice> g(1000);

class grafo{
    private:
        pvertice pGrafo;
    public:
        grafo();
        ~grafo();
        void insertarVertice(int,int);
        void insertarArista(int,int,int);
        void imprimirGrafo();
        void DFS(int,int,string);
};

grafo::grafo(){
    pGrafo=NULL;
}
grafo::~grafo(){
    pvertice p,rp;
    parista r,ra;
    p=pGrafo;
    while(p!=NULL){
        r=p->adyacente;
        while(r!=NULL){
            ra=r;
            r = r->sgteArista;
            delete ra;
        }
        rp=p;
        p=p->sgteVertice;
        delete rp;
    }
}
void grafo::insertarVertice(int x, int idx){
    if(g[idx] != NULL){
        cout<<"Indice ya ocupado"<<endl;
        return;
    }
    pvertice aux;
    aux = new vertice;
    aux->idx = idx;
    aux->datoOrigen=x;
    aux->adyacente=NULL;
    aux->sgteVertice=pGrafo;
    pGrafo = aux;
    g[idx] = aux;
}
void grafo::insertarArista(int idx, int idy,int weight){
    pvertice p1;
    parista a;
    p1=g[idx];
    if(p1!=NULL && g[idy]!=NULL){
        a = new arista;
        a->idxDestino = idy;
        a->peso = weight;
        a->sgteArista = p1->adyacente;
        p1->adyacente = a;
    }
}

void grafo::imprimirGrafo(){
    pvertice p;
    parista a;
    p=pGrafo;
    if(p==NULL) cout<<"Grafo vacio"<<endl;
    else
        while(p!=NULL){
            cout<<p->idx<<" ";
            a=p->adyacente;
            cout<<" Adyacentes: ";
            while(a!=NULL){
                cout<<a->idxDestino<<" ";
                a=a->sgteArista;
            }
            cout<<endl;
            p=p->sgteVertice;
        }
}
bool visited[1000] = {false};
void grafo::DFS(int x, int y,string z){
    visited[x] = true;
    if(x == y){
        cout<<z<<endl;
        return;
    }
    parista a = g[x]->adyacente;
    while(a != NULL){
        if(!visited[a->idxDestino]){
            DFS(a->idxDestino,y,z+"->"+to_string(a->idxDestino));
        }
        a = a->sgteArista;
    }
    return;
}
int main(){
    grafo g;
    int x,y;
    
    g.insertarVertice(4,0);
    g.insertarVertice(6,1);
    g.insertarVertice(3,2);
    g.insertarVertice(4,3);

    cout<< "Vert-Aristas" <<endl;
    g.insertarArista(0,1,3);
    g.insertarArista(1,2,2);
    g.insertarArista(2,3,5);
    g.insertarArista(2,4,7);

    g.imprimirGrafo();

    g.DFS(0,2,to_string(0));
}