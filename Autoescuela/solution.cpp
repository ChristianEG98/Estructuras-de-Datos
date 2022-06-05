#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class Autoescuela{
public:
    void alta(const string& alumno, const string& profesor) {
        if (alumnos.count(alumno)) {
            string antiguo_profesor = alumnos[alumno].profesor;
            profesores[profesor].erase(alumno);
        }
        alumnos[alumno].profesor = profesor;
        profesores[profesor].insert(alumno);
    }
    bool es_alumno(const string& alumno, const string& profesor) {
        return alumnos.count(alumno) && alumnos[alumno].profesor == profesor;
    }
    int puntuacion(const string& alumno) {
        return buscar_alumno(alumno).puntuacion;
    }
    void actualizar(const string& alumno, int puntuacion) {
        buscar_alumno(alumno).puntuacion += puntuacion;
    }
    vector<string> examen(const string& profesor, int puntuacion) {
        vector<string> result;
        if (profesores.count(profesor)) {
            for (const string& alumno : profesores[profesor]) {
                if (alumnos[alumno].puntuacion >= puntuacion) {
                    result.push_back(alumno);
               }
            }
        }
        return result;
    }
    void aprobar(const string& alumno) {
        InfoAlumno al = buscar_alumno(alumno);
        profesores[al.profesor].erase(alumno);
        alumnos.erase(alumno);
    }
private:
    struct InfoAlumno {
        int puntuacion;
        string profesor;

        InfoAlumno() : puntuacion(0), profesor("") { }
    };
    unordered_map<string, InfoAlumno> alumnos;
    unordered_map<string, set<string>> profesores;

    const InfoAlumno buscar_alumno(const string& alumno) const {
        auto it = alumnos.find(alumno);
        if (it == alumnos.end()) throw domain_error("El alumno " + alumno + " no esta matriculado");
        else return it->second;
    }
    InfoAlumno& buscar_alumno(const string& alumno) {
        auto it = alumnos.find(alumno);
        if (it == alumnos.end()) throw domain_error("El alumno " + alumno + " no esta matriculado");
        else return it->second;
    }
};

bool tratar_caso() {
    Autoescuela autoescuela;
    string comando, alumno, profesor;
    int puntuacion;
    cin >> comando;
    if (!cin) return false;
    while (comando != "FIN") {
        try {
            if (comando == "alta") {
                cin >> alumno >> profesor;
                autoescuela.alta(alumno, profesor);
            }
            else if (comando == "es_alumno") {
                cin >> alumno >> profesor;
                if (autoescuela.es_alumno(alumno, profesor)) cout << alumno + " es alumno de " + profesor << endl;
                else cout << alumno + " no es alumno de " + profesor << endl;
            }
            else if (comando == "puntuacion") {
                cin >> alumno;
                int p = autoescuela.puntuacion(alumno);
                cout << "Puntuacion de " + alumno + ": ";
                cout << p << endl;
            }
            else if (comando == "actualizar") {
                cin >> alumno >> puntuacion;
                autoescuela.actualizar(alumno, puntuacion);
            }
            else if (comando == "examen") {
                cin >> profesor >> puntuacion;
                vector<string> alumnosExamen = autoescuela.examen(profesor, puntuacion);
                cout << "Alumnos de " + profesor + " a examen: " << endl;
                for (int i = 0; i < alumnosExamen.size(); i++) {
                    cout << alumnosExamen[i] << endl;
                }
            }
            else if (comando == "aprobar") {
                cin >> alumno;
                autoescuela.aprobar(alumno);
            }
        }
        catch (domain_error &exception) {
            cout << "ERROR" << endl;
        }
        cin >> comando;
    }
    cout << "---" << endl;
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