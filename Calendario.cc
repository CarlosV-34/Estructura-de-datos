#include "Calendario.h"
/*** Calendario ***/
// Private
map<Fecha,Evento> Calendario::getMapa() const{
    return mapa;
}

void Calendario::actualizarFrecuenciaInsert(const Evento& e){
    // Actualizo frecuencias
    // Categorias
    if (frecuencia_cat.count(e.getCategoria())>0){
        frecuencia_cat[e.getCategoria()] += 1;
    }
    else frecuencia_cat[e.getCategoria()] = 1;
    // Dias
    if (frecuencia_dia.count(e.getFecha().getDia())>0){
        frecuencia_dia[e.getFecha().getDia()] += 1;
    }
    else frecuencia_dia[e.getFecha().getDia()] = 1;
    // Meses
    if (frecuencia_mes.count(e.getFecha().getMes())>0){
        frecuencia_mes[e.getFecha().getMes()] += 1;
    }
    else frecuencia_mes[e.getFecha().getMes()] = 1;
    // Anyos
    if (frecuencia_anyo.count(e.getFecha().getAnyo())>0){
        frecuencia_anyo[e.getFecha().getAnyo()] += 1;
    }
    else frecuencia_anyo[e.getFecha().getAnyo()] = 1; 
}
void Calendario::actualizarFrecuenciaDelete(const Evento& e){
    // Actualizo frecuencias
    // Categorias
    if (frecuencia_cat.count(e.getCategoria())>0 && frecuencia_cat[e.getCategoria()]>0){
        frecuencia_cat[e.getCategoria()] -= 1;
    }
    // Dias
    if (frecuencia_dia.count(e.getFecha().getDia())>0 && frecuencia_dia[e.getFecha().getDia()]>0){
        frecuencia_dia[e.getFecha().getDia()] -= 1;
    }
    // Meses
    if (frecuencia_mes.count(e.getFecha().getMes())>0 && frecuencia_mes[e.getFecha().getMes()]>0){
        frecuencia_mes[e.getFecha().getMes()] -= 1;
    }
    // Anyos
    if (frecuencia_anyo.count(e.getFecha().getAnyo())>0 && frecuencia_anyo[e.getFecha().getAnyo()]>0){
        frecuencia_anyo[e.getFecha().getAnyo()] -= 1;
    }
}

//Constructor por defecto: calendario sin ningún evento
Calendario::Calendario(){
}
//Constructor de copia
Calendario::Calendario(const Calendario& c){
    mapa = c.getMapa();
    inserciones = c.inserciones;
    borrados = c.borrados;
}
//Operador de asignación
Calendario& Calendario::operator=(const Calendario &c){
    if (mapa != c.getMapa()) {
        mapa = c.getMapa();
        inserciones = c.inserciones;
        borrados = c.borrados;
    }
    return *this;
}
//Destructor
Calendario::~Calendario(){
    map<Fecha,Evento> nuevo;
    mapa = nuevo;
}

//Añade un evento al calendario. Si ya existía un evento en esa fecha, 
//devuelve false y no hace nada. En caso contrario, devuelve true.
bool Calendario::insertarEvento(const Evento& e){
    if (comprobarEvento(e.getFecha())) return false;
    else{
        mapa[e.getFecha()] = e;
        inserciones.push(e);
        // Actualizo frecuencias
        actualizarFrecuenciaInsert(e);
        
        return true;
    }
}

//Elimina un evento del calendario. Si no había ningún evento asociado a esa fecha, 
//devuelve false y no hace nada. En caso contrario, devuelve true.
bool Calendario::eliminarEvento(const Fecha& f){
    if (!comprobarEvento(f)) return false;
    else {
        borrados.push(mapa.at(f));
        // Actualizar frecuencia
        actualizarFrecuenciaDelete(mapa.at(f));
        mapa.erase(f);
        return true;
    }
}

//Comprueba si hay algún evento asociado a la fecha dada
bool Calendario::comprobarEvento(const Fecha &f) const{
    if (mapa.count(f)==1) return true;
    else return false;
}


Evento Calendario::obtenerEvento(const Fecha& f) const{
    Evento e;
    if (comprobarEvento(f)){
        e = mapa.at(f);
    }
    return e;
}

//Devuelve una cadena con el contenido completo del calendario
string Calendario::aCadena(const vector<string>& categorias) const{
    string cadena;
    string aux = "";
    for (auto it = mapa.begin(); it != mapa.end(); ++it){
        if (aux==""){
            aux = it->second.aCadena(categorias);
        }
        else{
            cadena += "\n" + it->second.aCadena(categorias);
        }   
    }
    aux += cadena;
    return aux;
}

void Calendario::deshacerInsercion(){
    if (!inserciones.empty()){
        mapa.erase(inserciones.top().getFecha());
        // Actualizo frecuencias
        actualizarFrecuenciaDelete(inserciones.top());
        inserciones.pop();
    }
}

void Calendario::deshacerBorrado(){
   if (!borrados.empty()){
        mapa[borrados.top().getFecha()] = borrados.top();
        // Actualizo frecuencias
        actualizarFrecuenciaInsert(borrados.top());
        borrados.pop();
    }
}
//Devuelve una cadena con el contenido completo del calendario
string Calendario::aCadenaPorTitulo(const string& t,const vector<string>& categorias) const{
    string cadena = "";
    string aux = "";
    for (auto it = mapa.begin(); it != mapa.end(); ++it){
        if (aux=="" && it->second.getTitulo()==t){
            aux = it->second.aCadena(categorias);
        }
        else{
            if (it->second.getTitulo()==t){
                cadena += "\n" + it->second.aCadena(categorias);
            }
        }   
    }
    return cadena;
}

int Calendario::categoriaMasFrecuente() const{
    int result = -2;
    int cantidad = 0;
    for (auto it = frecuencia_cat.begin(); it != frecuencia_cat.end(); ++it){
        if (it->second>cantidad){
            result = it->first;
            cantidad = it->second;
        }
        else if (it->second==cantidad){
            if(it->first>result){
                result=it->first;
            }
        }
    }
    return result;
}

int Calendario::diaMasFrecuente() const{
    int result = -2;
    int cantidad = 0;
    for (auto it = frecuencia_dia.begin(); it != frecuencia_dia.end(); ++it){
        if (it->second>cantidad){
            result = it->first;
            cantidad = it->second;
        }
        else if (it->second==cantidad){
            if(it->first>result){
                result=it->first;
            }
        }
    }
    return result;
}

int Calendario::mesMasFrecuente() const{
    int result = -2;
    int cantidad = 0;
    for (auto it = frecuencia_mes.begin(); it != frecuencia_mes.end(); ++it){
        if (it->second>cantidad){
            result = it->first;
            cantidad = it->second;
        }
        else if (it->second==cantidad){
            if(it->first>result){
                result=it->first;
            }
        }
    }
    return result;
}

int Calendario::anyoMasFrecuente() const{
    int result = -2;
    int cantidad = 0;
    for (auto it = frecuencia_anyo.begin(); it != frecuencia_anyo.end(); ++it){
        if (it->second>cantidad){
            result = it->first;
            cantidad = it->second;
        }
        else if (it->second==cantidad){
            if(it->first>result){
                result=it->first;
            }
        }
    }
    return result;
}



