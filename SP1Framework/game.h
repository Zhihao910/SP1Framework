#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "Framework\console.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#define VK_1 0x31 
#define VK_2 0x32 
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_P 0x50

using namespace std;

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;
extern bool newMap;
extern bool setSpawn;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_SPACE,
	K_1, 
	K_2,
	K_3,
	K_4,
	K_5,
	K_6,
	K_P,
    K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
	S_MAINMENU,
	S_INSTRUCTIONS,
    S_GAME,
	S_LEVELS,
	S_COUNT
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
	int redKey;
	int	blueKey;
	int gold;

};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 

void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void renderMainMenuScreen();
void renderInstructionScreen();
void renderLevelSelection();
void renderDialogue();

void mainmenuwait();
void instructionwait();
void selectLevel();

void PrintSplashScreen();	//Loads and Prints the Splash Screen
void PrintMainMenu();		//Loads and Prints the Main Menu
void PrintInstructions();	//Loads and Prints the Instruction Screen
void PrintLevelSelect();	//Loads and Prints the Level Selection Screen
void PrintDialogueBox();
void PrintDialogueText();

void SplashScreen();
void MainMenu();
void Instructions();
void LevelSelect();
void DialogueBox();

void MapLayout1();
void MapLayout2();
void MapLayout3();
void MapLayout4();
void MapLayout5();
void MapLayout6();
void MapLayout7();
void MapLayout8();
void MapLayout9();
void MapLayout10();
void loadMap(int level);

void readMap(int level, int height, int width);
#endif // _GAME_H