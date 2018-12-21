#pragma once
#ifndef MENU_PRINCIPAL
#define MENU_PRINCIPAL
class menuprincipal {
public:
	menuprincipal();
	menuprincipal(const menuprincipal &);

	int choix_menu(const char* touche);
	
private:
	int nombre_element;
	int pos_selectionne;
	int * liste_menu_suiv;
};
#endif // !MENU_PRINCIPAL
