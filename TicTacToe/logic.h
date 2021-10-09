#pragma once

struct App;

void findClickedCell(App& app, int x, int y);
void swapPlayer(App& app);
bool checkEndGame(App& app);
void resetGame(App& app);