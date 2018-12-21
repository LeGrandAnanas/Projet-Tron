#ifndef JOUEUR
#define JOUEUR
class Joueur
{
public:
	Joueur();
	Joueur(const Joueur&);

	//Get
	char get_nom();
	int get_id_joueur();
	int get_score();
	int get_couleur();

	//Set
	void set_nom(const char new_name);
	void set_id(const int new_id);
	void set_score(int new_score);
	void set_couleur(int new_color);

private:
	char nom;
	int id_joueur;
	int long score;
	int couleur;
};
#endif // !JOUEUR_H
