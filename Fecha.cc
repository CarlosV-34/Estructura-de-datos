#include<string>
#include "Fecha.h"

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

 
