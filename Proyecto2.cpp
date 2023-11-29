#include <iostream>
using namespace std;

/*
V = Vitalidad del Aventurero.
T = Tipo de Aventurero.
M = Cantidad de Mazmorras.
L A = Largo y Ancho de la Mazmorra respectivamente.
Configuración de la mazmorra.*/

class Tablero{
    int filas;
    int columnas;
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

    Tablero(){
        this -> filas = 0;
		this -> columnas = 0;
    }

    Tablero(int filas, int columnas){
        this -> filas = filas;
		this -> columnas = columnas;
        this -> char tablero[filas][columnas];
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
}


int main(){

    /*CREACION TABLERO*/
    int vitalidad;
    string tipoDeAventurero;
    int cantidadMazmorras; 
    int largoMazmorra; /*por cada mazmorra*/
    int anchoMazmorra;

    cin >> vitalidad; 
    cin >> tipoDeAventurero;
    cin >> cantidadMazmorras;
    cin >> largoMazmorra;
    cin >> anchoMazmorra;

    return 0;
}