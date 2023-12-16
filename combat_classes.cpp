#include <iostream>
using namespace std;

class ability
{
public:
	int dmg = -1;
	int cd = -1;
	int used = -99;
	ability(int _dmg, int _cd, int _used){
		dmg = _dmg;
		cd = _cd;
		used = _used;
	}
};

class Entity //Just an Interface
{
public:
	char type;
	int ability_num;
	int vitality;
	ability* ptr_abs;
	void print(){
		cout << "Class: " << type <<"\n";
		cout << "VIT: " << vitality << " - ";
		cout << "ABS: " << ability_num << "\n";
	}
	void recieve_damage(int dmg){vitality -= dmg;}
	int calculate_ability(int turn, bool log = false){
		int damage_to_execute = 0;
		if(log){print();}
		for (int i = 0; i < ability_num; ++i)
		{
			if (turn - (ptr_abs+i)-> cd > (ptr_abs+i)-> used)
			{
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

ability lu_arr_abs[4] = {ability(12,4,-99),ability(7,3,-99),ability(4,2,-99),ability(2,1,-99)};
class Lu: public Entity{
	public:
		Lu(int _vitality = -1){
			type = 'L';
			ability_num = 4;
			vitality = _vitality;
			ptr_abs = &lu_arr_abs[0];
		}
};

ability ar_arr_abs[4] = {ability(2,3,-99),ability(2,2,-99),ability(2,1,-99),ability(1,1,-99)};
class Ar: public Entity{
	public:
		Ar(int _vitality = -1){
			type = 'A';
			ability_num = 4;
			vitality = _vitality;
			ptr_abs = &ar_arr_abs[0];
		}
};

ability sl_arr_abs[1] = {ability(1,1,-99)};
class Sl: public Entity{
	public:
		Sl(int _vitality = -1){
			type = 'S';
			ability_num = 1;
			vitality = _vitality;
			ptr_abs = &sl_arr_abs[0];
		}
};

ability or_arr_abs[2] = {ability(4,3,-99), ability(2,2,-99)};
class Or: public Entity{
	public:
		Or(int _vitality = -1){
			type = 'O';
			ability_num = 1;
			vitality = _vitality;
			ptr_abs = &or_arr_abs[0];
		}
};
ability gi_arr_abs[1] = {ability(5,2,-99)};
class Gi: public Entity{
	public:
		ability arr_abs[1] = {ability(5,2,-99)};
		Gi(int _vitality = -1){
			type = 'G';
			ability_num = 1;
			vitality = _vitality;
			ptr_abs = &gi_arr_abs[0];
		}
};

int extract_num(string t){
	string n_t = "";
	for (int i = 1; i < t.size(); ++i){
		n_t+= t[i];
	}
	return stoi(n_t);
}

Entity get_hero(char hero_type, int hero_vitality){
	switch(hero_type){
	case 'L': return Lu(hero_vitality); break;
	case 'A': return Ar(hero_vitality);
	default: return Ar(hero_vitality);
	}
}

Entity get_monster(char monster_type, int monster_vitality){
	switch(monster_type){
	case 'S': return Sl(monster_vitality);
	case 'O': return Or(monster_vitality);
	case 'G': return Gi(monster_vitality);
	default : return Gi(monster_vitality);
	}
}

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

int start_combat(char hero_type, int hero_vitality ,string monster_string, bool log = false){
	char monster_type = monster_string[0];
	int monster_vitality = extract_num(monster_string);
	Entity hero = get_hero(hero_type, hero_vitality);
	Entity monster = get_monster(monster_type, monster_vitality);


	return combat(hero, monster, 1, log);
}


int main(int argc, char const *argv[])
{	
	cout << start_combat('A', 25, "S23", true);
	return 0;
}