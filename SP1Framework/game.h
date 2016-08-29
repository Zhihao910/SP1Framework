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
#include "clock.h"

#define VK_1		0x31 
#define VK_2		0x32 
#define VK_3		0x33
#define VK_4		0x34
#define VK_5		0x35
#define VK_6		0x36
#define VK_7		0x37
#define VK_8		0x38
#define VK_9		0x39
#define VK_0		0x30
#define VK_A		0x41
#define VK_B		0x42
#define VK_C		0x43
#define VK_D		0x44
#define VK_E		0x45
#define VK_F		0x46
#define VK_G		0x47
#define VK_H		0x48
#define VK_I		0x49
#define VK_J		0x4A
#define VK_K		0x4B
#define VK_L		0x4C
#define VK_M		0x4D
#define VK_N		0x4E
#define VK_O		0x4F
#define VK_P		0x50
#define VK_Q		0x51
#define VK_R		0x52
#define VK_S		0x53
#define VK_T		0x54
#define VK_U		0x55
#define VK_V		0x56
#define VK_W		0x57
#define VK_X		0x58
#define VK_Y		0x59
#define VK_Z		0x5A
#define VK_NUMPAD1	0x61
#define VK_NUMPAD2	0x62
#define VK_NUMPAD3	0x63
#define VK_RETURN	0x0D

using namespace std;

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
	K_RETURN,
	K_A,
	K_B,
	K_C,
	K_D,
	K_E,
	K_F,
	K_G,
	K_H,
	K_I,
	K_J,
	K_K,
	K_L,
	K_M,
	K_N,
	K_O,
	K_P,
	K_Q,
	K_R,
	K_S,
	K_T,
	K_U,
	K_V,
	K_W,
	K_X,
	K_Y,
	K_Z,
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
	K_NUM1,
	K_NUM2,
	K_NUM3,
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
	S_FIGHT,
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
void PrintCombat();				// Loads and Prints the Combat Screen

void SplashScreen();			// Function for loading the text file
void MainMenu();				// Function for loading the text file
void Instructions();			// Function for loading the text file
void LevelSelect();				// Function for loading the text file
void DialogueBox();				// Function for loading the text file
void HighScoreBox();			// Function for loading the text file
void Death();					// Function for loading the text file
void Difficulty();				// Function for loading the text file
void CombatScreen();			// Function for loading the text file
void loadCombatScreen();		// Function for loading the text file

void HighScore(int score);		// Function for loading highscore data from file.
void combat();					// Function for combat in-game
void Portal();					// Function for in-game portals

void fireTrap();				// Function for traps
void poisonTrap();				// Function for traps
void pitTrap();					// Function for traps
void spikeTrap();				// Function for traps

void Type(string enemyWord);

void MapLayout(int levels, int *numberOfEnemy);						// Function for printing selected level from data
void readMap(int level, int height, int width, int *numberOfEnemy);	// Function for loading selected level into data
#endif // _GAME_H