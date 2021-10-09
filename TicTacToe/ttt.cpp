/*
 *	David Cook
 */

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include "app.h"
#include "render.h"
#include "logic.h"

bool init(App &app);
bool loadMedia(App &app);
void close(App &app);



bool init(App &app) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to initialize\n");
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: Linear texture filtering not enabled!");
	}

	app.window = SDL_CreateWindow("Tic-Tac-Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (app.window == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}

	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (app.renderer == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

bool loadMedia(App &app) {
	if (!app.XTexture.loadFromFile(app, "assets/X.png")) {
		printf("X Texture failed to load\n");
		return false;
	}

	if (!app.OTexture.loadFromFile(app, "assets/O.png")) {
		printf("O Texture failed to load\n");
		return false;
	}

	app.font = TTF_OpenFont("assets/AquilineTwo.ttf", 28);
	if (app.font == nullptr)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

void close(App &app) {
	//Destroy textures
	app.XTexture.free();
	app.OTexture.free();
	app.textTexture.free();

	//Destroy Font
	TTF_CloseFont(app.font);
	app.font = nullptr;

	//Destroy window	
	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
	app.window = nullptr;
	app.renderer = nullptr;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}



int main(int argc, char* argv[]) {
	bool quit = false;
	SDL_Event e;
	App app;

	if (!init(app))
		return EXIT_FAILURE;

	if (!loadMedia(app))
		return EXIT_FAILURE;

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				quit = true;
			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				findClickedCell(app, x, y);
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
		SDL_RenderClear(app.renderer);

		renderBoard(app);
		renderCells(app);
		renderText(app);

		//Update screen
		SDL_RenderPresent(app.renderer);
	}

	close(app);
	return 0;
}