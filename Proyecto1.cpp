#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string> //stoi
using namespace std;

/*TO DO
- TIPO DE DATO MAZMORRA string || clase x
- CARACTERES RAROS EN EL PRINCIPIO DEL TXT
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
class Mazmorra{
    public:
    int row;
    int col;
    string** mazmorra;

    Mazmorra(int L, int A){
        this -> row = L;
        this -> col = A;
    }
    string** createMazmorra(){
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
    void initMazmorra(string line, int i){
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
    void printMazmorra(){
        cout << endl;
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++)
                cout << " " << mazmorra[i][j];
            cout << endl;
        }
        cout << endl;
    }
    void deleteMazmorra(){
        for(int i = 0; i < row; i++){
            delete[]mazmorra[i];
        }
        delete[]mazmorra;
    }
};

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
    /*Al principio del archivo salen caracteres raros, 
    debo investigarlo pero por los momentos lo estoy cortando*/
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

        //Mazmorra
        Mazmorra mazmorra(L, A);
        
        mazmorra.mazmorra = mazmorra.createMazmorra();
        for(int i = 0; i < L; i++){
            getline(cin, line);
            mazmorra.initMazmorra(line, i);
        }
        
        mazmorra.printMazmorra();
        mazmorra.deleteMazmorra();
        
    }
    
    return 0;
}