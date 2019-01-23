#include "stdafx.h"
#include "IA.h"


//srand((int)time(NULL));

ia::ia():niveau(0), id_ia(0)
{
}

ia::ia(const ia & I):niveau(I.niveau), id_ia(I.id_ia)
{
}

int ia::get_ia_level()
{
	return niveau;
}

int ia::get_ia_id()
{
	return id_ia;
}

void ia::set_ia_level(const int _level)
{
	niveau = _level;
}

void ia::set_ia_id(const int _id)
{
	id_ia = _id;
}

int ia::direction(const int direction_prec, jeu GAME)
{
	int X = GAME.get_X();
	int Y = GAME.get_Y();
	int X_temp = X;
	int Y_temp = Y;
	int nouv_direction = rand() % 4;
	switch (niveau){
		case 1:
			while (direction_prec == nouv_direction) {
				nouv_direction = rand() % 4;
			}
			return nouv_direction;
			break;
		case 2:
			while (GAME.get_map_val(X_temp, Y_temp) != 0) {
				while (direction_prec == nouv_direction) {
					nouv_direction = rand() % 4;
					switch (nouv_direction) {//La position (x=0,y=0) est en haut à gauche de l'écran 
						case 0:Y_temp += 1;
							break;
						case 1:X_temp += 1;
							break;
						case 2:Y_temp -= 1;
							break;
						case 3:X_temp -= 1;
							break;
					}
				}
			}
			return nouv_direction;
			break;
		case 3:
			while (GAME.get_map_val(X_temp, Y_temp) != 0) {
				while (direction_prec == nouv_direction) {
					nouv_direction = rand() % 4;
					switch (nouv_direction) {//La position (x=0,y=0) est en haut à gauche de l'écran 
					case 0:Y_temp += 1;
						break;
					case 1:X_temp += 1;
						break;
					case 2:Y_temp -= 1;
						break;
					case 3:X_temp -= 1;
						break;
					}
				}
			}
			return nouv_direction;
			break;
		default:
			while (direction_prec == nouv_direction) {
				nouv_direction = rand() % 4;
			}
			return nouv_direction;
			break;
	};
}
void test_ia() {
	ia ordi;
	ordi.set_ia_level(1);
	ordi.set_ia_id(3);

}
