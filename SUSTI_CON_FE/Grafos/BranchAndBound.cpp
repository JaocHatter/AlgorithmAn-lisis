#include <bits/stdc++.h>
using namespace std;
//Estrategia:
//Usaremos una tabla de booleanos para representar si el espacio está ocupado
//o no

//Estructuras
struct Objeto {
    int ancho, alto;
    Objeto(int a, int h) : ancho(a), alto(h) {}
};
struct Contenedor {
    int ancho, alto;
    Contenedor(int a, int h) : ancho(a), alto(h) {}
};
struct Nodo {
    int nivel, beneficio, areaLibre;
    std::vector<std::vector<bool>> layout;
    Nodo(int n, int b, int a, std::vector<std::vector<bool>> l)
        : nivel(n), beneficio(b), areaLibre(a), layout(l) {}
};

//Función Cabe:
/*
Esta función nos indicará si podemos colocar un objeto en
cierto espacio del contenedor
*/
bool cabe(const Objeto &obj, const Contenedor &cont, int x, int y, const std::vector<std::vector<bool>> &layout) {
    if (x + obj.ancho > cont.ancho || y + obj.alto > cont.alto) return false;
    for (int i = 0; i < obj.ancho; ++i)
        for (int j = 0; j < obj.alto; ++j)
            if (layout[x + i][y + j]) return false;
    return true;
}
//Función Coloca:
/*
Esta función marcará como True a cada espacio del contenedor que
sea ocupado por un objeto
*/
void coloca(Objeto obj, int x, int y, std::vector<std::vector<bool>> &layout) {
    for (int i = 0; i < obj.ancho; ++i)
        for (int j = 0; j < obj.alto; ++j)
            layout[x + i][y + j] = true;
}

void ramificacionPoda(const std::vector<Objeto> &objetos, const Contenedor &cont){
    int mejorBeneficio = 0;
    std::vector<std::vector<bool>> mejorLayout(cont.ancho, std::vector<bool>(cont.alto, false));
    //Iniciamos nuestro arbol con una tabla vacia
    Nodo root(0, 0, cont.ancho * cont.alto, mejorLayout);
    std::vector<Nodo> stack = { root };
    
    //Iniciamos el algoritmo de Branching and Prunning
    //Para representar la recursividad usaremos una Pila
    while (!stack.empty()){
        //removemos el primer elemento de la pila
        Nodo actual = stack.back();
        stack.pop_back();
        if(actual.nivel == objetos.size()){
            //se establece como mejor beneficio y mejor layout
            if(actual.beneficio > mejorBeneficio){
                mejorBeneficio = actual.beneficio;
                mejorLayout = actual.layout;
            }
            //ya no continuamos, solo lo eliminamos de la pila
            continue;
        } 
        //tomamos un objeto para añadir
        const Objeto &obj = objetos[actual.nivel];
        //averiguemos todas las posibilibidades en la que cabe
        for(int i=0;i<cont.ancho;++i){
            for(int j=0;j<cont.alto;++j){
                if(cabe(obj,cont,i,j,actual.layout)){
                    std::vector<std::vector<bool>> nuevoLayout = actual.layout;
                    int newBeneficio = actual.beneficio + obj.alto * obj.ancho;
                    int nuevaAreaLibre = actual.areaLibre - obj.alto * obj.ancho;
                    coloca(obj,i,j,nuevoLayout);
                    if(newBeneficio > mejorBeneficio){
                        stack.emplace_back(actual.nivel+1,newBeneficio,nuevaAreaLibre,nuevoLayout);
                    }
                }
            }
        }
        stack.emplace_back(actual.nivel+1,actual.beneficio,actual.areaLibre,actual.layout);
    }
    cout<<"Mejor Beneficio: "<<mejorBeneficio<<endl;
}
int main() {
    Contenedor cont(3, 3); 
    std::vector<Objeto> objetos = { Objeto(2, 2), Objeto(1, 1),Objeto(1, 1),Objeto(3,2)};
    ramificacionPoda(objetos, cont);
    return 0;
}