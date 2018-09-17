#ifndef JOUEUR
#define JOUEUR
class Joueur
{
public:
	Joueur();
	Joueur(const Joueur&);


private:
	char nom;
	int id_joueur;
	int long score;
};
#endif // !JOUEUR_H
