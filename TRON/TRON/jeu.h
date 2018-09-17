#pragma once
#ifndef JEU
#define JEU
class jeu {
public:
	//CONSTRUCTEURS
	jeu();
	jeu(const jeu &);

	//GET
	int get_id();
	int get_couleur();
	int get_vies();
	/*int *get_positions_X();
	int *get_positions_Y();*/

	//SET
	void set_id(int new_id);
	void set_couleur(int new_couleur);
	void set_vies(int new_vies);
	/*void set_positions(int * new_positions);
	void set_dern_position(int X, int Y);*/

private:
	int id;
	int couleur;
	int vies;
	//int ** positions;
};
#endif // !JEU
