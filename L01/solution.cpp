/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  Introduce aquí los nombres de los componentes del grupo:

  Componente 1: Christian
  Componente 2: 
  */

#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_ELEMS = 2000;


class Multiconjunto {
public:
    Multiconjunto(); //Coste constante
    void anyadir(int elem); //Coste lineal con respecto a num_elems
    bool pertenece(int elem); //Coste logaritmico con respecto a num_elems
    void eliminar(int elem); //Coste lineal con respecto a num_elems
private:
    struct Elem {
        int valor;
        int multiplicidad;
    };
    Elem elems[MAX_ELEMS];
    int num_elems;
    int busqueda_binaria(int ini, int fin, int num); //Coste logaritmico con respecto al tamaño de la busqueda fin - ini
};

Multiconjunto::Multiconjunto() :num_elems(0) {};

void Multiconjunto::anyadir(int elem) {
    int pos = busqueda_binaria(0, num_elems, elem);
    if (pos == num_elems) {
        elems[pos].valor = elem;
        elems[pos].multiplicidad = 1;
        num_elems++;
    }
    else if (elems[pos].valor == elem) {
        elems[pos].multiplicidad++;
    }
    else {
        for (int i = num_elems; i > pos; i--) {
            elems[i].valor = elems[i - 1].valor;
            elems[i].multiplicidad = elems[i - 1].multiplicidad;
        }
        num_elems++;
        elems[pos].valor = elem;
        elems[pos].multiplicidad = 1;
    }
}

int Multiconjunto::busqueda_binaria(int ini, int fin, int num) {
    if (ini == fin)
        return ini;
    else {
        int m = (fin + ini) / 2;
        if (elems[m].valor >= num) return busqueda_binaria(ini, m, num);
        else return busqueda_binaria(m + 1, fin, num);
    }
}

bool Multiconjunto::pertenece(int elem) {
    int pos = busqueda_binaria(0, num_elems, elem);
    return pos < num_elems && elems[pos].valor == elem;
}

void Multiconjunto::eliminar(int elem) {
    int pos = busqueda_binaria(0, num_elems, elem);
    if (pos != num_elems && elems[pos].valor == elem) {
        if (elems[pos].multiplicidad > 1) elems[pos].multiplicidad--;
        else {
            for (int i = pos; i < num_elems; i++) {
                elems[i].valor = elems[i + 1].valor;
                elems[i].multiplicidad = elems[i + 1].multiplicidad;
            }
            num_elems--;
        }
    }
}

bool tratar_caso() {
    int tam, num;
    std::cin >> tam;
    if (tam == 0) return false;
    Multiconjunto secuencia; //Multiconjunto de la secuencia secreta
    vector <int> secVector(tam); //vector con la secuencia secreta
    vector <int> intento(tam); //vector con el intento
    vector <char> solucion(tam); //vector con los caracteres de la solucion
    for (int i = 0; i < tam; i++) {
        std::cin >> num;
        secuencia.anyadir(num);
        secVector[i] = num;
    }
    //Guardamos la secuencia de intento y marcamos las repeticiones que estan en el lugar correcto
    for (int i = 0; i < tam; i++) {
        std::cin >> intento[i];
        if (intento[i] == secVector[i]) {
            solucion[i] = '#';
            secuencia.eliminar(intento[i]);
        } 
    }
    //Marcamos el resto de repeticiones y las que no aparecen
    for (int i = 0; i < tam; i++) {
        if (solucion[i] != '#') {
            if (secuencia.pertenece(intento[i])) {
                solucion[i] = 'O';
                secuencia.eliminar(intento[i]);
            }
            else solucion[i] = '.';
        }
    }
    
    for (int i = 0; i < tam; i++) std::cout << solucion[i];
    std::cout << "\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar en Windows si la consola se cierra inmediatamente
    // system("PAUSE");
#endif
    return 0;
}