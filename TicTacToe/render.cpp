#include "render.h"
#include "app.h"

void renderBoard(App& app) {
	//Draw first vertical line
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0xFF);
	SDL_RenderDrawLine(app.renderer, CELL_WIDTH, 0, CELL_WIDTH, CELL_HEIGHT * 3);

	//Draw second vertical line
	SDL_RenderDrawLine(app.renderer, CELL_WIDTH * 2, 0, CELL_WIDTH * 2, CELL_HEIGHT * 3);

	//Draw first horizontal line
	SDL_RenderDrawLine(app.renderer, 0, CELL_HEIGHT, CELL_WIDTH * 3, CELL_HEIGHT);

	//Draw second horizontal line
	SDL_RenderDrawLine(app.renderer, 0, CELL_HEIGHT * 2, CELL_WIDTH * 3, CELL_HEIGHT * 2);
}

// Draws the x's and o's to the board
void renderCells(App& app) {
	SDL_Rect renderQuad;
	renderQuad.w = CELL_WIDTH - 10;
	renderQuad.h = CELL_HEIGHT - 10;

	for (int i = 0; i < BOARD_LENGTH; ++i) {
		for (int j = 0; j < BOARD_LENGTH; ++j) {
			if (app.board[i][j] == X) {
				renderQuad.x = j * CELL_WIDTH + 5;
				renderQuad.y = i * CELL_HEIGHT + 5;
				app.XTexture.render(app, renderQuad);
			}
			else if (app.board[i][j] == O) {
				renderQuad.x = j * CELL_WIDTH + 5;
				renderQuad.y = i * CELL_HEIGHT + 5;
				app.OTexture.render(app, renderQuad);
			}
		}
	}
}

//render text to the screen if the board is in a game over state
void renderText(App& app) {
	if (app.state == PLAYER_X_WON) {
		app.textTexture.loadFromRenderedText(app, "Player 1 wins!\nClick on the board to play again", { 255, 0, 0 });
		app.textTexture.render(app, CELL_WIDTH * 3 + 10, (SCREEN_HEIGHT - app.textTexture.getHeight()) / 2);
	}
	else if (app.state == PLAYER_O_WON) {
		app.textTexture.loadFromRenderedText(app, "Player 2 wins!\nClick on the board to play again", { 0, 255, 0 });
		app.textTexture.render(app, CELL_WIDTH * 3 + 10, (SCREEN_HEIGHT - app.textTexture.getHeight()) / 2);
	}
	else if (app.state == TIE) {
		app.textTexture.loadFromRenderedText(app, "The game ended in a tie!\nClick on the board to play again", { 100, 100, 100 });
		app.textTexture.render(app, CELL_WIDTH * 3 + 10, (SCREEN_HEIGHT - app.textTexture.getHeight()) / 2);
	}
}