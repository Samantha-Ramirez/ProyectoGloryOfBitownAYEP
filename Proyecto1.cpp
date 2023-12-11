#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
using namespace std;
/*
class Tablero{
    int filas;
    int columnas;
    int** tablero;
    char casillaDefault = '.';
    char casillaInvalida = '*';
    string portalSalida = "PS";
    string portalEntrada = "PE";
    string arbol = "AR";
    string pantano = "PA";
    string mounstroSlime = "S";
    string mounstroOrco = "O";
    string mounstroGigante = "G";
    string arquero = "AR";
    string luchador = "LU";

    Tablero(int filas, int columnas){
        this -> filas = filas;
		this -> columnas = columnas;
        this -> tablero = crearTablero(filas, columnas);
    }

    int** crearTablero(int filas, int columnas){
		int** matriz = new int*[filas];
		for(int i = 0; i < filas; i++){
				matriz[i] = new int[columnas];
		}
        return matriz;
    }

    void initTablero(){
        for(int i = 0; i < filas; i++){
            for(int j = 0; j < columnas; j++){
                this -> tablero[i][j] = casillaDefault;
            }
        }
    }

    void printTablero(){
        cout << endl;
        for(int i = 0; i < filas; i++) {
            for(int j = 0; j < columnas; j++)
                cout << " " << tablero[i][j];
            cout << endl;
        }
        cout << endl;
    }

    void borrarTablero(int** matriz, int filas, int columnas){
		for(int i = 0; i < filas; i++){
				delete[]matriz[i];
		}
		delete[]matriz;
    }
};
*/

int main(){
    string V = "";    //Vitalidad del Aventurero
    string T = ""; //Tipo de Aventurero
    string M = "";    //Cantidad de Mazmorras
    //L A = Largo y Ancho de la Mazmorra respectivamente  
    
    string linea;
    string tableroString = "35$LU$1";
    int sizeOfTableroString = 7;
    while(getline(cin, linea)) {
        tableroString += linea;
        tableroString += "$";
        //cout << linea << endl;
    }
    int i = 0;
    for(; i < sizeOfTableroString; i++){
        if(tableroString[i] == '$')
            break;
        V += tableroString[i];
    }
    for(i = i+1; i < sizeOfTableroString; i++){
        if(tableroString[i] == '$')
            break;
        T += tableroString[i];
    }
    for(i = i+1; i < sizeOfTableroString; i++){
        if(tableroString[i] == '$')
            break;
        M += tableroString[i];
    }
    
    return 0;
}