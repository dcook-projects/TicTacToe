#pragma once

#include <SDL_ttf.h>
#include "ltexture.h"

constexpr int SCREEN_WIDTH = 1200;
constexpr int SCREEN_HEIGHT = 675;

constexpr int CELL_WIDTH = SCREEN_WIDTH / 6;
constexpr int CELL_HEIGHT = SCREEN_HEIGHT * 2 / 9;
constexpr int BOARD_LENGTH = 3;

enum Cell {
	BLANK = 0,
	X = 1,
	O = 2
};

enum GameState {
	PLAYER_X_TURN,
	PLAYER_O_TURN,
	PLAYER_X_WON,
	PLAYER_O_WON,
	TIE
};

struct App {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	LTexture XTexture;
	LTexture OTexture;
	LTexture textTexture;
	TTF_Font* font = nullptr;
	GameState state = PLAYER_X_TURN;
	Cell board[BOARD_LENGTH][BOARD_LENGTH] =  { BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK};
} ;