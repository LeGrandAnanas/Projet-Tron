#include "stdafx.h"

#include "jeu.h"

jeu::jeu():id(0),couleur(0),positions(0)
{
}

jeu::jeu(const jeu & J):id(J.id),couleur(J.couleur),vies(J.vies),positions(J.positions)
{
}

int jeu::get_id()
{
	return id;
}

int jeu::get_couleur()
{
	return couleur;
}

int jeu::get_vies()
{
	return vies;
}

int * jeu::get_positions_X()
{
	int * pos = new int[20];
	for (int k = 0; k < 20; k++) {
		pos[k] = positions [0] [k];
	}
	return pos;
}

int * jeu::get_positions_Y()
{
	int * pos = new int[20];
	for (int k = 0; k < 20; k++) {
		pos[k] = positions[0][k];
	}
	return pos;
}

void jeu::set_id(int new_id)
{
	id = new_id;
}

void jeu::set_couleur(int new_couleur)
{
	couleur = new_couleur;
}

void jeu::set_vies(int new_vies)
{
	vies = new_vies;
}

void jeu::set_positions(int * new_positions)
{
	for (unsigned int i = 0; i < 19; i++) {
		positions[i + 1][0] = positions[i][0];
		positions[i + 1][1] = positions[i][1];
	}
	positions[0][0] = new_positions[0];
	positions[0][1] = new_positions[1];
}

void jeu::set_dern_position(int X, int Y)
{
	for (unsigned int i = 0; i < 19; i++) {
		positions[i + 1][0] = positions[i][0];
		positions[i + 1][1] = positions[i][1];
	}
	positions[0][0] = X;
	positions[0][1] = Y;
}
