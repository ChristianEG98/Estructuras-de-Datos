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
#include <queue>

using namespace std;

// Puedes copiar aquí algunas de las implementaciones de los TADs vistos esta semana:

// Pilas: https://github.com/manuelmontenegro/ED/blob/main/lineales/stack_linkedlist/stack_linkedlist.h
// Colas: https://github.com/manuelmontenegro/ED/blob/main/lineales/queue_linkedlist/queue_linkedlist.h
// Colas dobles: https://github.com/manuelmontenegro/ED/blob/main/lineales/deque/dequeue.h

// En caso de utilizar alguno de los TADs anteriores, ha de copiarse TAL CUAL, sin realizar ningún cambio
// en sus implementaciones. Para facilitar la corrección, coloca la implementación de estos TADs fuera
// de las etiquetas <answer> y </answer>. El profesor asumirá que tienen la misma implementación que la
// vista en teoría.

// Alternativamente, puedes utilizar las clases de la librería estándar de C++ (stack<T>, queue<T> y deque<T>).

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------

//Coste lineal con respecto a:
// N (numeros de horas adulto) si N > T y N > (M-N)
// M (numero de horas yema) si M > T y M > (M-N)
// T (duracion del experimento) T > N y T > (M-N)
bool tratar_caso() {
    queue<int> adultos, yemas;
    int horas_adulto, horas_yema, horas;
    cin >> horas_adulto;
    if (cin.eof()) return false;
    cin >> horas_yema >> horas;
	//Inicizalimos las dos colas
	for (int i = 0; i < horas_adulto - 1; i++) adultos.push(0);
	adultos.push(1);
	for (int i = 0; i < (horas_yema - horas_adulto); i++) yemas.push(0);

	while (horas > 0) {
		int fA = adultos.front();
		int fY = yemas.front();
		adultos.pop();
		yemas.pop();
		//Si solo hay yemas
		if (fY != 0 && fA == 0) {
			adultos.push(fY);
			yemas.push(0);
		}
		//Si hay yemas y adultos
		else if (fY != 0 && fA != 0) {
			adultos.push(fY + fA);
			yemas.push(fA);
		}
		//Si solo hay adultos
		else if (fY == 0 && fA != 0) {
			adultos.push(fA);
			yemas.push(fA);
		}
		//Si no hay ni yemas ni adultos
		else {
			adultos.push(0);
			yemas.push(0);
		}
		horas--;
	}

	int tamY = yemas.size();
	int tamA = adultos.size();
	int sum = 0;
	for (int i = 0; i < tamY; i++) {
		sum += yemas.front();
		yemas.pop();
	}
	for (int i = 0; i < tamA; i++) {
		sum += adultos.front();
		adultos.pop();
	}

	cout << sum << endl;

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

