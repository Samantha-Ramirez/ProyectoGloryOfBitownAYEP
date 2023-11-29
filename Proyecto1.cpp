#include <iostream>
using namespace std;

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

    void borrarMatriz(int** matriz, int filas, int columnas){
		for(int i = 0; i < filas; i++){
				delete[]matriz[i];
		}
		delete[]matriz;
    }
};


int main(){
    int V; //Vitalidad del Aventurero
    string T; //Tipo de Aventurero
    int M; //Cantidad de Mazmorras

    /*por cada mazmorra
    int L; // Largo mazmorra
    int A; // Ancho mazmorra
    cin >> L;
    cin >> A;
    */

    cin >> V; 
    cin >> T;
    cin >> M;

    return 0;
}