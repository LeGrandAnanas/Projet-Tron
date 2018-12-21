#pragma once
#ifndef JEU
#define JEU
class jeu {
public:
	//CONSTRUCTEURS
	jeu();
	jeu(const jeu &);

	void create_map(int taille);

	//GET
	int get_id();
	int get_vies();
	void get_map();
	int get_X();
	int get_Y();
	int get_dir();
	int get_taille();
	int ** get_pos_prec();

	//SET
	void set_id_joueur(const int _id_joueur);
	void set_id(int new_id);
	void set_vies(int new_vies);
	int set_map(int X, int Y, int valeur);
	int set_map(const int ** positions, const int _valeur);
	void set_X(int nouv_x);
	void set_Y(int nouv_y);
	void set_dir(int new_dir);
	void set_pos_prec(int _X, int _Y);


private:
	int id;//Identifiant de la partie
	int vies;//Nombre de vie courante du joueur
	int ** map;//Carte de la partie
	int id_joueur;//Identifiant du joueur
	int X;//Position X du joueur
	int Y;//Position Y du joueur
	int direction;//Direction du joueur
	int taille;//Taille de la carte
	int ** pos_prec;//Matrice des positions précédentes du joueur
};
void test_jeu();
#endif // !JEU
