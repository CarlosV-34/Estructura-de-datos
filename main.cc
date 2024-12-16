#include "Calendario.h"
#include "Evento.h"
#include "Fecha.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

int main() {

    // 1. Leer las categorías
    vector<string> categorias;
    string linea;

    // Leer categorías hasta encontrar [FIN_CATEGORIAS]
    while (getline(cin, linea) && linea != "[FIN_CATEGORIAS]") {
        categorias.push_back(linea);
    }
    
    // Crear el objeto Calendario
    Calendario calendario;

    // 2. Leer y ejecutar operaciones hasta encontrar [FIN]
    while (getline(cin, linea) && linea != "[FIN]") {
        stringstream ss(linea);
        string metodo;
        ss >> metodo;  // Leer el nombre del método

        if (metodo == "insertarEvento") {
            // Leer los parámetros del evento
            int dia, mes, anyo, categoria;
            string titulo, descripcion;
            
            // Leer los parámetros básicos (fecha y categoría)
            ss >> dia >> mes >> anyo;
            
            // Leer el título, hasta el primer punto y coma o la categoría
            ss >> titulo;
            for(char& c : titulo){
                if(c == '_'){
                    c = ' ';
                }
            }
            // Leer descripcion
            ss >> descripcion;
            for(char& c : descripcion){
                if(c == '_'){
                    c = ' ';
                }
            }
            // Leer la categoría
            ss >> categoria;  
            
            //cout << categoria << " ";
            // Crear el objeto Fecha y Evento
            Fecha fecha(dia, mes, anyo);
            Evento evento(fecha, titulo, descripcion, categoria);

            // Intentar insertar el evento en el calendario
            if (calendario.insertarEvento(evento)) {
                cout << 1 << endl;
            } else {
                cout << 0 << endl;
            }

        } else if (metodo == "eliminarEvento") {
            // Leer la fecha para eliminar el evento
            int dia, mes, anyo;
            ss >> dia >> mes >> anyo;
            Fecha fecha(dia, mes, anyo);
            if(calendario.eliminarEvento(fecha)){
                cout << 1 << endl;
            } else {
                cout << 0 << endl;
            }

        } else if (metodo == "comprobarEvento") {
            // Leer la fecha para comprobar el evento
            int dia, mes, anyo;
            ss >> dia >> mes >> anyo;
            Fecha fecha(dia, mes, anyo);
            if(calendario.comprobarEvento(fecha)){
                cout << 1 << endl;
            } else {
                cout << 0 << endl;
            }

        } else if (metodo == "obtenerEvento") {
            // Leer la fecha para obtenerEvento 
            int dia, mes, anyo;
            ss >> dia >> mes >> anyo;
            Fecha fecha(dia, mes, anyo);
            cout << calendario.obtenerEvento(fecha).aCadena(categorias) << endl;

        } else if (metodo == "categoriaMasFrecuente") {
            // Ejecutar el método categoriaMasFrecuente
            int categoria = calendario.categoriaMasFrecuente();
            cout << categoria << endl;


        } else if (metodo == "diaMasFrecuente") {
            // Ejecutar el método diaMasFrecuente
            int dia = calendario.diaMasFrecuente();
            cout << dia << endl;


        } else if (metodo == "mesMasFrecuente") {
            // Ejecutar el método mesMasFrecuente
            int mes = calendario.mesMasFrecuente();
            cout << mes << endl;


        } else if (metodo == "anyoMasFrecuente") {
            // Ejecutar el método anyoMasFrecuente
            int anyo = calendario.anyoMasFrecuente();
            cout << anyo << endl;


        } else if (metodo == "aCadena") {
            // Imprimir el calendario completo
            cout << calendario.aCadena(categorias);


        } else if (metodo == "aCadenaPorTitulo") {
            // Leer el título y ejecutar aCadenaPorTitulo
            string titulo;
            getline(ss, titulo);
            //titulo = titulo.substr(1);  // Eliminar el espacio después del nombre del método
            cout << calendario.aCadenaPorTitulo(titulo, categorias) << endl;

        } else if (metodo == "deshacerInsercion") {
            // Deshacer la última inserción
            calendario.deshacerInsercion();

        } else if (metodo == "deshacerBorrado") {
            // Deshacer el último borrado
            calendario.deshacerBorrado();
        }
    }
    
    return 0;
}


