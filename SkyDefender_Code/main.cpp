#include "Game.h"
#include <winbgim.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Constants.h"
using namespace std;

//main menu
void showMainMenu(bool& startGame, bool& showTutorial) {
    
    cleardevice();
    setbkcolor(COLOR(0, 0, 0));

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
    setcolor(COLOR(0, 191, 255));
    outtextxy(WIDTH / 2 - 200, HEIGHT / 4, "SKY DEFENDER");

    setcolor(COLOR(255, 255, 255));
    setfillstyle(SOLID_FILL, COLOR(0, 0, 0));
    
    // Start Game Button
    rectangle(WIDTH / 2 - 120, HEIGHT / 2 - 40, WIDTH / 2 + 100, HEIGHT / 2);
    floodfill(WIDTH / 2, HEIGHT / 2 - 40, COLOR(255, 255, 255));
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(COLOR(255, 255, 255));
    outtextxy(WIDTH / 2 - 80, HEIGHT / 2 - 30, "START GAME");

    // Instructions Button
    rectangle(WIDTH / 2 - 120, HEIGHT / 2 + 20, WIDTH / 2 + 100, HEIGHT / 2 + 60);
    floodfill(WIDTH / 2 - 120, HEIGHT / 2 + 40, COLOR(255, 255, 255));
    outtextxy(WIDTH / 2 - 95, HEIGHT / 2 + 30, "INSTRUCTIONS");
    
    while (true) {
    	
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y); //get coordinate of mouse click
			
			//check whether click the START GAME
            if (x >= WIDTH / 2 - 100 && x <= WIDTH / 2 + 100 &&
                y >= HEIGHT / 2 - 40 && y <= HEIGHT / 2) {
                startGame = true;
                break;
            }
			
			//check if click the INSTRUCTIONS
            if (x >= WIDTH / 2 - 100 && x <= WIDTH / 2 + 100 &&
                y >= HEIGHT / 2 + 20 && y <= HEIGHT / 2 + 60) {
                showTutorial = true;
                break;
            }
        }
        delay(50);
    }
}

//game instruction
void showInstructions() {
    
    cleardevice();
    setbkcolor(COLOR(0, 0, 0));
    setcolor(COLOR(255, 255, 255));
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);

    outtextxy(50, 50, "Controls:");
	outtextxy(50, 90, "- Arrow keys to move");
	outtextxy(50, 130, "- Auto shoot bullets");
	outtextxy(50, 170, "- Avoid enemies and bullets");
	outtextxy(50, 210, "- ESC to quit");
	
	outtextxy(50, 300, "Press any key to return to menu...");
	getch(); // read user input
}

int main() {
    initwindow(WIDTH, HEIGHT); // set max width and height for screen
    
    //instruction menu
    bool startGame = false;
    bool showTutorial = false;

    while (!startGame) {
        showMainMenu(startGame, showTutorial);

        if (showTutorial) {
            showInstructions();
            showTutorial = false;
        }
    }
    
    Game game;
    game.run();
    
    closegraph();
    return 0;
}

