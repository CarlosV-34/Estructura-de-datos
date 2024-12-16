#include "Evento.h"

Evento::Evento(){
    Fecha fecha;
    titulo = "sin título";
    descripcion = "";
    categoria = -1;

}

Evento::Evento(const Fecha& f, const string& t,const string&d, int cat): fecha(f){
    fecha = f;

    if(t.length() == 0){
        titulo = "sin título";
    } else{
        titulo = t;
    }
    
    descripcion = d;

    if(cat < -1){
        categoria = -1;
    } else{
        categoria = cat;
    }
}

Evento::Evento(const Evento& e){
    fecha = e.getFecha();
    titulo = e.getTitulo();
    descripcion = e.getDescripcion();
    categoria = e.getCategoria();

}

Evento& Evento::operator=(const Evento &e){
    if(this != &e ){
        fecha = e.getFecha();
        titulo = e.getTitulo();
        descripcion = e.getDescripcion();
        categoria = e.getCategoria();
        return *this;
    }else{
        return *this;
    }
}

Evento::~Evento(){
    fecha.setDia(1);
    fecha.setMes(1);
    fecha.setAnyo(1900);
    titulo = "sin título";
    descripcion = "";
    categoria = -1;
}

//Operador de comparación
bool Evento::operator==(const Evento &e) const{
    if(fecha == e.getFecha() && titulo == e.getTitulo() 
       && descripcion == e.getDescripcion() && categoria == e.getCategoria()){ 
        return true;
    } else{
        return false;
    }
}

//Operador de comparación
bool Evento::operator!=(const Evento &e) const{
    if(*this == e){
        return false; 
    } else {
        return true;
    }
}

//Devuelve (una copia de) la fecha
Fecha Evento::getFecha() const{
    Fecha f2(fecha.getDia(), fecha.getMes(), fecha.getAnyo());
    return f2;
}
//Devuelve (una copia de) la descripción
string Evento::getTitulo() const{
    string titulo2 = titulo;
    return titulo2;
}
//Devuelve (una copia de) la descripción
string Evento::getDescripcion() const{
    string descripcion2 = descripcion;
    return descripcion2;
}
int Evento::getCategoria() const{
    int categoria2 = categoria;
    return categoria2;
}

//Modifica la fecha
void Evento::setFecha(const Fecha& f){
    fecha = f;
}
//Modifica la descripción
void Evento::setTitulo(const string &t){
    if(t.length() == 0){
        titulo = "sin título";
    } else {
        titulo = t;
    }
}

void Evento::setDescripcion(const string & d){
    descripcion = d;
}

void Evento::setCategoria(int cat){
    if(cat < -1){
        categoria = -1;
    } else {
        categoria = cat;
    }
}

//Convierte en cadena
string Evento::aCadena(const vector<string>& categorias) const{
    // Cadena resultante donde almacenaremos toda la información del calendario
    string resultado;

    resultado += fecha.aCadena(true,true);
    resultado += ':';
    resultado += titulo;
    resultado += '[';
    if(categoria == -1){
        resultado += "";
    } else{
        resultado += categorias[categoria];
    }
    resultado += ']';
    resultado += ':';
    resultado += descripcion;

    return resultado;
}


