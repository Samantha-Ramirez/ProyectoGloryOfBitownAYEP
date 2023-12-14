#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string> //stoi
using namespace std;

/*TO DO
- TIPO DE DATO MAZMORRA
- OBTENER A, L
- POR QUE CARACTERES RAROS EN PRIMERO 
- RECORRIDO COMPLETO DE MAZMORRA
*/

//DECLARACION PROVISIONAL DE VALORES
char casillaDefault = '.';
char casillaInvalida = '*';
string portalEntrada = "PE";
string portalSalida = "PS";
string arbol = "AR";
string pantano = "PA";
string mounstroSlime = "S";
string mounstroOrco = "O";
string mounstroGigante = "G";
string arquero = "AR";
string luchador = "LU";

//METODOS MAZMORRA
string** createMazmorra(int row, int col){
    string** maz = new string*[row];
    for(int i = 0; i < row; i++){
            maz[i] = new string[col];
    }
    
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            maz[i][j] = "";
        }
    }
    
    return maz;
}

void initMazmorra(string** mazmorra, string line, int i){
    int x = 0;
    int j = 0;
    for(int j = 0; j < line.size(); j++){
        if(line[j] != ' '){
            mazmorra[i][x] += line[j];
        }else{
            x++;
        }
    }
}

void printMazmorra(string** mazmorra, int row, int col){
    cout << endl;
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++)
            cout << " " << mazmorra[i][j];
        cout << endl;
    }
    cout << endl;
}

void deleteMazmorra(string** mazmorra, int row, int col){
    for(int i = 0; i < row; i++){
        delete[]mazmorra[i];
    }
    delete[]mazmorra;
}

int cutStringNum(string line, int &index){
    string aux = "";
    for(int i = index; i < line.size(); i++){
        if(line[i] == ' ')
            break;
        aux += line[i];
        index++;
    }
    index++;
    return stoi(aux);
}

int main(){

    //GET DATOS DEL TXT
    string line;

    //Vitalidad del Aventurero
    int V = -1;
    getline(cin, line);
    int index = 3;
    V = cutStringNum(line, index);

    //Tipo de Aventurero
    string T = "";
    getline(cin, line);
    T = line;

    //Cantidad de Mazmorras 
    int M = -1;
    getline(cin, line);
    M = stoi(line);
    
    for(int i = 0; i < M; i++){
        //Largo de Mazmorra
        //Ancho de Mazmorra
        int L = -1;
        int A = -1;
        getline(cin, line);
        
        int index = 0;
        L = cutStringNum(line, index);
        A = cutStringNum(line, index);
        
        
        string** mazmorra = createMazmorra(L, A);
        printMazmorra(mazmorra, L, A);
        for(int i = 0; i < L; i++){
            getline(cin, line);
            
            initMazmorra(mazmorra, line, i);
        }
        
        printMazmorra(mazmorra, L, A);
        deleteMazmorra(mazmorra, L, A);
        
    }
    
    return 0;
}