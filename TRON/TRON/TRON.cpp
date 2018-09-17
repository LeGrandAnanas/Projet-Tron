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


	SDL_Window *window;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("TRON", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_OPENGL);
	SDL_Delay(3000);
	SDL_DestroyWindow(window);

	return 0;
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
