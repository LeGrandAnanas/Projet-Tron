// TRON.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include <iostream>

#include "SDL.h"

#include "jeu.h"
#include "Joueur.h"
#include "menuprincipal.h"

using namespace std;

int main(int argc, char * argv[])
{
	SDL_Event evenement;
	SDL_Window *window;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("TRON", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1000, SDL_WINDOW_OPENGL);
	while (1) {
		if (SDL_PollEvent(&evenement)) {
			if (evenement.type == SDL_KEYDOWN) {
				printf("Touche %s", SDL_GetKeyName(evenement.key.keysym.sym));

				switch (evenement.key.keysym.sym)
					case(SDLK_ESCAPE):
						SDL_Delay(3000);
						SDL_DestroyWindow(window);
						return 0;
			}


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
