#include <iostream>
#include <conio.h>
#include <string.h>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>

using namespace std;

class Nodo{
public:
    string dato;
    Nodo*derecha;
    Nodo*izquierda;
    Nodo*padre;
};

Nodo*crearNodo(string DATO,Nodo*padre){
    Nodo*NuevoNodo = new Nodo();
    NuevoNodo->dato = DATO;
    NuevoNodo->derecha = NULL;
    NuevoNodo->izquierda = NULL;
    NuevoNodo->padre=padre;

    return NuevoNodo;
}

void incertarNodo(Nodo*&arbol,string DATO,Nodo*padre){
    if(arbol == NULL){
        Nodo*NuevoNodo = crearNodo(DATO,padre);
        arbol = NuevoNodo;
    }else{
        string valorRaiz = arbol->dato;
        //.c_str() comvierte la palabra en arreglo de chars
        if(strcmp(DATO.c_str(),valorRaiz.c_str())>0){//si tengo dos palabras becerro(a incertar) y avion resultado becerro esta despues de avion
            incertarNodo(arbol->derecha,DATO,arbol);
        }else{
            incertarNodo(arbol->izquierda,DATO,arbol);
        }
    }
}

void mostrarArbol(Nodo*arbol, int contador){
    if(arbol==NULL){
        return;
    }else{
        mostrarArbol(arbol->derecha,contador+1);
        for (int i=0;i<contador;i++) {
            cout<<"    ";
        }
        cout<<arbol->dato<<endl;
        mostrarArbol(arbol->izquierda,contador+1);
    }
}

Nodo*minimo(Nodo*arbol){
    if(arbol==NULL){
        return NULL;
    }else{
        if(arbol->izquierda){
            return  minimo(arbol->izquierda);
        }else{
            return arbol;
        }
    }
}

void reemplazar(Nodo*arbol,Nodo*nuevoNodo){
    if(arbol->padre){
        if(arbol->dato == arbol->padre->izquierda->dato){
            arbol->padre->izquierda=nuevoNodo;
        }else if(arbol->dato == arbol->padre->derecha->dato){
            arbol->padre->derecha=nuevoNodo;
        }
    }
    if(nuevoNodo){
        nuevoNodo->padre=arbol->padre;
    }
}

void destruirNodo(Nodo*nodo){
    nodo->izquierda=NULL;
    nodo->derecha=NULL;
    delete nodo;
}

void eliminarNodo(Nodo*nodoEliminar){
    if(nodoEliminar->izquierda && nodoEliminar->derecha){//si tiene dos hijos
        Nodo*menor = minimo(nodoEliminar->derecha);
        nodoEliminar->dato = menor->dato;
        eliminarNodo(menor);
    }else if(nodoEliminar->izquierda){//si tiene solo hijo izquierdo
        reemplazar(nodoEliminar,nodoEliminar->izquierda);
        destruirNodo(nodoEliminar);
    }else if(nodoEliminar->derecha){//si tiene solo hijo derecho
        reemplazar(nodoEliminar,nodoEliminar->derecha);
        destruirNodo(nodoEliminar);
    }else{//si no tiene hijos
        reemplazar(nodoEliminar,NULL);
        destruirNodo(nodoEliminar);
    }
}

void eliminar(Nodo*arbol, string DATO){
    if(arbol==NULL){
        return;
    }else{
        string valorRaiz = arbol->dato;
        if(strcmp(DATO.c_str(),valorRaiz.c_str())>0){
            eliminar(arbol->derecha,DATO);
        }else if(strcmp(DATO.c_str(),valorRaiz.c_str())<0){
            eliminar(arbol->izquierda,DATO);
        }else if(DATO==valorRaiz){
            eliminarNodo(arbol);
        }
    }
}

string escribirDatos(Nodo*arbol, int contador,string datos2){
    string contenido;
    if(arbol==NULL){
        datos2=""+datos2;
    }else{
        escribirDatos(arbol->derecha,contador+1,datos2);
        for (int i=0;i<contador;i++) {
            //cout<<"    ";
        }
        datos2=datos2+"nodo"+to_string(contador)+"[label =\"<C0>|"+arbol->dato+"|<C1>\"];";
        datos2=datos2+"nodo"+to_string(contador)+":C1->nodo"+to_string(contador-1);
        //cout<<arbol->dato<<endl;
        escribirDatos(arbol->izquierda,contador+1,datos2);
        datos2=datos2+"nodo"+to_string(contador-1)+":C0->nodo"+to_string(contador);
    }
       return datos2;
}

void escribir(string contenido){
    ofstream archivo;

    archivo.open("codigoImagen.dot",ios::out);

    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }else{
        archivo<<"digraph arbol {"<<endl;
        archivo<<"rankdir=TB;"<<endl;
        archivo<<"graph [splines=ortho, nodesep=0.5];"<<endl;
        archivo<<"node [shape = record, style=filled, fillcolor=seashell2,width=0.7,height=0.2];"<<endl;



        archivo<<contenido;

        archivo<<"}"<<endl;
        archivo.close();
        system("dot.exe -Tjpg codigoImagen.dot -o graficoArbol.jpg");
        system("graficoArbol.jpg");
    }
}


//prototipos
Nodo*crearNodo(string,Nodo*);
void incertarNodo(Nodo*&, string, Nodo*);
Nodo*arbol=NULL;
void mostrarArbol(Nodo*,int);
void eliminar(Nodo*,string);
void eliminarNodo(Nodo*);
void nodoMinimio(Nodo*);
void reemplazar(Nodo*,Nodo*);
void destruir(Nodo*);
void escribir(string);
string esribirDatos(Nodo*,int,string);

int main()
{
    int opcion,contador=0;
    string dato,datoArchivo,datos2;

    do{
        cout << "Tarea 3" << endl;
        cout << "1. Incertar Elemento" << endl;
        cout << "2. Eliminar Elemento" << endl;
        cout << "3. Mostrar Arbol" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin>>opcion;

        switch (opcion) {
            case 1: cout<<"Incertar nombre: ";
                    cin>>dato;
                    incertarNodo(arbol,dato,NULL);
            break;
            case 2: cout<<"Incertar Nombre a Eliminar: ";
                    cin>>dato;
                    eliminar(arbol,dato);
            break;
            case 3:
                    mostrarArbol(arbol,contador);
                    datoArchivo=escribirDatos(arbol,contador,datos2);
                    escribir(datoArchivo);
                    system("pause");
            break;
        }
         system("cls");
    }while(opcion != 4);

    return 0;
}
