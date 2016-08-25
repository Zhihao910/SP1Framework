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
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39
#define VK_0 0x30
#define VK_P 0x50
#define VK_C 0x43

using namespace std;

extern CStopWatch g_swTimer;
extern char map[100][50];
extern struct SGameChar g_sChar;
extern bool g_bQuitGame;
extern bool newMap;
extern bool setSpawn;
const int totalEnemy = 8;

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
	K_7,
	K_8,
	K_9,
	K_0,
	K_C,
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
	S_DIFFICULTY,
	S_LEVELS,
	S_SCORE,
	S_DEATH,
	S_COUNT
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
	int health;
	int redKey;
	int	greenKey;
	int gold;
};

struct SEnemyChar
{
	COORD m_cLocation;
	bool  m_bActive;
	bool bSomethingHappened = false;
	double slowDownTime = 0;
	int random = 1;
	int tempCheck = 1;
};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();		// waits for time to pass in splash screen
void gameplay();				// gameplay logic
void moveCharacter();			// moves the character, collision detection, physics, etc
void enemyMove();				// moves the monsters, collision detection, physics, etc
void processUserInput();		// checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();				// clears the current screen and draw from scratch 

void renderSplashScreen();		// Renders the splash screen
void renderGame();				// Renders the game stuff
void renderMap();				// Renders the map to the buffer first
void renderCharacter();			// Renders the character into the buffer
void renderFog(int diffLevel);	// Renders the Fog of War into the buffer
void renderEnemy();				// Renders the enemy into the buffer
void renderFramerate();			// Renders debug information, frame rate, elapsed time, etc
void renderHighScore();			// Renders the highscore
void renderToScreen();			// Dump the contents of the buffer to the screen, one frame worth of game

void mainmenuwait();			// Logic for Main Menu
void instructionwait();			// Logic for Instruction Screen
void selectLevel();				// Logic for Level Selection
void selectDifficulty();		// Logic for Difficulty Selection
void scorewait();				// Logic for Score Screen
void deathwait();				// Logic for Death Screen

void PrintSplashScreen();		// Loads and Prints the Splash Screen
void PrintMainMenu();			// Loads and Prints the Main Menu
void PrintInstructions();		// Loads and Prints the Instruction Screen
void PrintLevelSelect();		// Loads and Prints the Level Selection Screen
void PrintDialogueBox();		// Loads and Prints the Dialogue Template
void PrintDialogueText();		// Loads and Prints the Dialogue Text
void PrintDeath();				// Loads and Prints the Death Screen
void PrintDifficulty();			// Loads and Prints the Difficulty Screen
void PrintMaze();				// Loads and Prints the Maze

void SplashScreen();			// Function for loading the text file
void MainMenu();				// Function for loading the text file
void Instructions();			// Function for loading the text file
void LevelSelect();				// Function for loading the text file
void DialogueBox();				// Function for loading the text file
void HighScoreBox();			// Function for loading the text file
void Death();					// Function for loading the text file
void Difficulty();				// Function for loading the text file
void loadMaze();				// Function for loading the text file

void HighScore(int score);		// Function for loading highscore data from file.
void Portal();					// Function for in-game portals

void fireTrap();				// Function for traps
void poisonTrap();				// Function for traps
void pitTrap();					// Function for traps
void spikeTrap();				// Function for traps

void mazeRunner();				// Function for MazeRunner minigame


void MapLayout(int levels, int *numberOfEnemy);						// Function for printing selected level from data
void readMap(int level, int height, int width, int *numberOfEnemy);	// Function for loading selected level into data
#endif // _GAME_H