#pragma once
#ifndef IA
#define IA
#include "jeu.h"
//Chargement des librairies et paramétrisation de la variable random
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
//
class ia {
public:
	//CONSTRUCTEURS
	ia();
	ia(const ia &);

	//GET
	int get_ia_level();
	int get_ia_id();

	//SET
	void set_ia_level(const int _level);
	void set_ia_id(const int _id);

	//Déplacement
	int direction(const int direction_prec, jeu GAME);

private:
	int niveau;//niveau de l'IA
	int id_ia;//identifiant de l'IA

};
#endif