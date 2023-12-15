#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string> //stoi
using namespace std;

//VALORES
string casillaDefault = ".";
string casillaInvalida = "*";
string portalEntrada = "PE";
string portalSalida = "PS";
string arbol = "AR";
string pantano = "PA";
string mounstroSlime = "S";
string mounstroOrco = "O";
string mounstroGigante = "G";
string arquero = "AR";
string luchador = "LU";
enum outputsMazmorra{
    YOUGETTHEGLORY = 0, 
    YOUSURVIVE = 1, 
    YOUDIE = 2,
};

//BORRAR
string tipoAventurero = luchador;

//MAZMORRA
//Movimientos
int posibilitiesI[] = {1, 0, 0, -1};
int posibilitiesJ[] = {0, 1, -1, 0};
int sizePosibilities = sizeof(posibilitiesI)/sizeof(int);

class Mazmorra{
    public:
    int row; //filas
    int col; //columnas
    int iPE; //i portal de entrada
    int jPE; //j portal de entrada
    int iPS; //i portal de salida
    int jPS; //j portal de salida
    string** mazmorra; //mazmorra
    outputsMazmorra output; //resultado del recorrido

    Mazmorra(int L, int A){
        this -> row = L;
        this -> col = A;
        this -> output = YOUDIE;
    }

    string** createMazmorra(){
        //crear
        string** maz = new string*[row];
        for(int i = 0; i < row; i++){
            maz[i] = new string[col];
        }
        
        //inicializar
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

            //ignorar espacio
            if(line[j] != ' '){
                mazmorra[i][x] += line[j];
                
                //encontrar portal de entrada
                if(mazmorra[i][x] == portalEntrada){
                    this -> iPE = i;
                    this -> jPE = x;
                }else if(mazmorra[i][x] == portalSalida){
                    this -> iPS = i;
                    this -> jPS = x;
                }

            }else{
                //cambiar indice cuando hay espacio
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
    
    bool isMonster(string position){
        if(position[0] == mounstroSlime[0] || position[0] == mounstroOrco[0] || position[0] == mounstroGigante[0]){
            return true;
        }
        return false;
    }

    bool stillMonsters(){
        //
        return true;
    }

    bool isValid(int i, int j, int index){
        i = i + posibilitiesI[index];
        j = j + posibilitiesJ[index];
        
        if(i >= 0 && i < row && j >= 0 && j < col){
            if((mazmorra[i][j] == casillaDefault)
            || (mazmorra[i][j] == arbol && tipoAventurero == arquero)
            || (mazmorra[i][j] == pantano && tipoAventurero == luchador)
            || (mazmorra[i][j] == portalSalida)){
                return true;

            }else if(isMonster(mazmorra[i][j])){
                //fight();
            }
        }
        return false;
    }

    void place(int &i, int &j, int index){
        i = i + posibilitiesI[index];
        j = j + posibilitiesJ[index];
    }

    bool isSolution(int i, int j){
        if(i == iPS && j == jPS){
            return true;
        }
        return false;
    }

    bool isBestSolution(){
        if(!stillMonsters()){
            return true;
        }
        return false;
    }
    
    void wanderMazmorra(int iIndex, int jIndex){
        if(isSolution(iIndex, jIndex)){
            this -> output = YOUSURVIVE;
            if(isBestSolution()){
                this -> output = YOUGETTHEGLORY;
            }
        }
        else if(output != YOUGETTHEGLORY && iIndex * jIndex < row * col){
            for(int i = 0; i < sizePosibilities; i++){
                if(isValid(iIndex, jIndex, i)){
                    //backup
                    int auxI = iIndex;
                    int auxJ = jIndex;

                    //procesar
                    place(iIndex, jIndex, i);
                    string auxPosition = mazmorra[iIndex][jIndex];
                    mazmorra[iIndex][jIndex] = casillaInvalida;       
                    printMazmorra();

                    //backtracking
                    wanderMazmorra(iIndex, jIndex);

                    //reload backup
                    mazmorra[iIndex][jIndex] = auxPosition;
                    iIndex = auxI;
                    jIndex = auxJ;
                }
            }
        }
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
    getline(cin, line);
    int V = stoi(line);

    //Tipo de Aventurero
    getline(cin, line);
    string T = line;

    //Cantidad de Mazmorras 
    getline(cin, line);
    int M = stoi(line);
    
    for(int i = 0; i < M; i++){
        //Largo de Mazmorra
        //Ancho de Mazmorra
        getline(cin, line);
        int index = 0;
        int L = cutStringNum(line, index);
        int A = cutStringNum(line, index);

        //MAZMORRA
        Mazmorra mazmorra(L, A);
        mazmorra.mazmorra = mazmorra.createMazmorra();
        for(int i = 0; i < L; i++){
            getline(cin, line);
            mazmorra.initMazmorra(line, i);
        }

        //BACKTRACKING
        mazmorra.wanderMazmorra(mazmorra.iPE, mazmorra.jPE);

        //SALIDA
        cout << "SALIDA " << mazmorra.output << endl;

        //ELIMINAR MAZMORRA
        mazmorra.deleteMazmorra();
        
    }
    
    return 0;
}