#include "stdafx.h"
#include "menuprincipal.h"

menuprincipal::menuprincipal() :nombre_element(0), pos_selectionne(0), liste_menu_suiv(0)
{
}

menuprincipal::menuprincipal(const menuprincipal & A): nombre_element(A.nombre_element), pos_selectionne(A.pos_selectionne), liste_menu_suiv(A.liste_menu_suiv)
{
}

int menuprincipal::choix_menu(const char* touche)
{
	if (touche == "UP") {
		if (pos_selectionne < 0) {
			pos_selectionne -= 1;
		}
	}
	if (touche == "DOWN") {
		if (pos_selectionne != nombre_element) {
			pos_selectionne += 1;
		}
	}
	if (touche == "SPACE") {
		return liste_menu_suiv[pos_selectionne];
	}
	return 0;
}