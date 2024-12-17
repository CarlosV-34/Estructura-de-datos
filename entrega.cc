#ifndef FECHA_H
#define FECHA_H

#include <string>

using namespace std;

class Fecha{
   private:
   int dia;
   int mes;
   int anyo;
   
   //Puede ser útil: eliminar si no se han implementado estos métodos auxiliares
   bool esFechaCorrecta(int, int, int) const;
   bool esBisiesto(int) const ;
   int calculaDiasMes(int, int) const;
   int obtenerDiaSemana() const;


   public:
   
   //Constructor por defecto: inicializa la fecha a 1/1/1900
   Fecha();
   
   //Constructor sobrecargado: inicializa la fecha según los parámetros
   Fecha(int dia,int mes,int anyo);
   
   //Constructor de copia
   Fecha(const Fecha &);
   
   //Destructor: pone la fecha a 1/1/1900
   ~Fecha();

   //Operador de asignación
   Fecha& operator=(const Fecha &);
   
   //Operador de comparación
   bool operator==(const Fecha &) const;
   
   //Operador de comparación
   bool operator!=(const Fecha &) const;
   
   //Operador de comparación
   bool operator<(const Fecha &) const;
   
   //Operador de comparación
   bool operator>(const Fecha &) const;
   
   
   //Devuelve el día
   int getDia() const;
   
   //Devuelve el mes
   int getMes() const;
   
   //Devuelve el año
   int getAnyo() const;
   
   //Modifica el día: devuelve false si la fecha resultante es incorrecta
   bool setDia(int);
   
   //Modifica el mes: devuelve false si la fecha resultante es incorrecta
   bool setMes(int);

  //Modifica el anyo: devuelve false si la fecha resultante es incorrecta
   bool setAnyo(int);

  //Incrementa la fecha en el número de días pasado como parámetro.
  //Si el parámetro es negativo, la decrementa
  bool incrementaDias(int );
  
  //Incrementa la fecha en el número de meses pasado como parámetro.
  //Si el parámetro es negativo, la decrementa
  bool incrementaMeses(int );
 
  //Incrementa la fecha en el número de años pasado como parámetro.
  //Si el parámetro es negativo, la decrementa
  bool incrementaAnyos(int );
  
  //Devuelve una representación como cadena de la fecha
  string aCadena(bool larga, bool conDia) const;
   
};


#endif

#ifndef EVENTO_H
#define EVENTO_H

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

#ifndef CALENDARIO_H
#define CALENDARIO_H

#include<string>
#include<map>
#include<unordered_map>
#include<stack>
using namespace std;

class Calendario{
private:
map<Fecha,Evento> mapa;
stack<Evento> inserciones;
stack<Evento> borrados;
unordered_map<int, int> frecuencia_cat;
unordered_map<int, int> frecuencia_dia;
unordered_map<int, int> frecuencia_mes;
unordered_map<int, int> frecuencia_anyo;
map<Fecha,Evento> getMapa() const;
void actualizarFrecuenciaInsert(const Evento&);
void actualizarFrecuenciaDelete(const Evento&);

public:
//Constructor por defecto: calendario sin ningún evento
Calendario();
//Constructor de copia
Calendario(const Calendario&);
//Operador de asignación
Calendario& operator=(const Calendario &);
//Destructor
~Calendario();
//Añade un evento al calendario. Si ya existía un evento en esa fecha, 
//devuelve false y no hace nada. En caso contrario, devuelve true.
bool insertarEvento(const Evento&);
//Elimina un evento del calendario. Si no había ningún evento asociado a esa fecha, 
//devuelve false y no hace nada. En caso contrario, devuelve true.
bool eliminarEvento(const Fecha&);
//Comprueba si hay algún evento asociado a la fecha dada
bool comprobarEvento(const Fecha&) const;
//Obtiene la descripción asociada al evento. Si no hay ningún evento asociado a la fecha
Evento obtenerEvento(const Fecha&) const;
//Devuelve una cadena con el contenido completo del calendario
string aCadena(const vector<string>&) const;
//Deshace la última inserción exitosa
void deshacerInsercion();
//Deshace el último borrado exitoso
void deshacerBorrado();
//Devuelve una cadena con el contenido completo del calendario
string aCadenaPorTitulo(const string&, const vector<string>&) const;
//categoría, día, mes y año más frecuente
int categoriaMasFrecuente() const;
int diaMasFrecuente() const;
int mesMasFrecuente() const;
int anyoMasFrecuente() const;
};

#endif



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
            cout << calendario.aCadena(categorias) << endl;


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



#include<string>

#include <iostream>
#include <cstdlib>

using namespace std;


//Método auxiliares: eliminar si no se han implementado
bool Fecha::esFechaCorrecta(int dia,int mes,int anyo) const{}
bool Fecha::esBisiesto(int a) const{
    if(a % 4 == 0 && (a % 100 != 0 || a % 400 == 0)){
        return true;
    }
    return false;
}

int Fecha::calculaDiasMes(int m, int a) const{
    if(m == 0){
        m = 12;
    }
    if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12){
        return 31;
    } else if(m == 4 || m == 6 || m == 9 || m == 11){
        return 30;
    } else if(esBisiesto(a) && m == 2){
        return 29;
    } else{
        return 28;
    }

}

int Fecha::obtenerDiaSemana() const{
    int totalDias = 0;

    for(int i = 1; i < anyo; i++){
        if(esBisiesto(i)){
            totalDias += 366;
        }else{
            totalDias += 365;
        }
    }

    for (int i = 1; i < mes; i++){
        totalDias += calculaDiasMes(i, anyo);
    }

    totalDias += dia;
    totalDias -= 1;

    return (totalDias%7);
}


Fecha::Fecha(){
    dia = 1;
    mes = 1;
    anyo = 1900;
}

Fecha::Fecha(int d,int m,int a){
    if(d > 0 && d <= calculaDiasMes(m,a) && m > 0 && m < 13 && a >= 1900){
        dia = d;
        mes = m;
        anyo = a;
    } else{
        dia = 1;
        mes = 1;
        anyo = 1900;
    }
}

Fecha::Fecha(const Fecha &f){
    dia = f.dia;
    mes = f.mes;
    anyo = f.anyo;
}

Fecha::~Fecha(){
    dia = 1;
    mes = 1;
    anyo = 1900;
}

Fecha& Fecha::operator=(const Fecha &f){
    if(this != &f ){
        (*this).~Fecha();
        dia = f.dia;
        mes = f.mes;
        anyo = f.anyo;
    }
    return *this;
}

int Fecha::getDia() const{
    return dia;
}

int Fecha::getMes() const{
    return mes;
}

int Fecha::getAnyo() const{
    return anyo;
}

bool Fecha::setDia(int d){
    if(d > 0 && d <= calculaDiasMes(mes, anyo)){
        dia = d;
        return true;
    } else return false;
}

bool Fecha::setMes(int m){
    if(m > 0 && m <= 12){
        mes = m;
        return true;
    } else return false;
}

bool Fecha::setAnyo(int a){
    if(a < 1900 || (dia == 29 && !esBisiesto(a))){
        return false;
    } else{
        anyo = a;
        return true;
    }
}

bool Fecha::operator==(const Fecha &f) const{
    if(f.getDia() == dia && f.getMes() == mes && f.getAnyo() == anyo){
        return true;
    }else return false;
}

bool Fecha::operator!=(const Fecha &f) const{
    if(f.getDia() == dia && f.getMes() == mes && f.anyo){
        return false;
    }else return true;
}

bool Fecha::operator<(const Fecha &f) const{
    if(anyo < f.anyo){
        return true;
    } else if(anyo > f.anyo){
        return false;
    } else{
        if(mes < f.mes){
            return true;
        } else if(mes > f.mes){
            return false;
        } else{
            if(dia < f.dia){
                return true;
            } else if(dia > f.dia){
                return false;
            } else{
                return false;
            }
        }
    }
}

bool Fecha::operator>(const Fecha &f) const{
    if(anyo > f.anyo){
        return true;
    } else if(anyo < f.anyo){
        return false;
    } else{
        if(mes > f.mes){
            return true;
        } else if(mes < f.mes){
            return false;
        } else{
            if(dia > f.dia){
                return true;
            } else if(dia < f.dia){
                return false;
            } else{
                return false;
            }
        }
    }
}


bool Fecha::incrementaDias(int inc){
    int dia2 = dia;
    int mes2 = mes;
    int anyo2 = anyo;

    while (inc != 0){
        if(inc > 0){
            if(esBisiesto(anyo) && inc >= 365 && mes > 2){
                anyo++;
                inc -= 365;
                continue;
            } else if(!(esBisiesto(anyo)) && !(esBisiesto(anyo + 1)) && inc >= 365){
                anyo++;
                inc -= 365;
                continue;
            } else if(esBisiesto(anyo) && inc >= 366 && mes <= 2){
                anyo++;
                inc -= 366;
                continue;
            } else if(!(esBisiesto(anyo)) && esBisiesto(anyo + 1) && inc >= 366 && mes > 2){
                anyo++;
                inc -= 366;
                continue;
            } else if(!(esBisiesto(anyo)) && esBisiesto(anyo + 1) && inc >= 365 && mes <= 2){
                anyo++;
                inc -= 365;
                continue;
            } else if(inc >= calculaDiasMes(mes, anyo)){
                inc -= calculaDiasMes(mes, anyo);
                mes++;
                if(mes == 13){
                    mes = 1;
                    anyo++;
                }
                continue;

            } else if(inc > (calculaDiasMes(mes, anyo) - dia)){
                inc -= (calculaDiasMes(mes, anyo) - dia);
                mes++;
                if(mes == 13){
                    mes = 1;
                    anyo++;
                }
                dia = inc;
                inc = 0;

            }else if(inc <= (calculaDiasMes(mes, anyo) - dia)){
                dia += inc;
                inc = 0;
            }

        }
        if (inc < 0){
            int diasRestar = abs(inc);
            while(diasRestar > 0){

                if(dia > diasRestar){
                    dia -= diasRestar;
                    diasRestar = 0;
                } else {
                    diasRestar -= dia;
                    mes--;

                    if(mes == 0){
                        mes = 12;
                        anyo--;
                    }

                    dia = calculaDiasMes(mes, anyo);
                }

            }
            if(anyo < 1900){
                dia = dia2;
                mes = mes2;
                anyo = anyo2;
                return false;
            }
            inc = 0;
        }
    }
    return true;
}

bool Fecha::incrementaMeses(int inc){
    int dia2 = dia;
    int mes2 = mes;
    int anyo2 = anyo;

    while(inc != 0){
        if(inc > 0){
            mes += inc;
            while(mes > 12){
                mes -= 12;
                anyo++;
            }
            int diasMes = calculaDiasMes(mes, anyo);
            if(dia > diasMes){
                dia = dia2;
                mes = mes2;
                anyo = anyo2;
                return false;
            }
            inc = 0;
        }
        if(inc < 0){
            mes -= abs(inc);
            while(mes <= 0){
                mes += 12;
                anyo--;
            }
            int diasMes = calculaDiasMes(mes, anyo);
            if(dia > diasMes){
                dia = diasMes;
            }
            inc = 0;
        }
        if(anyo < 1900){
                dia = dia2;
                mes = mes2;
                anyo = anyo2;
                return false;
            }
    }
    return true;
}

bool Fecha::incrementaAnyos(int inc){
    int dia2 = dia;
    int mes2 = mes;
    int anyo2 = anyo;

    while(inc != 0){
        while(inc > 0){
            anyo++;
            inc -= 1;

        }
        int diasMes = calculaDiasMes(mes, anyo);
            if(dia > diasMes){
                dia = dia2;
                mes = mes2;
                anyo = anyo2;
                return false;
            }
        if (inc < 0){
            if(anyo < 1900){
                dia = dia2;
                mes = mes2;
                anyo = anyo2;
                return false;
            }else{
                anyo -= 1;
                inc++;
            }
        }
    }
    return true;
}

string Fecha::aCadena(bool larga, bool conDia) const{
    string ldia = to_string(dia);
    string lmes = to_string(mes);
    string lanyo = to_string(anyo);
    string lfecha = "";
    string ldiasemana;

    int diacalculo;
    if (conDia){
        diacalculo = obtenerDiaSemana();
        switch (diacalculo){
        case (0):
            ldiasemana = "lunes";
            break;
        case (1):
            ldiasemana = "martes";
            break;
        case (2):
            ldiasemana = "miércoles";
            break;
        case (3):
            ldiasemana = "jueves";
            break;
        case (4):
            ldiasemana = "viernes";
            break;
        case (5):
            ldiasemana = "sábado";
            break;
        case (6):
            ldiasemana = "domingo";
            break;
        default:
            break;
        }
    }
    if (larga){
        switch(mes){
            case (1):
                lmes = "enero";
                break;
            case (2):
                lmes = "febrero";
                break;
            case (3):
                lmes = "marzo";
                break;
            case (4):
                lmes = "abril";
                break;
            case (5):
                lmes = "mayo";
                break;
            case (6):
                lmes = "junio";
                break;
            case (7):
                lmes = "julio";
                break;
            case (8):
                lmes = "agosto";
                break;
            case (9):
                lmes = "septiembre";
                break;
            case (10):
                lmes = "octubre";
                break;
            case (11):
                lmes = "noviembre";
                break;
            case (12):
                lmes = "diciembre";
                break;
        }
    }

    if(larga){
        if (conDia){
            lfecha = lfecha + ldiasemana + " " + ldia + " de " + lmes + " de " + lanyo;
        } else {
            lfecha = lfecha + ldia + " de " + lmes + " de " + lanyo;
        }
    } else {
        if (conDia){
            lfecha = lfecha + ldiasemana + " " + ldia + "/" + lmes + "/" + lanyo;
        } else {
            lfecha = lfecha + ldia + "/" + lmes + "/" + lanyo;
        }
    }
    return lfecha;
    //return string();
}

 


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



