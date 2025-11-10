/* 
Harold  Arian Corimanya Arias - 20242164J

Desarrolla un sistema de gestión académica para la UNI que permita administrar la información de estudiantes, cursos y sus calificaciones. 
El sistema debe utilizar estructuras en C++ para organizar los datos de manera eficiente. Su implementación debe

- Aplicar conceptos de estructuras en C++
- Implementar arreglos de estructuras
- Usar anidamiento de estructuras
- Trabajar con punteros a estructuras
- Pasar estructuras como parámetros de funciones
- Implementar funciones miembro en estructuras

*/
#include <iostream>
#include <string>
#include <iomanip> // para organizar las tablas
using namespace std;

struct Notas{
    float EP;   // Examen Parcial (30%)
    float EF;   // Examen Final (50%)
    float PP;   // Promedio de Prácticas (20%)

    float calcularPromedio() {
        return EP * 0.3 + EF * 0.5 + PP * 0.2;
    }

    string obtenerEstado() {
        float prom = calcularPromedio();
        if (prom >= 10.5) return "Aprobado";
        else return "Desaprobado";
    }
};

struct Curso{
    string codigo;
    string nombre;
    int creditos;
    string profesor;
    Notas notas;

    void mostrarInformacion() {
        cout << left << setw(8) << codigo << " "
             << setw(35) << nombre << " "
             << right << setw(8) << creditos << "   "
             << setw(3) << (int)notas.EP << "  "
             << setw(3) << (int)notas.EF << "  "
             << setw(3) << (int)notas.PP << "   "
             << fixed << setprecision(2)
             << setw(8) << notas.calcularPromedio() << "   "
             << left << setw(10) << notas.obtenerEstado() << endl;
    }
};

struct Estudiante{
    string codigo;
    string nombre;
    string carrera;
    int ciclo;
    Curso cursos[6];     // Máximo 6 cursos por estudiante
    int cantidadCursos;

    void mostrarDatos() {
        cout << "Estudiante: " << nombre << " (" << codigo << ")" << endl;
        cout << "Carrera: " << carrera << " - Ciclo: " << ciclo << endl;
    }
};

void registrarEstudiante(Estudiante estudiantes[], int &cantidad) {
    cout << "\n=== REGISTRAR ESTUDIANTE ===\n";
    Estudiante e;
    cout << "Código: ";
    getline(cin, e.codigo);
    cout << "Nombre: "; 
    getline(cin, e.nombre);
    cout << "Carrera: "; 
    getline(cin, e.carrera);
    cout << "Ciclo: "; 
    cin >> e.ciclo; 
    cin.ignore(); //limpieza de buffer
    e.cantidadCursos = 0;
    estudiantes[cantidad++] = e;
}

Estudiante* buscarEstudiante(Estudiante estudiantes[], int cantidad, string codigo) {
    for (int i = 0; i < cantidad; i++)
        if (estudiantes[i].codigo == codigo)
            return &estudiantes[i];
    return nullptr;
}

void matricularCurso(Estudiante &e) {
    cout << "\n=== MATRICULAR CURSO ===\n";
    Curso c;
    cout << "Código del curso: "; 
    getline(cin, c.codigo);
    cout << "Nombre: "; 
    getline(cin, c.nombre);
    cout << "Créditos: "; 
    cin >> c.creditos; 
    cin.ignore(); // limpieza de buffer 
    cout << "Profesor: "; 
    getline(cin, c.profesor);
    e.cursos[e.cantidadCursos++] = c;
}

void ingresarNotas(Estudiante &e) {
    cout << "\n=== INGRESAR NOTAS ===\n";
    cout << "Código del curso: ";
    string codigo; 
    getline(cin, codigo);

    for (int i = 0; i < e.cantidadCursos; i++) {
        if (e.cursos[i].codigo == codigo) {
            cout << "Examen Parcial: "; 
            cin >> e.cursos[i].notas.EP;
            cout << "Examen Final: "; 
            cin >> e.cursos[i].notas.EF;
            cout << "Promedio de Prácticas: "; 
            cin >> e.cursos[i].notas.PP;
            cin.ignore(); //limpieza de buffer
            break;
        }
    }
}

void mostrarCursosEstudiante(Estudiante e) {
    cout << "\n=== CURSOS DEL ESTUDIANTE ===\n";
    e.mostrarDatos();

    cout << left << setw(8) << "Código" << " "
         << setw(35) << "Curso" << " "
         << right << setw(8) << "Créditos" << "   "
         << setw(3) << "EP" << "  "
         << setw(3) << "EF" << "  "
         << setw(3) << "PP" << "   "
         << setw(8) << "Promedio" << "   "
         << left << setw(10) << "Estado" << endl;

    for (int i = 0; i < e.cantidadCursos; i++)
        e.cursos[i].mostrarInformacion();
}

float calcularPromedioPonderado(Estudiante e) {
    float suma = 0;
    int totalCred = 0;
    for (int i = 0; i < e.cantidadCursos; i++) {
        suma += e.cursos[i].notas.calcularPromedio() * e.cursos[i].creditos;
        totalCred += e.cursos[i].creditos;
    }
    return suma / totalCred;
}

int calcularTotalCreditos(Estudiante e) {
    int total = 0;
    for (int i = 0; i < e.cantidadCursos; i++)
        total += e.cursos[i].creditos;
    return total;
}

void generarBoleta(Estudiante e) {
    cout << "\n=== BOLETA DE NOTAS ===\n";
    e.mostrarDatos();

    cout << left << setw(8) << "Código" << " "
         << setw(35) << "Curso" << " "
         << right << setw(8) << "Créditos" << "   "
         << setw(3) << "EP" << "  "
         << setw(3) << "EF" << "  "
         << setw(3) << "PP" << "   "
         << setw(8) << "Promedio" << "   "
         << left << setw(10) << "Estado" <<endl;

    for (int i = 0; i < e.cantidadCursos; i++)
        e.cursos[i].mostrarInformacion();

    cout << "\nPromedio Ponderado: " << fixed << setprecision(2)
         << calcularPromedioPonderado(e) <<endl;
    cout << "Total Créditos: " << calcularTotalCreditos(e) <<endl;
}

void mostrarMejorPromedio(Estudiante estudiantes[], int cantidad) {
    int indice = 0;
    float mejorProm = calcularPromedioPonderado(estudiantes[0]); // Resulta útil tomar el primer estudiante
    for (int i = 1; i < cantidad; i++) {
        float Prom = calcularPromedioPonderado(estudiantes[i]);
        if (Prom > mejorProm) {
            mejorProm = Prom;
            indice = i;
        }
    }
    cout << "\n=== MEJOR PROMEDIO ===\n";
    cout << estudiantes[indice].nombre << " (" << estudiantes[indice].codigo << ") - "<< fixed << setprecision(2) << mejorProm <<endl;
}

void estudiantesAprobadosCurso(Estudiante estudiantes[], int cantidad, string codigoCurso) {
    cout << "\n=== ESTUDIANTES APROBADOS EN " << codigoCurso << " ===\n";
    for (int i = 0; i < cantidad; i++) {
        for (int j = 0; j < estudiantes[i].cantidadCursos; j++) {
            if (estudiantes[i].cursos[j].codigo == codigoCurso && estudiantes[i].cursos[j].notas.obtenerEstado() == "Aprobado") {
                cout << estudiantes[i].codigo << " - " << estudiantes[i].nombre
                     << " | Promedio: " << fixed << setprecision(2)
                     << estudiantes[i].cursos[j].notas.calcularPromedio() <<endl;
            }
        }
    }
}

void reporteGeneral(Estudiante estudiantes[], int cantidad) {
    cout << "\n=== REPORTE GENERAL ===\n";
    for (int i = 0; i < cantidad; i++) {
        estudiantes[i].mostrarDatos();

        cout << left << setw(8) << "Código" << " "
             << setw(35) << "Curso" << " "
             << right << setw(8) << "Créditos" << "   "
             << setw(3) << "EP" << "  "
             << setw(3) << "EF" << "  "
             << setw(3) << "PP" << "   "
             << setw(8) << "Promedio" << "   "
             << left << setw(10) << "Estado" << endl;

        for (int j = 0; j < estudiantes[i].cantidadCursos; j++)
            estudiantes[i].cursos[j].mostrarInformacion();

        cout << "Promedio: " << fixed << setprecision(2)
             << calcularPromedioPonderado(estudiantes[i])
             << " | Créditos: " << calcularTotalCreditos(estudiantes[i]) << "\n\n";
    }
}

int main() {
    const int MAX = 100;
    Estudiante estudiantes[MAX];
    int cantidad = 0;
    int opc;

    do {
        cout << "\n=== SISTEMA DE GESTIÓN ACADÉMICA UNI ===\n";
        cout << "1.Registrar estudiante" << endl;
        cout << "2.Matricular curso a estudiante" << endl;
        cout << "3.Ingresar notas de curso" << endl;
        cout << "4.Mostrar información de estudiante" << endl;
        cout << "5.Generar boleta de notas" << endl;
        cout << "6.Mostrar mejor promedio" << endl;
        cout << "7.Estudiantes aprobados por curso" << endl;
        cout << "8.Reporte general" << endl;
        cout << "9.Salir" << endl;
        cout << "Elija una opcion: ";
        cin >> opc;
        cin.ignore(); //limpieza de buffer

        switch (opc) {
            case 1: {
                registrarEstudiante(estudiantes, cantidad); 
                break;
            }

            case 2: {
                string cod; 
                cout << "Código del estudiante: "; 
                getline(cin, cod);
                Estudiante* e = buscarEstudiante(estudiantes, cantidad, cod);
                if (e)  // e != nullptr
                matricularCurso(*e);
                break;
            }

            case 3: {
                string cod; 
                cout << "Código del estudiante: "; 
                getline(cin, cod);
                Estudiante* e = buscarEstudiante(estudiantes, cantidad, cod);
                if (e)  // e != nullptr
                ingresarNotas(*e);
                break;
            }

            case 4: {
                string cod; 
                cout << "Código del estudiante: "; 
                getline(cin, cod);
                Estudiante* e = buscarEstudiante(estudiantes, cantidad, cod);
                if (e) // e != nullptr
                mostrarCursosEstudiante(*e);
                break;
            }

            case 5: {
                string cod; 
                cout << "Código del estudiante: "; 
                getline(cin, cod);
                Estudiante* e = buscarEstudiante(estudiantes, cantidad, cod);
                if (e) // e != nullptr
                generarBoleta(*e);
                break;
            }

            case 6: {
                mostrarMejorPromedio(estudiantes, cantidad); 
                break;
            }

            case 7: {
                string cod;
                cout << "Código del curso: "; 
                getline(cin, cod);
                estudiantesAprobadosCurso(estudiantes, cantidad, cod);
                break;
            }
            case 8: 
                reporteGeneral(estudiantes, cantidad); 
                break;

            case 9:
                break;

            default: {
                cout << "Error."<<endl; 
                break;
            }
        }
    } while (opc != 9);

    return 0;
}
