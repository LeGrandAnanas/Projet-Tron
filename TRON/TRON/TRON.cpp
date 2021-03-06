// TRON.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include <iostream>
#include <chrono>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "SDL.h"

#include "jeu.h"
#include "Joueur.h"
#include "menuprincipal.h"



using namespace std;
using namespace std::chrono;

SDL_Event evenement;
SDL_Window *window;
SDL_AudioSpec want, have;
int direction = 0;
//srand (time(NULL));

int main(int argc, char * argv[])
{
	test_jeu();
	jeu game;
	Joueur player1;
	player1.set_nom((char)"Adrian");
	player1.set_id(10);
	player1.set_score(0);
	player1.set_couleur(1);
	game.create_map(50);
	game.set_id(1);
	game.set_id_joueur(player1.get_id_joueur());
	game.set_vies(5);
	game.set_X(500);
	game.set_Y(500);
	game.set_pos_prec(game.get_X(), game.get_Y());
	int y = game.get_Y();
	int x = game.get_X();
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	window = SDL_CreateWindow("TRON", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1000, SDL_WINDOW_OPENGL);
	while (1) {
		if (SDL_PollEvent(&evenement)) {
			if (evenement.type == SDL_KEYDOWN) {
				//printf("Touche %s", SDL_GetKeyName(evenement.key.keysym.sym));

				switch (evenement.key.keysym.sym) {
				case(SDLK_ESCAPE):
					cout << "Fin de Partie" << endl; 
					game.get_map();
					SDL_Delay(3000);
					SDL_DestroyWindow(window);
					return 0;
					break;
				case(SDLK_UP):
					cout << "UP" << endl;
					direction = 0;
					break;
				case(SDLK_DOWN):
					cout << "DOWN" << endl;
					direction = 2;
					break;
				case(SDLK_LEFT):
					cout << "LEFT" << endl;
					direction = 1;
					break;
				case(SDLK_RIGHT):
					cout << "RIGHT" << endl;
					direction = 3;
					break;
				case(SDLK_SPACE):
					cout << "SPACE" << endl;
					break;
				default:
					printf("Une touche a ete appuyee");
					break;
				}
			}
		}
		else {
			SDL_Delay(1000);
			switch (direction){//La position (x=0,y=0) est en haut à gauche de l'écran 
			case 0:y += 1;	
				break;
			case 1:x += 1;
				break;
			case 2:y -= 1;
				break;
			case 3:x -= 1;
				break;
			};
			game.set_X(x);
			game.set_Y(y);
			game.set_pos_prec(game.get_X(), game.get_Y());
			cout << "( x = " << x << " , y= " << y << " )" << endl;
			//game.get_map();
		}
	}
}

/*
//TEST SDL
int main(int argc, char * argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		cout << "SDL initialization succeeded!";
	}

	cin.get();
	return 0;
}
*/
