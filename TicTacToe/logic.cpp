#include "logic.h"
#include "app.h"

// Finds out which square in the board was clicked. If there was a click outside the board, then nothing happens.
void findClickedCell(App& app, int x, int y) {
	if ((x >= 0 && x <= CELL_WIDTH * 3) && (y >= 0 && y <= CELL_HEIGHT * 3)) {
		if (app.state == PLAYER_X_TURN || app.state == PLAYER_O_TURN) {
			int row = y / CELL_HEIGHT;
			int column = x / CELL_WIDTH;

			if (app.board[row][column] == BLANK) {
				if (app.state == PLAYER_X_TURN) {
					app.board[row][column] = X;
					swapPlayer(app);
				}
				else if (app.state == PLAYER_O_TURN) {
					app.board[row][column] = O;
					swapPlayer(app);
				}
			}

			checkEndGame(app);
		}
		else {
			resetGame(app);
		}
	}
}

void swapPlayer(App& app) {
	if (app.state == PLAYER_X_TURN)
		app.state = PLAYER_O_TURN;
	else if (app.state == PLAYER_O_TURN)
		app.state = PLAYER_X_TURN;
}

bool checkEndGame(App& app) {
	int blankCount = 0;

	//check rows to see if there is a winner
	for (int row = 0; row < BOARD_LENGTH; ++row) {
		if (app.board[row][0] == X && app.board[row][1] == X && app.board[row][2] == X) {
			app.state = PLAYER_X_WON;
			return true;
		}

		if (app.board[row][0] == O && app.board[row][1] == O && app.board[row][2] == O) {
			app.state = PLAYER_O_WON;
			return true;
		}
	}

	//check columns to see if there is a winner
	for (int col = 0; col < BOARD_LENGTH; ++col) {
		if (app.board[0][col] == X && app.board[1][col] == X && app.board[2][col] == X) {
			app.state = PLAYER_X_WON;
			return true;
		}

		if (app.board[0][col] == O && app.board[1][col] == O && app.board[2][col] == O) {
			app.state = PLAYER_O_WON;
			return true;
		}
	}

	//check diagonal for X winner
	if (app.board[0][0] == X && app.board[1][1] == X && app.board[2][2] == X) {
		app.state = PLAYER_X_WON;
		return true;
	}

	//check diagonal for O winner
	if (app.board[0][0] == O && app.board[1][1] == O && app.board[2][2] == O) {
		app.state = PLAYER_O_WON;
		return true;
	}

	//check other diagonal for X winner
	if (app.board[2][0] == X && app.board[1][1] == X && app.board[0][2] == X) {
		app.state = PLAYER_X_WON;
		return true;
	}

	//check other diagonal for O winner
	if (app.board[2][0] == O && app.board[1][1] == O && app.board[0][2] == O) {
		app.state = PLAYER_O_WON;
		return true;
	}

	//At this point, we know that neither X nor O have won, so now we find a blank space to determine
	//if the game ended in a tie.
	for (int row = 0; row < BOARD_LENGTH; ++row) {
		for (int col = 0; col < BOARD_LENGTH; ++col) {
			if (app.board[row][col] == BLANK) {
				return false;
			}
		}
	}

	//Since no blank tiles on the board were found, the game has ended in a tie
	app.state = TIE;
	return true;
}

void resetGame(App& app) {
	app.state = PLAYER_X_TURN;

	for (int row = 0; row < BOARD_LENGTH; ++row)
		for (int col = 0; col < BOARD_LENGTH; ++col)
			app.board[row][col] = BLANK;
}