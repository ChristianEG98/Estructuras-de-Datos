#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <map>
#include <unordered_set>
// Añade los #include que necesites
// Implementa los métodos pedidos dentro de la clase.
// No te olvides del coste de cada método.

//Costes:
//E = Estaciones en la linea
//L = Lineas a las que pertenece una estacion

using s_linea = string;
using s_estacion = string;
using i_posicion = int;

class Ferrovistan {
public:
	void nueva_linea(const string &nombre) { //O(1)
		if (lineas.count(nombre)) { //O(1)
			throw domain_error("Linea existente");
		}
		lineas.insert({ nombre, { } }); //O(1)
	}
	void nueva_estacion(const string &linea, const string &nombre, int posicion) { //O(log E + log L)
		if (!lineas.count(linea)) { //O(1)
			throw domain_error("Linea no existente");
		}
		if (lineas[linea].estaciones.count(nombre)) { //O(1)
			throw domain_error("Estacion duplicada en linea");
		}
		if (lineas[linea].estaciones_ordenadas.count(posicion)) { //O(log E)
			throw domain_error("Posicion ocupada");
		}
		lineas[linea].estaciones_ordenadas.insert({ posicion, nombre }); //O(log E)
		lineas[linea].estaciones.insert(nombre); //O(1)
		estaciones[nombre].insert({ linea, posicion }); //O(log L)
	}
	void eliminar_estacion(const string &estacion) { //O(L * log E)
		if (!estaciones.count(estacion)) { //O(1)
			throw domain_error("Estacion no existente");
		}
		for (auto it = estaciones.at(estacion).begin(); it != estaciones.at(estacion).end(); it++) { //O(L * log E)
			string lin = it->first;
			int pos = it->second;
			lineas.at(lin).estaciones.erase(estacion); //O(1)
			lineas.at(lin).estaciones_ordenadas.erase(pos); //O(log E)
		}
	}
	vector<string> lineas_de(const string &estacion) const { //O(L)
		if (!estaciones.count(estacion)) { //O(1)
			throw domain_error("Estacion no existente");
		}
		vector<string> result;
		auto it = estaciones.at(estacion).begin(); //O(1)
		while (it != estaciones.at(estacion).end()) { //O(L)
			result.push_back(it->first); //O(1)
			it++;
		}
		return result;
	}
	string proxima_estacion(const string &linea, const string &estacion) const { //O(log L + log E)
		if (!lineas.count(linea)) { //O(1)
			throw domain_error("Linea no existente");
		}
		if (!lineas.at(linea).estaciones.count(estacion)) { //O(1)
			throw domain_error("Estacion no existente");
		}
		int posicion = estaciones.at(estacion).at(linea); //O(log L)
		auto it = lineas.at(linea).estaciones_ordenadas.find(posicion); //O(log E)
		if (++it == lineas.at(linea).estaciones_ordenadas.end()) {
			throw domain_error("Fin de trayecto");
		}
		return it->second;
	}
private:
	struct InfoLinea {
		map<i_posicion, s_estacion> estaciones_ordenadas;
		unordered_set<s_estacion> estaciones;
	};

	unordered_map<s_linea, InfoLinea> lineas;
	unordered_map<s_estacion, map<s_linea, i_posicion>> estaciones;
};