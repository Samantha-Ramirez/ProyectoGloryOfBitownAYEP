#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
using namespace std;

//VALORES MAZMORRA
string casillaDefault = ".";
string casillaInvalida = "*";
string portalEntrada = "PE";
string portalSalida = "PS";
string arbol = "AR";
string pantano = "PA";
string monstruoSlime = "S";
string monstruoOrco = "O";
string monstruoGigante = "G";
string arquero = "AR";
string luchador = "LU";
string monstruoNoSuperable = "M";
string residuoMonstruo = "R";
enum outputsMazmorra{
    YOUGETTHEGLORY = 0, 
    YOUSURVIVE = 1, 
    YOUDIE = 2,
};

int extract_num(string t){
	string n_t = "";
	for (int i = 1; i < t.size(); ++i){
		n_t+= t[i];
	}
	return stoi(n_t);
}

char getFirstPosition(string position){
    return position[0];
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

bool isNumber(char pos){
    char num[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int sizeNum = 10;
    for(int i = 0; i < sizeNum; i++){
        if(pos == num[i]){
            return true;
        }
    }
    return false;
}

int getNumber(string line){
    string num = "";
    for(int i = 0; i < line.size(); i++){
        if(isNumber(line[i])){
            num += line[i];
        }
    }
    return stoi(num);
}

class ability{
public:
	int dmg = -1; //Daño
	int cd = -1; //Cooldown
	int used = -99; //Ultimo turno en el que se usó
	ability(int _dmg, int _cd, int _used){
		dmg = _dmg;
		cd = _cd;
		used = _used;
	}
};

class Entity{
public:
	char type; //Tipo
	int ability_num; //Numero de habilidad
	int vitality; //Vitalidad
	ability* ptr_abs; //Pointer de habilidades

	void print(){
		cout << "Class: " << type <<"\n";
		cout << "VIT: " << vitality << " - ";
		cout << "ABS: " << ability_num << "\n";
	}

	void recieve_damage(int dmg){
		vitality -= dmg;
	}

	int calculate_ability(int turn, bool log = false){
		int damage_to_execute = 0;

		//DEBUG
		if(log){print();}

		for (int i = 0; i < ability_num; ++i){
			if (turn - (ptr_abs+i)-> cd > (ptr_abs+i)-> used){
				damage_to_execute = (ptr_abs+i)-> dmg;
				if(log){cout << "PREV_USE: " << (ptr_abs+i)-> used << " - ";}
				(ptr_abs+i)-> used = turn;
				if(log){cout << "NEW_USE : " << (ptr_abs+i)-> used << "\n";}
				break;
			}
		}
		if(log){cout << "Attacks : " << damage_to_execute << " -  Vitality: " << vitality << "\n\n";}

		return damage_to_execute;
	}
};

//LUCHADOR
ability lu_arr_abs[4] = {ability(12,4,-99),ability(7,3,-99),ability(4,2,-99),ability(2,1,-99)}; //array de habilidades
class Lu: public Entity{
	public:
		Lu(int _vitality = -1){
			type = getFirstPosition(luchador);
			ability_num = 4;
			vitality = _vitality;
			ptr_abs = &lu_arr_abs[0];
		}
};

//ARQUERO
ability ar_arr_abs[4] = {ability(2,3,-99),ability(2,2,-99),ability(2,1,-99),ability(1,1,-99)}; //array de habilidades
class Ar: public Entity{
	public:
		Ar(int _vitality = -1){
			type = getFirstPosition(arquero);
			ability_num = 4;
			vitality = _vitality;
			ptr_abs = &ar_arr_abs[0];
		}
};

//SLIMES
ability sl_arr_abs[1] = {ability(1,1,-99)}; //array de habilidades
class Sl: public Entity{
	public:
		Sl(int _vitality = -1){
			type = getFirstPosition(monstruoSlime);
			ability_num = 1;
			vitality = _vitality;
			ptr_abs = &sl_arr_abs[0];
		}
};

//ORCOS
ability or_arr_abs[2] = {ability(4,3,-99), ability(2,2,-99)}; //array de habilidades
class Or: public Entity{
	public:
		Or(int _vitality = -1){
			type = getFirstPosition(monstruoOrco);
			ability_num = 1;
			vitality = _vitality;
			ptr_abs = &or_arr_abs[0];
		}
};

//GIGANTES
ability gi_arr_abs[1] = {ability(5,2,-99)}; //array de habilidades
class Gi: public Entity{
	public:
		ability arr_abs[1] = {ability(5,2,-99)};
		Gi(int _vitality = -1){
			type = getFirstPosition(monstruoGigante);
			ability_num = 1;
			vitality = _vitality;
			ptr_abs = &gi_arr_abs[0];
		}
};

//OBTENER HEROE
Entity get_hero(char hero_type, int hero_vitality){
	switch(hero_type){
	case 'L': return Lu(hero_vitality); break;
	case 'A': return Ar(hero_vitality);
	default: return Ar(hero_vitality);
	}
}

//OBTENER MONSTRUO
Entity get_monster(char monster_type, int monster_vitality){
	switch(monster_type){
	case 'S': return Sl(monster_vitality);
	case 'O': return Or(monster_vitality);
	case 'G': return Gi(monster_vitality);
	default : return Gi(monster_vitality);
	}
}

//COMBATE
int combat(Entity hero, Entity monster, int turn, bool log = false){
	if(hero.vitality <= 0){return 0;}
	int hero_damage = 0;
	int monster_damage = 0;

	hero_damage = hero.calculate_ability(turn);
	monster.recieve_damage(hero_damage);

	if(log){cout << "V: " << hero.vitality <<" DMG: " << hero_damage << " M: " << monster.vitality << "\n";}
	if(monster.vitality <= 0){return hero.vitality;}
	
	monster_damage = monster.calculate_ability(turn);
	hero.recieve_damage(monster_damage);
	turn += 1;

	return combat(hero, monster, turn, log);
}

//COMENZAR COMBATE
int start_combat(char hero_type, int hero_vitality ,string monster_string, bool log = false){
	char monster_type = monster_string[0];
	int monster_vitality = extract_num(monster_string);
	Entity hero = get_hero(hero_type, hero_vitality);
	Entity monster = get_monster(monster_type, monster_vitality);

	return combat(hero, monster, 1, log);
}

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
    Entity adventure; //aventurero
    

    Mazmorra(int V, string T, int L, int A){
        this -> row = L;
        this -> col = A;
        this -> output = YOUDIE; //por default
        this -> adventure.type = getFirstPosition(T);
        this -> adventure.vitality = V;
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
                maz[i][j] = ".";
            }
        }
        
        return maz;
    }

    int valuesMazmorra(string position){
        string values[] = {casillaDefault, casillaInvalida, portalEntrada, portalSalida, arbol, pantano};
        int valuesSize = 6;
        string monsters[] = {monstruoSlime, monstruoOrco, monstruoGigante};
        int monstersSize = 3;
        //valor exacto
        for(int i = 0; i < valuesSize; i++){
            if(position == values[i]){
                return 1;
            }
        }
        //es un monstruo
        for(int i = 0; i < monstersSize; i++){
            if(position == monsters[i]){
                return 0;
            }
        }
        //inicio
        for(int i = 0; i < valuesSize; i++){
            if(position[0] == getFirstPosition(values[i])){
                return 2;
            }
        }
        return -1;
    }

    void initMazmorra(string line, int i){
        //Suprimir espacios
        string newLine = "";
        for(int j = 0; j < line.size(); j++){
            if(line[j] != ' '){
                newLine += line[j];
            }
        }

        int x = 0;
        string aux = "";
        for(int j = 0; j < newLine.size(); j++){
            aux += newLine[j];

            if(valuesMazmorra(aux) == 1){
                mazmorra[i][x] = aux;
                //encontrar portal de entrada
                if(mazmorra[i][x] == portalEntrada){
                    this -> iPE = i;
                    this -> jPE = x;
                }else if(mazmorra[i][x] == portalSalida){
                    this -> iPS = i;
                    this -> jPS = x;
                }
                aux = "";
                x++;
            }else if(valuesMazmorra(aux) == 0){
                mazmorra[i][x] = aux;
                
                string num = "";
                while(j+1 < newLine.size() && valuesMazmorra(num + newLine[j+1]) == -1){
                    mazmorra[i][x] += newLine[j+1];
                    num = "";
                    j++;
                }
                aux = "";
                x++;
            }
        }
    } 

    void printMazmorra(){
        cout << endl;
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++){
                cout << " " << mazmorra[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }

    void printOutput(int o){
        switch(o){
        case YOUGETTHEGLORY: cout << "YOU GET THE GLORY" << endl; break;
        case YOUSURVIVE: cout << "YOU SURVIVE" << endl; break;
        case YOUDIE: cout << "YOU DIE" << endl; break;
        }
    }

    void deleteMazmorra(){
        for(int i = 0; i < row; i++){
            delete[]mazmorra[i];
        }
        delete[]mazmorra;
    }

    int typeOfMonster(string position){
        switch(getFirstPosition(position)){
        case 'M': return 3;
        case 'S': return 2;
        case 'O': return 1;
        case 'G': return 0;
        default: return -1;
        }
    }

    bool isMonster(string position){
        if(typeOfMonster(position) != -1){
            return true;
        }
        return false;
    }

    bool stillMonsters(){
        bool isThereMonsters = false;
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++){
                if(isMonster(mazmorra[i][j])){
                    isThereMonsters = true;
                    return isThereMonsters;
                }
            }
        }
        return isThereMonsters;
    }

    void restoreMonsters(){
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++){
                //RESIDUOS DE GIGANTE
                if(getFirstPosition(mazmorra[i][j]) == getFirstPosition(residuoMonstruo)){
                    mazmorra[i][j] = "";
                    for(int k = 1; k < mazmorra[i][j].size(); k++){
                        mazmorra[i][j] += mazmorra[i][j][k];
                    }
                //NO SUPERABLE
                }else if((getFirstPosition(mazmorra[i][j]) == getFirstPosition(monstruoNoSuperable))){
                    int sizePosition = mazmorra[i][j].size();
                    mazmorra[i][j] = "";
                    for(int k = 1; k < sizePosition; k++){
                        mazmorra[i][j] += mazmorra[i][j][k];
                    }
                }
            }
        }
    }
    
    bool isValidValue(string position){
        if((position == casillaDefault)
        || (position == arbol && adventure.type == getFirstPosition(arquero))
        || (position == pantano && adventure.type == getFirstPosition(luchador))
        || (position == portalSalida)
        || (getFirstPosition(position) == getFirstPosition(monstruoSlime))
        || (getFirstPosition(position) == getFirstPosition(monstruoOrco))){
            return true;
        }
        return false; 
    }

    bool isValid(int i, int j, int index, int &vitality){
        i = i + posibilitiesI[index];
        j = j + posibilitiesJ[index];
        
        //Posicion dentro del tablero
        if(i >= 0 && i < row && j >= 0 && j < col){
            //COMBATE
            if(isMonster(mazmorra[i][j])){
                //Status despues de combate
                int status = start_combat(adventure.type, vitality, mazmorra[i][j], true);

                //derrota -> no sigo
                if(status == 0){
                    mazmorra[i][j] = monstruoNoSuperable + mazmorra[i][j]; //Marcado como no superable
                    printMazmorra();
                    return false;

                //victoria -> menos vida y cambio en mazmorra
                }else{
                    vitality = status;
                    if(getFirstPosition(mazmorra[i][j]) == getFirstPosition(monstruoGigante)){
                        mazmorra[i][j] = residuoMonstruo + mazmorra[i][j]; //Residuo de gigante
                    }
                }
            }

            //VALORES VALIDOS
            if(isValidValue(mazmorra[i][j])){
                return true;
            }
        }
        return false;
    }

    void place(int &i, int &j, int index){
        i = i + posibilitiesI[index];
        j = j + posibilitiesJ[index];
    }

    void displace(int &i, int &j, int index){
        i = i - posibilitiesI[index];
        j = j - posibilitiesJ[index];
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
                int auxVitality = adventure.vitality;
                if(isValid(iIndex, jIndex, i, adventure.vitality)){

                    //procesar
                    place(iIndex, jIndex, i);

                    //backup
                    string auxPosition = mazmorra[iIndex][jIndex];
                    mazmorra[iIndex][jIndex] = casillaInvalida;

                    //log 
                    printMazmorra();

                    //backtracking
                    wanderMazmorra(iIndex, jIndex);

                    //deshacer
                    adventure.vitality = auxVitality;  
                    mazmorra[iIndex][jIndex] = auxPosition;
                    displace(iIndex, jIndex, i);

                    //log
                    printMazmorra();

                    
                }
            }
            restoreMonsters();
            printMazmorra();
        }
    }
};

int main(){
    //GET DATOS DEL TXT
    string line;

    //Vitalidad del Aventurero
    getline(cin, line);
    int V = getNumber(line);

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
        Mazmorra mazmorra(V, T, L, A);
        mazmorra.mazmorra = mazmorra.createMazmorra();
        for(int i = 0; i < L; i++){
            getline(cin, line);
            mazmorra.initMazmorra(line, i);
        }

        //BACKTRACKING
        mazmorra.wanderMazmorra(mazmorra.iPE, mazmorra.jPE);
        mazmorra.printMazmorra();

        //SALIDA
        mazmorra.printOutput(mazmorra.output);

        //ELIMINAR MAZMORRA
        mazmorra.deleteMazmorra();
        
    }
    
    return 0;
}