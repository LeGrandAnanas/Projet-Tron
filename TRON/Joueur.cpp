#include "stdafx.h"

#include "Joueur.h"

Joueur::Joueur():
	nom(0),id_joueur(0),score(0)
{
}

Joueur::Joueur(const Joueur & J):
	nom(J.nom),id_joueur(J.id_joueur),score(J.score)
{
}

char Joueur::get_nom()
{
	return nom;
}

int Joueur::get_id_joueur()
{
	return id_joueur;
}

int Joueur::get_score()
{
	return score;
}

int Joueur::get_couleur()
{
	return couleur;
}

void Joueur::set_nom(const char new_name)
{
	nom = new_name;
}

void Joueur::set_id(const int new_id)
{
	id_joueur = new_id;
}

void Joueur::set_score(int new_score)
{
	score = new_score;
}

void Joueur::set_couleur(int new_color)
{
	couleur = new_color;
}
