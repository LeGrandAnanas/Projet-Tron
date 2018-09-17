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
