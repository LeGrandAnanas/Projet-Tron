#include <string>
#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>

#include "res_path.h"
#include "cleanup.h"

#include "Map.h"
#include "Mob.h"
#include "Mob2.h"


const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const int TILE_SIZE = 40;


void logSDLError(std::ostream &os, const std::string &msg) {
	os << msg << " error: " << SDL_GetError() << std::endl;
}
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren) {
	SDL_Texture *texture = nullptr;
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	if (loadedImage != nullptr) {
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		if (texture == nullptr) {
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

int main(int, char**) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}
	SDL_Window *window = SDL_CreateWindow("Pac Man", 250, 50, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}

	int r = 0;
	Mob pac;
	Mob pac2;
	Mob pac3;
	Mob pac4;
	Mob pac5;
	Mob pac6;

	pac.SetX(18);
	pac.SetY(18);
	pac2.SetX(972);
	pac2.SetY(774);

	pac.SetDir(2);
	pac2.SetDir(8);

	pac.SetTemp(0);
	pac2.SetTemp(0);
	
	pac3.SetX(72);
	pac3.SetY(72);
	pac4.SetX(918);
	pac4.SetY(720);

	pac3.SetDir(2);
	pac4.SetDir(8);

	pac3.SetTemp(0);
	pac4.SetTemp(0);

	const std::string resPath = getResourcePath("Pac Man");
	SDL_Texture *background = loadTexture("img/background.bmp", renderer);
	SDL_Texture *pacmanRO = loadTexture(pac.GetPathRO(), renderer);
	SDL_Texture *pacmanRC = loadTexture(pac.GetPathRC(), renderer);
	SDL_Texture *pacmanLO = loadTexture(pac.GetPathLO(), renderer);
	SDL_Texture *pacmanLC = loadTexture(pac.GetPathLC(), renderer);
	SDL_Texture *pacmanUO = loadTexture(pac.GetPathUO(), renderer);
	SDL_Texture *pacmanUC = loadTexture(pac.GetPathUC(), renderer);
	SDL_Texture *pacmanDO = loadTexture("img/motorouged.bmp", renderer);
	SDL_Texture *pacmanDvert = loadTexture("img/motovertd.bmp", renderer);
	SDL_Texture *pacmanDC = loadTexture(pac.GetPathDC(), renderer);
	SDL_Texture *point = loadTexture("img/point.bmp", renderer);
	SDL_Texture *grospoint = loadTexture("img/grospoint.bmp", renderer);
	SDL_Texture *menu = loadTexture("img/menu.bmp", renderer);
	SDL_Texture *press = loadTexture("img/press.bmp", renderer);
	SDL_Texture *paspress = loadTexture("img/paspress.bmp", renderer);
	SDL_Texture *menuprin = loadTexture("img/menuprin.bmp", renderer);
	SDL_Texture *rouge = loadTexture("img/rouge.bmp", renderer);
	SDL_Texture *rougeret = loadTexture("img/rougeret.bmp", renderer);
	SDL_Texture *vert = loadTexture("img/vert.bmp", renderer);
	SDL_Texture *vertret = loadTexture("img/vertret.bmp", renderer);
	SDL_Texture *v1 = loadTexture("img/1v.bmp", renderer);
	SDL_Texture *v2 = loadTexture("img/2v.bmp", renderer);
	SDL_Texture *u0 = loadTexture("img/0.bmp", renderer);



	if (background == nullptr || pacmanLC == nullptr || pacmanLO == nullptr || pacmanRC == nullptr || pacmanRO == nullptr || point == nullptr) {
		cleanup(background, pacmanRO, pacmanRC, pacmanLO, pacmanLC, point, renderer, window);
		SDL_Quit();
		return 1;
	}
	bool quit = false;
	SDL_Event e;
	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
	float XCaseSize = (SCREEN_WIDTH - 35) / 29, YCaseSize = (SCREEN_HEIGHT - 31) / 26;
	int touchmem = 0, score = 0, mange = 0, beg = 1, pok_start = 0, spe_start = 0, shaPosX = 0, shaPosY = 0, pacPosX = 0, pacPosY = 0, pac2PosX = 0, pac2PosY = 0, spePosX = 0, spePosY = 0, pokPosX = 0, pokPosY = 0;
	bool run = true;
	int iW, iH, diz = 0, cent = 0, mil = 0, vul = 0, vulCount = 0, MobEat = 0;
	int carte[31][28] = {
					{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
					{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
	};
	time_t timer1;
	time_t timer2;
	double seconds;
	time(&timer1);
	int abstime = 0;
	int start = 0;
	int startmenu = 0;
	int joueur = 1;
	int niveau = 1;
	int scores[300];
	
	string noms[300];
	string tab2[300];
	int scorei = 0;
	int scoreimod = 0;
	int menuscores = 0;
	int tmp;
	string tmp2;
	int jeu = 0;

	while (true) {
		if (r == 0) {
			if (start == 0) {
				SDL_QueryTexture(menu, NULL, NULL, 0, 0);
				renderTexture(menu, renderer, 150, 150);
				start = 1;
			}
			SDL_QueryTexture(press, NULL, NULL, 0, 0);
			






			


			pac.ChangeTemp(pac.GetY() - 1,pac.GetY() + 1, pac.GetX() - 1, pac.GetX() + 1, vul);
			
			
			pac2.ChangeTemp(pac2.GetY() - 1,pac2.GetY() + 1, pac2.GetX() - 1, pac2.GetX() + 1, vul);
			
			


			//Clear the window

			//Draw our image in the center of the window
			//We need the foreground image's width to properly compute the position
			//of it's top left corner so that the image will be centered


				/******* Changement X, Y pacman ***************/
			if (!pac.GetTemp())
				pac.PosChange(pac.GetY() - 1,pac.GetY() + 1, pac.GetX() - 1,pac.GetX() + 1);
			if (!pac2.GetTemp())
				pac2.PosChange(pac2.GetY() - 1,pac2.GetY() + 1,pac2.GetX() - 1, pac2.GetX() + 1);
		
			









			if (pac.GetDir() == 6)
			{
				SDL_QueryTexture(pacmanRO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanRO, renderer, pac.GetX() + pac.GetTemp(), pac.GetY());
				if (pac.GetX() >= 54) {
					SDL_QueryTexture(rougeret, NULL, NULL, &iW, &iH);
					renderTexture(rougeret, renderer, pac.GetX() + pac.GetTemp() - 18, pac.GetY());
				}
			}

			else if (pac.GetDir() == 4)
			{
				SDL_QueryTexture(pacmanLO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanLO, renderer, pac.GetX() + pac.GetTemp(), pac.GetY());
				if (pac.GetX() <= 936) {
					SDL_QueryTexture(rougeret, NULL, NULL, &iW, &iH);
					renderTexture(rougeret, renderer, pac.GetX() + pac.GetTemp() + 18, pac.GetY());
				}
			}

			else if (pac.GetDir() == 8)
			{
				SDL_QueryTexture(pacmanUO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanUO, renderer, pac.GetX(), pac.GetY() + pac.GetTemp());
				if (pac.GetY() <= 738) {
					SDL_QueryTexture(rouge, NULL, NULL, &iW, &iH);
					renderTexture(rouge, renderer, pac.GetX() - 3, pac.GetY() + pac.GetTemp() + 18);
				}
			}

			else if (pac.GetDir() == 2)
			{
				SDL_QueryTexture(pacmanDO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanDO, renderer, pac.GetX(), pac.GetY() + pac.GetTemp());
				if (pac.GetY() >= 54) {
					SDL_QueryTexture(rouge, NULL, NULL, &iW, &iH);
					renderTexture(rouge, renderer, pac.GetX() - 3, pac.GetY() + pac.GetTemp() - 18);
				}
			}


			if (pac2.GetDir() == 6)
			{
				SDL_QueryTexture(pacmanRO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanRO, renderer, pac2.GetX() + pac2.GetTemp(),  pac2.GetY());
				if (pac2.GetX() >= 54) {
					SDL_QueryTexture(vertret, NULL, NULL, &iW, &iH);
					renderTexture(vertret, renderer, pac2.GetX() + pac2.GetTemp()-18, pac2.GetY());
				}
			}

			else if (pac2.GetDir() == 4)
			{
				SDL_QueryTexture(pacmanLO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanLO, renderer, pac2.GetX() + pac2.GetTemp(), pac2.GetY());
				if (pac2.GetX() <= 936) {
					SDL_QueryTexture(vertret, NULL, NULL, &iW, &iH);
					renderTexture(vertret, renderer, pac2.GetX() + pac2.GetTemp()+18, pac2.GetY());
				}
			}

			else if (pac2.GetDir() == 8)
			{
				SDL_QueryTexture(pacmanUO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanUO, renderer,  pac2.GetX()  ,  pac2.GetY()  + pac2.GetTemp());
				if (pac2.GetY() <= 738) {
					SDL_QueryTexture(vert, NULL, NULL, &iW, &iH);
					renderTexture(vert, renderer, pac2.GetX() - 3, pac2.GetY() + pac2.GetTemp() + 18);
				}
			}

			else if (pac2.GetDir() == 2)
			{
				SDL_QueryTexture(pacmanDvert, NULL, NULL, &iW, &iH);
				renderTexture(pacmanDvert, renderer, pac2.GetX(), pac2.GetY() + pac2.GetTemp());
				if (pac2.GetY() >= 54) {
					SDL_QueryTexture(vert, NULL, NULL, &iW, &iH);
					renderTexture(vert, renderer, pac2.GetX() - 3, pac2.GetY() + pac2.GetTemp() - 18);
				}
			}

			if ((pac.GetX() >= 972) && (pac.GetY() <= 18)) {
				pac.SetDir(4);
			}
			if ((pac.GetX() <= 18) && (pac.GetY() <= 18)) {
				pac.SetDir(2);
			}
			if ((pac.GetX() <= 18) && (pac.GetY() >= 774)) {
				pac.SetDir(6);
			}
			if ((pac.GetX() >= 972) && (pac.GetY() >= 774)) {
				pac.SetDir(8);
			}

			if ((pac2.GetX() >= 972)&&(pac2.GetY()<=18)) {
				pac2.SetDir(4);
			}
			if ((pac2.GetX() <= 18) && (pac2.GetY() <= 18)) {
				pac2.SetDir(2);
			}
			if ((pac2.GetX() <= 18) && (pac2.GetY() >= 774)) {
				pac2.SetDir(6);
			}
			if ((pac2.GetX() >= 972) && (pac2.GetY() >= 774)) {
				pac2.SetDir(8);
			}



			pac3.ChangeTemp(pac3.GetY() - 1, pac3.GetY() + 1, pac3.GetX() - 1, pac3.GetX() + 1, vul);


			pac4.ChangeTemp(pac4.GetY() - 1, pac4.GetY() + 1, pac4.GetX() - 1, pac4.GetX() + 1, vul);




			//Clear the window

			//Draw our image in the center of the window
			//We need the foreground image's width to properly compute the position
			//of it's top left corner so that the image will be centered


				/******* Changement X, Y pac3man ***************/
			if (!pac3.GetTemp())
				pac3.PosChange(pac3.GetY() - 1, pac3.GetY() + 1, pac3.GetX() - 1, pac3.GetX() + 1);
			if (!pac4.GetTemp())
				pac4.PosChange(pac4.GetY() - 1, pac4.GetY() + 1, pac4.GetX() - 1, pac4.GetX() + 1);











			if (pac3.GetDir() == 6)
			{
				SDL_QueryTexture(pacmanRO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanRO, renderer, pac3.GetX() + pac3.GetTemp(), pac3.GetY());
				if (pac3.GetX() >= 108) {
					SDL_QueryTexture(rougeret, NULL, NULL, &iW, &iH);
					renderTexture(rougeret, renderer, pac3.GetX() + pac3.GetTemp() - 18, pac3.GetY());
				}
			}

			else if (pac3.GetDir() == 4)
			{
				SDL_QueryTexture(pacmanLO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanLO, renderer, pac3.GetX() + pac3.GetTemp(), pac3.GetY());
				if (pac3.GetX() <= 882) {
					SDL_QueryTexture(rougeret, NULL, NULL, &iW, &iH);
					renderTexture(rougeret, renderer, pac3.GetX() + pac3.GetTemp() + 18, pac3.GetY());
				}
			}

			else if (pac3.GetDir() == 8)
			{
				SDL_QueryTexture(pacmanUO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanUO, renderer, pac3.GetX(), pac3.GetY() + pac3.GetTemp());
				if (pac3.GetY() <= 684) {
					SDL_QueryTexture(rouge, NULL, NULL, &iW, &iH);
					renderTexture(rouge, renderer, pac3.GetX() - 3, pac3.GetY() + pac3.GetTemp() + 18);
				}
			}

			else if (pac3.GetDir() == 2)
			{
				SDL_QueryTexture(pacmanDO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanDO, renderer, pac3.GetX(), pac3.GetY() + pac3.GetTemp());
				if (pac3.GetY() >= 108) {
					SDL_QueryTexture(rouge, NULL, NULL, &iW, &iH);
					renderTexture(rouge, renderer, pac3.GetX() - 3, pac3.GetY() + pac3.GetTemp() - 18);
				}
			}


			if (pac4.GetDir() == 6)
			{
				SDL_QueryTexture(pacmanRO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanRO, renderer, pac4.GetX() + pac4.GetTemp(), pac4.GetY());
				if (pac4.GetX() >= 108) {
					SDL_QueryTexture(vertret, NULL, NULL, &iW, &iH);
					renderTexture(vertret, renderer, pac4.GetX() + pac4.GetTemp() - 18, pac4.GetY());
				}
			}

			else if (pac4.GetDir() == 4)
			{
				SDL_QueryTexture(pacmanLO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanLO, renderer, pac4.GetX() + pac4.GetTemp(), pac4.GetY());
				if (pac4.GetX() <= 882) {
					SDL_QueryTexture(vertret, NULL, NULL, &iW, &iH);
					renderTexture(vertret, renderer, pac4.GetX() + pac4.GetTemp() + 18, pac4.GetY());
				}
			}

			else if (pac4.GetDir() == 8)
			{
				SDL_QueryTexture(pacmanUO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanUO, renderer, pac4.GetX(), pac4.GetY() + pac4.GetTemp());
				if (pac4.GetY() <= 684) {
					SDL_QueryTexture(vert, NULL, NULL, &iW, &iH);
					renderTexture(vert, renderer, pac4.GetX() - 3, pac4.GetY() + pac4.GetTemp() + 18);
				}
			}

			else if (pac4.GetDir() == 2)
			{
				SDL_QueryTexture(pacmanDvert, NULL, NULL, &iW, &iH);
				renderTexture(pacmanDvert, renderer, pac4.GetX(), pac4.GetY() + pac4.GetTemp());
				if (pac4.GetY() >= 108) {
					SDL_QueryTexture(vert, NULL, NULL, &iW, &iH);
					renderTexture(vert, renderer, pac4.GetX() - 3, pac4.GetY() + pac4.GetTemp() - 18);
				}
			}

			if ((pac3.GetX() >= 918) && (pac3.GetY() <= 72)) {
				pac3.SetDir(4);
			}
			if ((pac3.GetX() <= 72) && (pac3.GetY() <= 72)) {
				pac3.SetDir(2);
			}
			if ((pac3.GetX() <= 72) && (pac3.GetY() >= 720)) {
				pac3.SetDir(6);
			}
			if ((pac3.GetX() >= 918) && (pac3.GetY() >= 720)) {
				pac3.SetDir(8);
			}

			if ((pac4.GetX() >= 918) && (pac4.GetY() <= 72)) {
				pac4.SetDir(4);
			}
			if ((pac4.GetX() <= 72) && (pac4.GetY() <= 72)) {
				pac4.SetDir(2);
			}
			if ((pac4.GetX() <= 72) && (pac4.GetY() >= 720)) {
				pac4.SetDir(6);
			}
			if ((pac4.GetX() >= 918) && (pac4.GetY() >= 720)) {
				pac4.SetDir(8);
			}

			time(&timer2);
			seconds = difftime(timer2, timer1);
			if (((seconds - abstime) >= 1) && (abstime % 2 == 1) || abstime == 0) {
				abstime++;
				renderTexture(paspress, renderer, 300, 500);
			}
			if (((seconds - abstime) >= 1) && (abstime % 2 == 0)) {
				renderTexture(press, renderer, 300, 500);
				abstime++;
			}
			std::cout << seconds << " " << abstime << endl;
			SDL_RenderPresent(renderer);

			while (SDL_PollEvent(&e) || !run)
			{
				if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
					quit = true;
				if (e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_SPACE:
						r = 1;
						break;
					}
				}
			}
		}

		if (r == 1) {
			if (startmenu == 0) {
				SDL_QueryTexture(menuprin, NULL, NULL, 0, 0);
				renderTexture(menuprin, renderer, 0, 0);
				startmenu = 1;
			}

			pac.ChangeTemp(pac.GetY() - 1, pac.GetY() + 1, pac.GetX() - 1, pac.GetX() + 1, vul);


			pac2.ChangeTemp(pac2.GetY() - 1, pac2.GetY() + 1, pac2.GetX() - 1, pac2.GetX() + 1, vul);




			//Clear the window

			//Draw our image in the center of the window
			//We need the foreground image's width to properly compute the position
			//of it's top left corner so that the image will be centered


				/******* Changement X, Y pacman ***************/
			if (!pac.GetTemp())
				pac.PosChange(pac.GetY() - 1, pac.GetY() + 1, pac.GetX() - 1, pac.GetX() + 1);
			if (!pac2.GetTemp())
				pac2.PosChange(pac2.GetY() - 1, pac2.GetY() + 1, pac2.GetX() - 1, pac2.GetX() + 1);











			if (pac.GetDir() == 6)
			{
				SDL_QueryTexture(pacmanRO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanRO, renderer, pac.GetX() + pac.GetTemp(), pac.GetY());
				if (pac.GetX() >= 54) {
					SDL_QueryTexture(rougeret, NULL, NULL, &iW, &iH);
					renderTexture(rougeret, renderer, pac.GetX() + pac.GetTemp() - 18, pac.GetY());
				}
			}

			else if (pac.GetDir() == 4)
			{
				SDL_QueryTexture(pacmanLO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanLO, renderer, pac.GetX() + pac.GetTemp(), pac.GetY());
				if (pac.GetX() <= 936) {
					SDL_QueryTexture(rougeret, NULL, NULL, &iW, &iH);
					renderTexture(rougeret, renderer, pac.GetX() + pac.GetTemp() + 18, pac.GetY());
				}
			}

			else if (pac.GetDir() == 8)
			{
				SDL_QueryTexture(pacmanUO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanUO, renderer, pac.GetX(), pac.GetY() + pac.GetTemp());
				if (pac.GetY() <= 738) {
					SDL_QueryTexture(rouge, NULL, NULL, &iW, &iH);
					renderTexture(rouge, renderer, pac.GetX() - 3, pac.GetY() + pac.GetTemp() + 18);
				}
			}

			else if (pac.GetDir() == 2)
			{
				SDL_QueryTexture(pacmanDO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanDO, renderer, pac.GetX(), pac.GetY() + pac.GetTemp());
				if (pac.GetY() >= 54) {
					SDL_QueryTexture(rouge, NULL, NULL, &iW, &iH);
					renderTexture(rouge, renderer, pac.GetX() - 3, pac.GetY() + pac.GetTemp() - 18);
				}
			}


			if (pac2.GetDir() == 6)
			{
				SDL_QueryTexture(pacmanRO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanRO, renderer, pac2.GetX() + pac2.GetTemp(), pac2.GetY());
				if (pac2.GetX() >= 54) {
					SDL_QueryTexture(vertret, NULL, NULL, &iW, &iH);
					renderTexture(vertret, renderer, pac2.GetX() + pac2.GetTemp() - 18, pac2.GetY());
				}
			}

			else if (pac2.GetDir() == 4)
			{
				SDL_QueryTexture(pacmanLO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanLO, renderer, pac2.GetX() + pac2.GetTemp(), pac2.GetY());
				if (pac2.GetX() <= 936) {
					SDL_QueryTexture(vertret, NULL, NULL, &iW, &iH);
					renderTexture(vertret, renderer, pac2.GetX() + pac2.GetTemp() + 18, pac2.GetY());
				}
			}

			else if (pac2.GetDir() == 8)
			{
				SDL_QueryTexture(pacmanUO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanUO, renderer, pac2.GetX(), pac2.GetY() + pac2.GetTemp());
				if (pac2.GetY() <= 738) {
					SDL_QueryTexture(vert, NULL, NULL, &iW, &iH);
					renderTexture(vert, renderer, pac2.GetX() - 3, pac2.GetY() + pac2.GetTemp() + 18);
				}
			}

			else if (pac2.GetDir() == 2)
			{
				SDL_QueryTexture(pacmanDvert, NULL, NULL, &iW, &iH);
				renderTexture(pacmanDvert, renderer, pac2.GetX(), pac2.GetY() + pac2.GetTemp());
				if (pac2.GetY() >= 54) {
					SDL_QueryTexture(vert, NULL, NULL, &iW, &iH);
					renderTexture(vert, renderer, pac2.GetX() - 3, pac2.GetY() + pac2.GetTemp() - 18);
				}
			}

			if ((pac.GetX() >= 972) && (pac.GetY() <= 18)) {
				pac.SetDir(4);
			}
			if ((pac.GetX() <= 18) && (pac.GetY() <= 18)) {
				pac.SetDir(2);
			}
			if ((pac.GetX() <= 18) && (pac.GetY() >= 774)) {
				pac.SetDir(6);
			}
			if ((pac.GetX() >= 972) && (pac.GetY() >= 774)) {
				pac.SetDir(8);
			}

			if ((pac2.GetX() >= 972) && (pac2.GetY() <= 18)) {
				pac2.SetDir(4);
			}
			if ((pac2.GetX() <= 18) && (pac2.GetY() <= 18)) {
				pac2.SetDir(2);
			}
			if ((pac2.GetX() <= 18) && (pac2.GetY() >= 774)) {
				pac2.SetDir(6);
			}
			if ((pac2.GetX() >= 972) && (pac2.GetY() >= 774)) {
				pac2.SetDir(8);
			}



			pac3.ChangeTemp(pac3.GetY() - 1, pac3.GetY() + 1, pac3.GetX() - 1, pac3.GetX() + 1, vul);


			pac4.ChangeTemp(pac4.GetY() - 1, pac4.GetY() + 1, pac4.GetX() - 1, pac4.GetX() + 1, vul);




			//Clear the window

			//Draw our image in the center of the window
			//We need the foreground image's width to properly compute the position
			//of it's top left corner so that the image will be centered


				/******* Changement X, Y pac3man ***************/
			if (!pac3.GetTemp())
				pac3.PosChange(pac3.GetY() - 1, pac3.GetY() + 1, pac3.GetX() - 1, pac3.GetX() + 1);
			if (!pac4.GetTemp())
				pac4.PosChange(pac4.GetY() - 1, pac4.GetY() + 1, pac4.GetX() - 1, pac4.GetX() + 1);











			if (pac3.GetDir() == 6)
			{
				SDL_QueryTexture(pacmanRO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanRO, renderer, pac3.GetX() + pac3.GetTemp(), pac3.GetY());
				if (pac3.GetX() >= 108) {
					SDL_QueryTexture(rougeret, NULL, NULL, &iW, &iH);
					renderTexture(rougeret, renderer, pac3.GetX() + pac3.GetTemp() - 18, pac3.GetY());
				}
			}

			else if (pac3.GetDir() == 4)
			{
				SDL_QueryTexture(pacmanLO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanLO, renderer, pac3.GetX() + pac3.GetTemp(), pac3.GetY());
				if (pac3.GetX() <= 882) {
					SDL_QueryTexture(rougeret, NULL, NULL, &iW, &iH);
					renderTexture(rougeret, renderer, pac3.GetX() + pac3.GetTemp() + 18, pac3.GetY());
				}
			}

			else if (pac3.GetDir() == 8)
			{
				SDL_QueryTexture(pacmanUO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanUO, renderer, pac3.GetX(), pac3.GetY() + pac3.GetTemp());
				if (pac3.GetY() <= 684) {
					SDL_QueryTexture(rouge, NULL, NULL, &iW, &iH);
					renderTexture(rouge, renderer, pac3.GetX() - 3, pac3.GetY() + pac3.GetTemp() + 18);
				}
			}

			else if (pac3.GetDir() == 2)
			{
				SDL_QueryTexture(pacmanDO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanDO, renderer, pac3.GetX(), pac3.GetY() + pac3.GetTemp());
				if (pac3.GetY() >= 108) {
					SDL_QueryTexture(rouge, NULL, NULL, &iW, &iH);
					renderTexture(rouge, renderer, pac3.GetX() - 3, pac3.GetY() + pac3.GetTemp() - 18);
				}
			}


			if (pac4.GetDir() == 6)
			{
				SDL_QueryTexture(pacmanRO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanRO, renderer, pac4.GetX() + pac4.GetTemp(), pac4.GetY());
				if (pac4.GetX() >= 108) {
					SDL_QueryTexture(vertret, NULL, NULL, &iW, &iH);
					renderTexture(vertret, renderer, pac4.GetX() + pac4.GetTemp() - 18, pac4.GetY());
				}
			}

			else if (pac4.GetDir() == 4)
			{
				SDL_QueryTexture(pacmanLO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanLO, renderer, pac4.GetX() + pac4.GetTemp(), pac4.GetY());
				if (pac4.GetX() <= 882) {
					SDL_QueryTexture(vertret, NULL, NULL, &iW, &iH);
					renderTexture(vertret, renderer, pac4.GetX() + pac4.GetTemp() + 18, pac4.GetY());
				}
			}

			else if (pac4.GetDir() == 8)
			{
				SDL_QueryTexture(pacmanUO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanUO, renderer, pac4.GetX(), pac4.GetY() + pac4.GetTemp());
				if (pac4.GetY() <= 684) {
					SDL_QueryTexture(vert, NULL, NULL, &iW, &iH);
					renderTexture(vert, renderer, pac4.GetX() - 3, pac4.GetY() + pac4.GetTemp() + 18);
				}
			}

			else if (pac4.GetDir() == 2)
			{
				SDL_QueryTexture(pacmanDvert, NULL, NULL, &iW, &iH);
				renderTexture(pacmanDvert, renderer, pac4.GetX(), pac4.GetY() + pac4.GetTemp());
				if (pac4.GetY() >= 108) {
					SDL_QueryTexture(vert, NULL, NULL, &iW, &iH);
					renderTexture(vert, renderer, pac4.GetX() - 3, pac4.GetY() + pac4.GetTemp() - 18);
				}
			}

			if ((pac3.GetX() >= 918) && (pac3.GetY() <= 72)) {
				pac3.SetDir(4);
			}
			if ((pac3.GetX() <= 72) && (pac3.GetY() <= 72)) {
				pac3.SetDir(2);
			}
			if ((pac3.GetX() <= 72) && (pac3.GetY() >= 720)) {
				pac3.SetDir(6);
			}
			if ((pac3.GetX() >= 918) && (pac3.GetY() >= 720)) {
				pac3.SetDir(8);
			}

			if ((pac4.GetX() >= 918) && (pac4.GetY() <= 72)) {
				pac4.SetDir(4);
			}
			if ((pac4.GetX() <= 72) && (pac4.GetY() <= 72)) {
				pac4.SetDir(2);
			}
			if ((pac4.GetX() <= 72) && (pac4.GetY() >= 720)) {
				pac4.SetDir(6);
			}
			if ((pac4.GetX() >= 918) && (pac4.GetY() >= 720)) {
				pac4.SetDir(8);
			}

			SDL_RenderPresent(renderer);

			while (SDL_PollEvent(&e) || !run)
			{
				if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
					quit = true;
				if (e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_1:
						r = 2;
						break;
					case SDLK_2:
						r = 3;
						break;
					case SDLK_3:
						joueur = (joueur + 1) % 5;;
						if (joueur == 0) {
							joueur++;
							SDL_QueryTexture(v1, NULL, NULL, &iW, &iH);
							renderTexture(v1, renderer, 589, 565);
						}
						if (joueur == 2) {

							SDL_QueryTexture(v2, NULL, NULL, &iW, &iH);
							renderTexture(v2, renderer, 589, 565);
						}
						SDL_RenderPresent(renderer);
						break;
					

					case SDLK_4:
						niveau = (niveau + 1) % 10;;
						if (niveau == 0) {
							niveau++;
							SDL_QueryTexture(v1, NULL, NULL, &iW, &iH);
							renderTexture(v1, renderer,580,624);
						}
						if (niveau == 2) {
							
							SDL_QueryTexture(v2, NULL, NULL, &iW, &iH);
							renderTexture(v2, renderer, 580,624);
						}
						SDL_RenderPresent(renderer);
						break;
					}
					
				}
			}
		}

		if (r == 2) {
			if (beg == 2)
			{
				SDL_Delay(2000);
				beg++;
				run = 1;
			}
			if (beg == 1)
			{
				vul = 0;
				vulCount = 0;
				pac6.SetX(13);
				pac6.SetY(23);
				pac5.SetX(13);
				pac5.SetY(7);

				pac6.SetDir(4);
				pac5.SetDir(4);

				pac6.SetTemp(0);
				pac5.SetTemp(0);

				beg++;
				if (!pac6.GetLives())
					pac6.SetLives(3);
				if (!pac5.GetLives())
					pac5.SetLives(3);
			}
			if (beg > 2 && beg < 100)
			{
				beg++;
			}
			if (beg > 2) /****** CHANGE TEMP *****/
			{
				pac6.ChangeTemp(carte[pac6.GetY() - 1][pac6.GetX()], carte[pac6.GetY() + 1][pac6.GetX()], carte[pac6.GetY()][pac6.GetX() - 1], carte[pac6.GetY()][pac6.GetX() + 1], vul);
				pac6.SetBouche((pac6.GetBouche() + 1) % 10);
				pac5.ChangeTemp(carte[pac5.GetY() - 1][pac5.GetX()], carte[pac5.GetY() + 1][pac5.GetX()], carte[pac5.GetY()][pac5.GetX() - 1], carte[pac5.GetY()][pac5.GetX() + 1], vul);
				pac5.SetBouche((pac5.GetBouche() + 1) % 10);
			}
			if (vul)
				vulCount++;
			if (vulCount > 550)
			{
				vul = 0;
				vulCount = 0;
				MobEat = 0;

			}
			//Clear the window
			SDL_RenderClear(renderer);

			//Get the width and height from the texture so we know how much to move x,y by
			//to tile it correctly
			SDL_QueryTexture(background, NULL, NULL, 0, 0);
			//We want to tile our background so draw it 4 times
			renderTexture(background, renderer, 0, 0);
			for (int i = 0; i < 30; i++)
			{
				for (int j = 0; j < 28; j++)
				{
					if (carte[i][j] == 1)
					{
						SDL_QueryTexture(point, NULL, NULL, 0, 0);
						renderTexture(point, renderer, 200 + j * 22 + 8, 150 + i * 18);
					}
					else if (carte[i][j] == 3)
					{
						SDL_QueryTexture(grospoint, NULL, NULL, 0, 0);
						renderTexture(grospoint, renderer, 200 + j * 22 + 8, 150 + i * 18);
					}
					else if (carte[i][j] == 2)
					{
						SDL_QueryTexture(point, NULL, NULL, 0, 0);
						renderTexture(grospoint, renderer, 200 + j * 22 + 8, 150 + i * 18);
					}
				}
			}

			//Draw our image in the center of the window
			//We need the foreground image's width to properly compute the position
			//of it's top left corner so that the image will be centered
			if (beg > 2)
			{
				/******* Changement X, Y pac6man ***************/
				if (!pac6.GetTemp())
					pac6.PosChange2(carte[pac6.GetY() - 1][pac6.GetX()], carte[pac6.GetY() + 1][pac6.GetX()], carte[pac6.GetY()][pac6.GetX() - 1], carte[pac6.GetY()][pac6.GetX() + 1]);
				if (!pac5.GetTemp())
					pac5.PosChange2(carte[pac5.GetY() - 1][pac5.GetX()], carte[pac5.GetY() + 1][pac5.GetX()], carte[pac5.GetY()][pac5.GetX() - 1], carte[pac5.GetY()][pac5.GetX() + 1]);
				if (pac6.GetX() == 0 && pac6.GetY() == 14 && pac6.GetTemp() <= 0 && pac6.GetDir() == 4)
				{
					pac6.SetX(27);
					pac6.SetTemp(0);
				}
				if (pac5.GetX() == 0 && pac5.GetY() == 14 && pac5.GetTemp() <= 0 && pac5.GetDir() == 4)
				{
					pac5.SetX(27);
					pac5.SetTemp(0);
				}
				if (pac6.GetX() == 27 && pac6.GetY() == 14 && pac6.GetTemp() >= 0 && pac6.GetDir() == 6)
				{
					pac6.SetX(0);
					pac6.SetTemp(0);
				}


			}

			if (pac6.GetDir() == 4 || pac6.GetDir() == 6)
			{
				pacPosX = pac6.GetX() * 18 + pac6.GetTemp();
				pacPosY = pac6.GetY() * 22;
			}
			else
			{
				pacPosX = pac6.GetX() * 18;
				pacPosY = pac6.GetY() * 22 + pac6.GetTemp();

			}

			if (pac5.GetDir() == 4 || pac5.GetDir() == 6)
			{
				pacPosX = pac5.GetX() * 18 + pac5.GetTemp();
				pacPosY = pac5.GetY() * 22;
			}
			else
			{
				pacPosX = pac5.GetX() * 18;
				pacPosY = pac5.GetY() * 22 + pac5.GetTemp();

			}




			if (carte[pac6.GetY()][pac6.GetX()] == 1)
			{
				carte[pac6.GetY()][pac6.GetX()] = 2;


			}
			else if (carte[pac6.GetY()][pac6.GetX()] == 2)
			{
				carte[pac6.GetY()][pac6.GetX()] = 2;
			}

			if (carte[pac5.GetY()][pac5.GetX()] == 1)
			{
				carte[pac5.GetY()][pac5.GetX()] = 1;


			}
			else if (carte[pac5.GetY()][pac5.GetX()] == 2)
			{
				carte[pac5.GetY()][pac5.GetX()] = 1;
				r = 0;
			}


			if (pac6.GetBouche() < 5 && pac6.GetDir() == 6)
			{
				SDL_QueryTexture(pacmanRO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanRO, renderer, 200 + pac6.GetX() * 22 + 9 + pac6.GetTemp(), 150 + pac6.GetY() * 18);
			}
			else if (pac6.GetBouche() >= 5 && pac6.GetDir() == 6)
			{
				SDL_QueryTexture(pacmanRC, NULL, NULL, &iW, &iH);
				renderTexture(pacmanRC, renderer, 200 + pac6.GetX() * 22 + 9 + pac6.GetTemp(), 150 + pac6.GetY() * 18);
			}
			else if (pac6.GetDir() == 4 && pac6.GetBouche() < 5)
			{
				SDL_QueryTexture(pacmanLO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanLO, renderer, 200 + pac6.GetX() * 22 + 9 + pac6.GetTemp(), 150 + pac6.GetY() * 18);
			}
			else if (pac6.GetDir() == 4 && pac6.GetBouche() >= 5)
			{
				SDL_QueryTexture(pacmanLC, NULL, NULL, &iW, &iH);
				renderTexture(pacmanLC, renderer, 200 + pac6.GetX() * 22 + 9 + pac6.GetTemp(), 150 + pac6.GetY() * 18);
			}
			else if (pac6.GetDir() == 8 && pac6.GetBouche() < 5)
			{
				SDL_QueryTexture(pacmanUO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanUO, renderer, 200 + pac6.GetX() * 22 + 9, 150 + pac6.GetY() * 18 + pac6.GetTemp());
			}
			else if (pac6.GetDir() == 8 && pac6.GetBouche() >= 5)
			{
				SDL_QueryTexture(pacmanUC, NULL, NULL, &iW, &iH);
				renderTexture(pacmanUC, renderer, 200 + pac6.GetX() * 22 + 9, 150 + pac6.GetY() * 18 + pac6.GetTemp());
			}
			else if (pac6.GetDir() == 2 && pac6.GetBouche() < 5)
			{
				SDL_QueryTexture(pacmanDO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanDO, renderer, 200 + pac6.GetX() * 22 + 9, 150 + pac6.GetY() * 18 + pac6.GetTemp());
			}
			else if (pac6.GetDir() == 2 && pac6.GetBouche() >= 5)
			{
				SDL_QueryTexture(pacmanDC, NULL, NULL, &iW, &iH);
				renderTexture(pacmanDC, renderer, 200 + pac6.GetX() * 22 + 9, 150 + pac6.GetY() * 18 + pac6.GetTemp());
			}

			if (pac5.GetBouche() < 5 && pac5.GetDir() == 6)
			{
				SDL_QueryTexture(pacmanRO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanRO, renderer, 200 + pac5.GetX() * 22 + 9 + pac5.GetTemp(), 150 + pac5.GetY() * 18);
			}
			else if (pac5.GetBouche() >= 5 && pac5.GetDir() == 6)
			{
				SDL_QueryTexture(pacmanRC, NULL, NULL, &iW, &iH);
				renderTexture(pacmanRC, renderer, 200 + pac5.GetX() * 22 + 9 + pac5.GetTemp(), 150 + pac5.GetY() * 18);
			}
			else if (pac5.GetDir() == 4 && pac5.GetBouche() < 5)
			{
				SDL_QueryTexture(pacmanLO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanLO, renderer, 200 + pac5.GetX() * 22 + 9 + pac5.GetTemp(), 150 + pac5.GetY() * 18);
			}
			else if (pac5.GetDir() == 4 && pac5.GetBouche() >= 5)
			{
				SDL_QueryTexture(pacmanLC, NULL, NULL, &iW, &iH);
				renderTexture(pacmanLC, renderer, 200 + pac5.GetX() * 22 + 9 + pac5.GetTemp(), 150 + pac5.GetY() * 18);
			}
			else if (pac5.GetDir() == 8 && pac5.GetBouche() < 5)
			{
				SDL_QueryTexture(pacmanUO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanUO, renderer, 200 + pac5.GetX() * 22 + 9, 150 + pac5.GetY() * 18 + pac5.GetTemp());
			}
			else if (pac5.GetDir() == 8 && pac5.GetBouche() >= 5)
			{
				SDL_QueryTexture(pacmanUC, NULL, NULL, &iW, &iH);
				renderTexture(pacmanUC, renderer, 200 + pac5.GetX() * 22 + 9, 150 + pac5.GetY() * 18 + pac5.GetTemp());
			}
			else if (pac5.GetDir() == 2 && pac5.GetBouche() < 5)
			{
				SDL_QueryTexture(pacmanDO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanDO, renderer, 200 + pac5.GetX() * 22 + 9, 150 + pac5.GetY() * 18 + pac5.GetTemp());
			}
			else if (pac5.GetDir() == 2 && pac5.GetBouche() >= 5)
			{
				SDL_QueryTexture(pacmanDC, NULL, NULL, &iW, &iH);
				renderTexture(pacmanDC, renderer, 200 + pac5.GetX() * 22 + 9, 150 + pac5.GetY() * 18 + pac5.GetTemp());
			}

			if (pac6.GetLives() > 0)
			{
				SDL_QueryTexture(pacmanRO, NULL, NULL, &iW, &iH);
				renderTexture(pacmanRO, renderer, 31, 570);
			}
			if (pac6.GetLives() > 1)
			{
				renderTexture(pacmanRO, renderer, 51, 570);
			}
			if (pac6.GetLives() > 2)
			{
				renderTexture(pacmanRO, renderer, 71, 570);
			}
			if (pac6.GetLives() > 3)
			{
				renderTexture(pacmanRO, renderer, 91, 570);
			}
			if (pac6.GetLives() > 4)
			{
				renderTexture(pacmanRO, renderer, 111, 570);
			}
			if (pac6.GetLives() > 5)
			{
				renderTexture(pacmanRO, renderer, 131, 570);
			}
			if (pac6.GetLives() > 6)
			{
				renderTexture(pacmanRO, renderer, 151, 570);
			}



			SDL_RenderPresent(renderer);

			if (beg > 2)
			{
				while (SDL_PollEvent(&e) || !run)
				{
					if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
						quit = true;
					if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							if ((carte[pac6.GetY() - 1][pac6.GetX()] < 3 && pac6.GetTemp() == 0) || pac6.GetDir() == 2)
							{
								if (pac6.GetDir() == 2)
								{
									if (carte[pac6.GetY() + 1][pac6.GetX()] < 3) {
										pac6.SetChange(true);
									}
								}
								pac6.SetDir(8);
								touchmem = 0;
							}
							else
								touchmem = 8;
							if ((carte[pac5.GetY() - 1][pac5.GetX()] < 3 && pac5.GetTemp() == 0) || pac5.GetDir() == 2)
							{
								if (pac5.GetDir() == 2)
								{
									if (carte[pac5.GetY() + 1][pac5.GetX()] < 3) {
										pac5.SetChange(true);
									}
								}
								pac5.SetDir(8);
								touchmem = 0;
							}
							else
								touchmem = 8;
							break;
						case SDLK_DOWN:
							if ((carte[pac6.GetY() + 1][pac6.GetX()] < 3 && pac6.GetTemp() == 0) || pac6.GetDir() == 8)
							{
								if (pac6.GetDir() == 8)
								{
									if (carte[pac6.GetY() - 1][pac6.GetX()] < 3) {
										pac6.SetChange(true);
									}
								}
								pac6.SetDir(2);
								touchmem = 0;
							}
							else
								touchmem = 2;
							if ((carte[pac5.GetY() + 1][pac5.GetX()] < 3 && pac5.GetTemp() == 0) || pac5.GetDir() == 8)
							{
								if (pac5.GetDir() == 8)
								{
									if (carte[pac5.GetY() - 1][pac5.GetX()] < 3) {
										pac5.SetChange(true);
									}
								}
								pac5.SetDir(2);
								touchmem = 0;
							}
							else
								touchmem = 2;
							break;
						case SDLK_LEFT:
							if ((carte[pac6.GetY()][pac6.GetX() - 1] < 3 && pac6.GetTemp() == 0) || pac6.GetDir() == 6)
							{
								if (pac6.GetDir() == 6)
								{
									if (carte[pac6.GetY()][pac6.GetX() + 1] < 3)
									{
										pac6.SetChange(true);
									}
								}
								pac6.SetDir(4);
								touchmem = 0;
							}
							else
								touchmem = 4;
							if ((carte[pac5.GetY()][pac5.GetX() - 1] < 3 && pac5.GetTemp() == 0) || pac5.GetDir() == 6)
							{
								if (pac5.GetDir() == 6)
								{
									if (carte[pac5.GetY()][pac5.GetX() + 1] < 3)
									{
										pac5.SetChange(true);
									}
								}
								pac5.SetDir(4);
								touchmem = 0;
							}
							else
								touchmem = 4;
							break;
						case SDLK_RIGHT:
							if ((carte[pac6.GetY()][pac6.GetX() + 1] < 3 && pac6.GetTemp() == 0) || pac6.GetDir() == 4)
							{
								if (pac6.GetDir() == 4)
								{
									if (carte[pac6.GetY()][pac6.GetX() - 1] < 3)
									{
										pac6.SetChange(true);
									}
								}
								pac6.SetDir(6);
								touchmem = 0;
							}
							else
								touchmem = 6;
							if ((carte[pac5.GetY()][pac5.GetX() + 1] < 3 && pac5.GetTemp() == 0) || pac5.GetDir() == 4)
							{
								if (pac5.GetDir() == 4)
								{
									if (carte[pac5.GetY()][pac5.GetX() - 1] < 3)
									{
										pac5.SetChange(true);
									}
								}
								pac5.SetDir(6);
								touchmem = 0;
							}
							else
								touchmem = 6;
							break;
						case SDLK_p:
							run = !run;
							break;
						case SDLK_ESCAPE:
							quit = true;
							break;
						default:
							break;
						}
					}
				}
				if (touchmem == 8 && !pac6.GetTemp() && carte[pac6.GetY() - 1][pac6.GetX()] < 3)
				{
					pac6.SetDir(touchmem);
					//touchmem = 0;
				}
				else if (touchmem == 6 && !pac6.GetTemp() && carte[pac6.GetY()][pac6.GetX() + 1] < 3)
				{
					pac6.SetDir(touchmem);
					//touchmem = 0;
				}
				else if (touchmem == 2 && !pac6.GetTemp() && carte[pac6.GetY() + 1][pac6.GetX()] < 3)
				{
					pac6.SetDir(touchmem);
					//touchmem = 0;
				}
				else if (touchmem == 4 && !pac6.GetTemp() && carte[pac6.GetY()][pac6.GetX() - 1] < 3)
				{
					pac6.SetDir(touchmem);
					//touchmem = 0;
				}
				if (touchmem == 8 && !pac5.GetTemp() && carte[pac5.GetY() - 1][pac5.GetX()] < 3)
				{
					pac5.SetDir(touchmem);
					touchmem = 0;
				}
				else if (touchmem == 6 && !pac5.GetTemp() && carte[pac5.GetY()][pac5.GetX() + 1] < 3)
				{
					pac5.SetDir(touchmem);
					touchmem = 0;
				}
				else if (touchmem == 2 && !pac5.GetTemp() && carte[pac5.GetY() + 1][pac5.GetX()] < 3)
				{
					pac5.SetDir(touchmem);
					touchmem = 0;
				}
				else if (touchmem == 4 && !pac5.GetTemp() && carte[pac5.GetY()][pac5.GetX() - 1] < 3)
				{
					pac5.SetDir(touchmem);
					touchmem = 0;
				}
			}



		
		}

		if (r == 3) {
			
			ifstream fichier("scores.txt");
			if (fichier)
			{
				string ligne;
				while (getline(fichier, ligne))
				{
					if (scoreimod == 0) {
						scores[scorei] = std::stoi(ligne);
						//cout << scores[scorei] << endl;
						scoreimod = 1;
					}
					else  {
						noms[scorei] = ligne;
						//cout << noms[scorei] << endl;
						scoreimod = 0;
						scorei++;
					}
				}
			}
			if (menuscores == 0) {
				SDL_QueryTexture(background, NULL, NULL, 0, 0);
				renderTexture(background, renderer, 0, 0);
				menuscores = 1;
				SDL_RenderPresent(renderer);
			}
			for (int d = 300; d != -1; d--)
			{
				for (int i = 0; i < d; i++)
				{
					if (scores[i] < scores[i + 1])
					{
						tmp = scores[i];
						scores[i] = scores[i + 1];
						scores[i + 1] = tmp;

						tmp2 = noms[i];
						noms[i] = noms[i + 1];
						noms[i + 1] = tmp2;
					}
				}
			}
			for (int i = 0; i < 10; i++)
			{
				std::cout << scores[i] <<" "<<noms[i]<< endl;
			}
			r = 4;
		}
		
		if (r == 4) {
			for (int i = 0; i < 10; i++)
			{
				if ((scores[i] / 100000) == 0) {
					SDL_QueryTexture(u0, NULL, NULL, &iW, &iH);
					renderTexture(u0, renderer, 100, 100);
				}
				if ((scores[i] / 10000)%10 == 0) {
					SDL_QueryTexture(u0, NULL, NULL, &iW, &iH);
					renderTexture(u0, renderer, 120, 100);
				}
				if ((scores[i] / 1000)%10 == 0) {
					SDL_QueryTexture(u0, NULL, NULL, &iW, &iH);
					renderTexture(u0, renderer, 140, 100);
				}
				if ((scores[i] / 100)%10 == 0) {
					SDL_QueryTexture(u0, NULL, NULL, &iW, &iH);
					renderTexture(u0, renderer, 160, 100);
				}
				if ((scores[i] / 10) % 10 == 0) {
					SDL_QueryTexture(u0, NULL, NULL, &iW, &iH);
					renderTexture(u0, renderer, 180, 100);
				}
				if (scores[i]  % 10 == 1) {
					SDL_QueryTexture(u0, NULL, NULL, &iW, &iH);
					renderTexture(u0, renderer, 200, 100);
				}
			}
			SDL_RenderPresent(renderer);
		}

		if (r == 5) {
			ofstream monscore{"scores.txt",ios::app };
			monscore << endl << "200";
			monscore << endl << "PA";
			r = 1;
		}
	}
}