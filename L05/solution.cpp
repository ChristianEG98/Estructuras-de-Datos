/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas está
  * prohibida, pues no se tendrá en cuenta para la corrección.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  /*
    Introduce aquí los nombres de los componentes del grupo:

    Componente 1: Christian
    Componente 2:
  */
  //@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <cassert>
#include <list>
#include <string>


using namespace std;


enum class Categoria { Primero, Segundo, Postre };

struct Plato {
    Categoria categoria;
    string nombre;
};

// Sobrecarga del operador << para imprimir platos
ostream& operator<<(ostream& out, const Plato& plato) {
    switch (plato.categoria) {
    case Categoria::Primero:
        out << "1";
        break;
    case Categoria::Segundo:
        out << "2";
        break;
    case Categoria::Postre:
        out << "P";
        break;
    }
    out << " " << plato.nombre;
    return out;
}

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------

bool esPrimero(Plato &plato) {
    return plato.categoria == Categoria::Primero;
}

bool esSegundo(Plato& plato) {
    return plato.categoria == Categoria::Segundo;
}

bool esPostre(Plato& plato) {
    return plato.categoria == Categoria::Postre;
}

// Coste lineal con respecto al tamaño de la lista
void ordenar_menu(list<Plato>& platos) {
    if (!platos.empty()) {
        auto it = platos.begin();
        for (int i = 0; i < platos.size(); i++) {
            if (esPrimero(*it)) {
                platos.insert(platos.end(), *it);
                it = platos.erase(it);
            }
            else it++;
        }
        it = platos.begin();
        for (int i = 0; i < platos.size(); i++) {
            if (esSegundo(*it)) {
                platos.insert(platos.end(), *it);
                it = platos.erase(it);
            }
            else it++;
        }
        it = platos.begin();
        for (int i = 0; i < platos.size(); i++) {
            if (esPostre(*it)) {
                platos.insert(platos.end(), *it);
                it = platos.erase(it);
            }
            else it++;
        }
    }
}

Categoria convertirEnum(char c) {
    Categoria categoria;
    if (c == '1') categoria = Categoria::Primero;
    else if (c == '2') categoria = Categoria::Segundo;
    else categoria = Categoria::Postre;
    return categoria;
}

bool tratar_caso() {
    list<Plato> platos;
    Plato plato;
    char categoria;
    string nombre;
    int tam;
    cin >> tam;
    if (tam == 0) return false;
    for (int i = 0; i < tam; i++) {
        cin >> categoria;
        getline(cin, nombre);
        plato.nombre = nombre;
        plato.categoria = convertirEnum(categoria);
        platos.push_back(plato);
    }
    ordenar_menu(platos);
    int t = platos.size();
    for (int i = 0; i < t; i++) {
        cout << platos.front() << endl;
        platos.pop_front();
    }
    cout << "---" << endl;
    return true;
}


//---------------------------------------------------------------
// No modificar por debajo de esta línea
// --------------------------------------------------------------
//@ </answer>


int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}

