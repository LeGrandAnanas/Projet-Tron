#include "stdafx.h"
#include <iostream>
using namespace std;
#include "jeu.h"

jeu::jeu():id(0), vies(0),map(0),id_joueur(0),X(0),Y(0),taille(0),pos_prec(0)
{
}

jeu::jeu(const jeu & J):id(J.id),vies(J.vies),map(J.map),id_joueur(J.id_joueur),X(J.X),Y(J.Y),taille(J.taille), pos_prec(J.pos_prec)
{
}

void jeu::create_map(int _taille)
{
	taille = _taille;
	map = new int *[taille];
	for (int m = 0; m < taille; m++) {
		map[m] = new int[taille];
	}
	for (int i = 0; i < taille; i++) {
		for (int k = 0; k < taille; k++) {
			map[i][k] = 0;
		}
	}
	for (int i = 0; i < taille; i++) {
		map[0][i] = 1;
		map[taille-1][i] = 1;
		map[i][0] = 1;
		map[i][taille-1] = 1;
	}
}

int jeu::get_id()
{
	return id;
}


int jeu::get_vies()
{
	return vies;
}

void jeu::get_map()
{
	cout << endl;
	int ** tab;
	for (int i = 0; i < taille; i++) {
		for (int j = 0; j < taille; j++) {
 			cout << map[i][j]<<"  ";
		}
		cout << endl;
	}
	cout << endl;
}

int jeu::get_map_val(const int _X, const int _Y)
{
	return map[_X][_Y];
}

int jeu::get_X()
{
	return X;
}

int jeu::get_Y()
{
	return Y;
}

int jeu::get_dir()
{
	return direction;
}

int jeu::get_taille()
{
	return taille;
}

int ** jeu::get_pos_prec()
{
	return pos_prec;
}



void jeu::set_id_joueur(const int _id_joueur)
{
	id_joueur = _id_joueur;
}

void jeu::set_id(int new_id)
{
	id = new_id;
}


void jeu::set_vies(int new_vies)
{
	vies = new_vies;
}
int jeu::set_map(int X, int Y, int valeur)
{
	if (map[X][Y] == 0) {
		map[X][Y] = valeur;
		return 0;//Rien ne se passe
	}
	else {
		if (valeur == 2) {//La valeur du mur du joueur 1 est 2
			return 2;//Le joueur 2 gagne
		}
		if (valeur == 3) {//La valeur du mur du joueur 2 est 3
			return 1;//Le joueur 1 gagne
		}
	}
}
int jeu::set_map(const int ** positions,const int _valeur)
{
	int size_positions = sizeof(positions);
	for (int i = 0; i < size_positions; i++) {
		int _X = positions[i][0];
		int _Y = positions[i][1];
		int reussite= set_map(_X, _Y,_valeur);
		switch (reussite) {
			case 1:
				return 1;//Le joueur 1 gagne
				break;
			case 2:
				return 2;//Le joueur 2 gagne
				break;
		}

	}
	return 0;
}
void jeu::set_X(int nouv_x)
{
	X = nouv_x;
}
void jeu::set_Y(int nouv_y)
{
	Y = nouv_y;
}
void jeu::set_dir(int new_dir)
{
	direction = new_dir;
}

void jeu::set_pos_prec(int _X, int _Y)
{
	/*int size_pos_prec=sizeof(pos_prec);
	pos_prec[0][size_pos_prec] = _X;
	pos_prec[1][size_pos_prec] = _Y;*/
}

void test_jeu()
{
	jeu Game;
	Game.set_id(10);
	Game.set_vies(3);
	Game.create_map(51);
	Game.set_map(10, 10, 3);
	Game.set_X(10);
	Game.set_Y(10);
	Game.set_dir(1);
	cout << "id = " << Game.get_id() << " vies = " << Game.get_vies() << " X = " << Game.get_X() << " Y = " << Game.get_Y() << " dir = " << Game.get_dir() << endl;
	Game.get_map();
}
 