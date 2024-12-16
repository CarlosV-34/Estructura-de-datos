#ifndef EVENTO_H
#define EVENTO_H

#include "Fecha.h"
#include<string>
#include<vector>
using namespace std;

class Evento{
private:
Fecha fecha;
string titulo;
string descripcion;
int categoria;

public:
Evento();
//Constructor sobrecargado: 
Evento(const Fecha&, const string&,const string&, int);
//Constructor de copia
Evento(const Evento&);
//Operador de asignación
Evento& operator=(const Evento &);
//Destructor: pone la fecha a 1/1/1900 y la descripción a "sin descripción"
~Evento();
//Operador de comparación
bool operator==(const Evento &) const;
//Operador de comparación
bool operator!=(const Evento &) const;
//Devuelve (una copia de) la fecha
Fecha getFecha() const;
//Devuelve (una copia de) la descripción
string getTitulo() const;
//Devuelve (una copia de) la descripción
string getDescripcion() const;
//Devuelve la categoría
int getCategoria() const;
//Modifica la fecha
void setFecha(const Fecha& );
//Modifica la descripción
void setTitulo(const string &);
//Modifica la descripción
void setDescripcion(const string &);
//Modifica la descripción
void setCategoria(int);
//Convierte en cadena
string aCadena(const vector<string>&) const;

};
#endif
