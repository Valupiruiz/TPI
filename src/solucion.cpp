#include "solucion.h"
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <string>
#include <cctype>
#include <math.h>       /* pow */

// Ejercicios
//1*********************************************************************************************************
bool duraMasDe(vector<int> s, int freq , float segundos){
    return s.size() >= freq * segundos;
}

bool enRango(vector<int> S, int prof){
    int verificador = 0;
    int capacidadMaxima =  pow(2,prof-1)-1;
    int capacidadMinima =  pow(-2,prof-1);
    for(int i = 0;i<S.size();i=i+1){
        if (S[i]>=capacidadMinima && S[i]<=capacidadMaxima){
            verificador = verificador + 1;
        }
    }
    return (verificador == S.size());
}

bool profValida(int prof){
    return prof == 8 || prof == 16 || prof == 32;
}

bool frecValida(int freq){
    return freq == 10;
}

bool esValida(vector<int> s, int prof, int freq){
    return frecValida(freq) && profValida(prof) && enRango(s, prof) && (duraMasDe(s, freq, 1));
}

bool esSenial(vector<int> s, int prof, int freq) {
    bool resp = false;
    return esValida(s, prof, freq);
    //return resp;
}
//1*********************************************************************************************************

//2*********************************************************************************************************

vector<int> subsenial(int i,senial s){
    vector<int> res;
    for(int j=0;j<=i;j=j+1){
        res.push_back(s[j]);
    }
    return res;
}

int tono(senial s){
    int sumatoria = 0;
    for(int j=0;j<s.size();j=j+1){
        sumatoria = sumatoria + abs(s[j]);
    }
    return (sumatoria / (s.size()));
}

bool umbralValido(int umbral){
    return umbral > 0;
}
bool superaElUmbral(senial s , int umbral){
    return tono(s)>umbral;
}

bool seEnojo(senial s, int umbral, int prof , int freq){
    if(esValida(s,prof,freq) && umbralValido(umbral)){
        for(int i=0;i<s.size();){
            if(superaElUmbral(subsenial(i,s),umbral) && duraMasDe(subsenial(i,s),freq,2)){
                return true;
            }else{
                i=i+1;
            }
        }
    }else{
        return false;
    }
    return false;
}
//2***********************************************************************************************************

//3***********************************************************************************************************
bool esMatriz(reunion r){
    int verificadorMatriz = 0;
    for(int i =0; i<r.size();i=i+1){
        if((r[i].first).size() == (r[0].first).size()){
            verificadorMatriz = verificadorMatriz + 1;
        }
    }
    return (verificadorMatriz==r.size());
}
//Debo revisar si es Matriz la reunion ,para que se cumpla
int aparicionesHablantes(int r0,reunion r){
    int cantidadDeAparacionDeHablantes = 0;
    for(int i = 0; i<r.size();i=i+1){
        if(r[i].second == r0){
            cantidadDeAparacionDeHablantes = cantidadDeAparacionDeHablantes + 1;
        }
    }
    return cantidadDeAparacionDeHablantes;
}

//Cuantas Veces aparece dicho hablante

bool hablantedeReunionValidos(reunion r, int prof, int freq){
    int validacionHablantes = 0;
    for(int i =0;i<r.size();i=i+1){
        if(aparicionesHablantes(r[i].second,r)==1){
            validacionHablantes = validacionHablantes + 1;
        }
    }
    return (validacionHablantes == r.size());
}



//Me fijo que cada hablante aparezca solo 1 vez(eso hace que no haya repetidos)
bool senialesValidas(reunion r, int prof, int freq){
    int validacion = 0;
    for(int i=0;i<r.size();i=i+1){
        if(esValida(r[i].first,prof,freq)){
            validacion++;
        }
    }
    return (validacion == r.size());
}

bool esReunionValida(reunion r, int prof, int freq) {
    if(r.size()>0 && senialesValidas(r,prof,freq) && hablantedeReunionValidos(r,prof,freq) && esMatriz(r)){
        return true;
    }else{
        return false;
    }
    return false;
}

//3***********************************************************************************************************
//4***********************************************************************************************************

void mostrarVector(vector<int> v){
    int i=0;
    cout<<"vector[";
    while (i<v.size()){
        if (i == v.size()-1){
            cout <<v[i] <<"";
            i = i +1;
        }else{
            cout <<v[i] << " "<<","<<" ";
            i = i +1;
        }
    }cout<<"]"<<endl;
}
void senialAcelereada(vector<int> &r) {
    vector<int> res;
    for(int i=0;i<r.size();i=i+1){
        if( i % 2 == 1){
            res.push_back(r[i]);
        }
    }
    r = res;
}


bool longitudesValidas(reunion r0, int freq){
    int verificadorDeLongitudValida = 0;
    for(int i=0;i<r0.size();i=i+1){
        if(((r0[i].first).size() / 2) >= freq * 1){
            verificadorDeLongitudValida = verificadorDeLongitudValida + 1;
        }
    }
    return verificadorDeLongitudValida==r0.size();
}//Aca coloque freq*1 porque a mi ver el profesor coloco 1000 por error(no trabajamos con lista de un largo tan largo todavia)


void acelerar(reunion &r, int prof, int freq) {
    if(esReunionValida(r,prof,freq)&& longitudesValidas(r,freq) ){
        for(int i=0;i<r.size();i++){
            senialAcelereada(r[i].first);
            mostrarVector(r[i].first);
        }
    }
}
//4****************************************************************************************************

//5****************************************************************************************************

int promedio(int numero1 , int numero2){
    return (numero1+numero2)/2;
}

senial senialRelantizada(vector<int> r ){
    vector<int> res;
    for(int i=0;i<r.size();i=i+1){
        if(i!=r.size()-1){
            res.push_back(r[i]);
            res.push_back(promedio(r[i],r[i+1]));
        }else{
            res.push_back(r[i]);
        }
    }
    return res;
}


void ralentizar(reunion &r, int prof, int freq) {
    if(esReunionValida(r,prof,freq)){
        for(int i=0;i<r.size();i=i+1){
            r[i].first = senialRelantizada(r[i].first);
            mostrarVector(r[i].first);
        }
    }
}
//5*********************************************************************************************************

//6*********************************************************************************************************
hablante HablanteDelControlador(senial controlador , reunion r){
    for(int i=0;i<r.size();i=i+1){
        if(controlador == r[i].first){
            return r[i].second;
        }
    }
    return 0;
}
hablante TieneElTonoMasElevado(reunion r){
    senial controlador = r[0].first;
    for(int i =0;i<r.size();i=i+1){
        if (tono(r[i].first) >= tono(controlador)){
            controlador = r[i].first;
        }
    }
    return HablanteDelControlador(controlador,r);
}
//esto es igual a buscar el maximo de una secuencia ,solo ahora evaluando el tono ,pero es la misma idea, y aca devuelve una señal
// ahora que tengo la señal que se que esta en r ,puedo sacarle su hablante


vector<hablante> tonosDeVozElevados(reunion r, int prof, int freq){
    vector<hablante> res;
    if(esReunionValida(r,prof,freq)){
        res.push_back(TieneElTonoMasElevado(r));
    }
    return res;
}
//6********************************************************************************************************

//7********************************************************************************************************
void ReunionOrdenada(reunion &r){
    senial res1;
    hablante res2;
    for(int i =0;i<r.size();i=i+1){
        for(int j =i+1;j<r.size();j=j+1){
            if (tono(r[i].first) <= tono(r[j].first)){
                res1=r[i].first;
                res2=r[i].second;
                r[i].first = r[j].first;
                r[i].second = r[j].second;
                r[j].first = res1;
                r[j].second = res2;

            }
        }
    }
}

void ordenar(reunion &r, int prof, int freq){
    if (esReunionValida(r, prof, freq)){//FUNCION PRINCIPAL
        ReunionOrdenada(r);
        cout<<"Test011"<<"";
    }
}
//7********************************************************************************************************

//8********************************************************************************************************
bool intervaloSilencio(senial s,int umbral){
    int verificador = 0;
    for(int i=0;i<s.size();i++){
        if( s[i]<umbral){
            verificador = verificador +1;
        }
    }
    return verificador == s.size();
}


vector<int> subSecAbs(senial s,int i ,int j){//hace como subsecuencia pero todo lo que entra se vuelve +
    vector<int> res;
    while(i<=j){
        res.push_back(abs(s[i]));
        i=i+1;
    }
    return res;

}


vector<intervalo> silencios(senial s, int prof, int freq, int umbral) {
    vector<pair<int,int> > intervalos;
    if(esSenial(s,prof,freq) && umbralValido(umbral)){
        for(int i=0;i<s.size();i++){
            for(int j=0;j<s.size();j++){
                if( duraMasDe(subSecAbs(s,i,j),freq,0.1) && intervaloSilencio(subSecAbs(s,i,j),umbral)){
                    if( i<j  || (i==0 && j==0) || (i==s.size()-1 && j==s.size()-1)){
                        intervalos.push_back(make_pair(i,j));
                    }
                }
            }
        }
    }
    return intervalos;
}

//8**********************************************************************************************************

//9**********************************************************************************************************
bool existeHablanteConIgualIntervalo(vector<intervalo>, hablante){
    int i = 0;

}
bool hablantesSuperpuestos(reunion r, int prof, int freq, int umbral) {
    bool resp = false;
    vector<pair<vector<intervalo>,hablante>> silencios_hablantes;
    if(esReunionValida(r,prof,freq) && umbralValido(umbral)){
        for(int i=0; i < r.size(); i++) {
            pair<vector<intervalo>, hablante> hablante_silencio;
            hablante_silencio.first = silencios(r[i].first, prof, freq, umbral);
            hablante_silencio.second = r[i].second;
            silencios_hablantes.push_back(hablante_silencio);
        }
    while( j < s.size && !resp){
        resp = existeHablanteConIgualIntervalo(silencios_hablantes[i].first, silencios_hablantes[i].second);
        j++;
        }
    }
    return resp;
}

//9*********************************************************************************************************

//10*********************************************************************************************************

senial reconstruir(senial s, int prof, int freq) {
    senial senalReconstruida;
    // Implementacion
    return senalReconstruida;
}

//10*********************************************************************************************************

//11*********************************************************************************************************

void filtradoMediana(senial& s, int R, int prof, int freq){
    // Implementacion
    return;
}

//11*********************************************************************************************************
