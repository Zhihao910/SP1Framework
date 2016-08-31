// This is the main file for the game logic and function
//
//
#include "game.h"


double  g_dElapsedTime;
double  g_dDeltaTime;
double g_dCountdown;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar;
SEnemyChar   g_sEnemy[2][totalEnemy]; //[Number of Enemy Type][Amount of enemy]
EGAMESTATES g_eGameState;
EGAMESTATES g_eCombatState;
double  g_dBounceTime;		// this is to prevent key bouncing, so we won't trigger keypresses more than once
char map[100][50];			// array for Maps
char text[50][100];			// array for Screens
int points;					// score variable
int difficulty = 0;			// difficulty selection
int maps = 0;				// level selection
int enemyType = 2;			// 2 types of enemy(Slow, Fast)
int numberOfEnemy = 0;		// Number of enemy in map
int unlocked = 1;			// number of levels unlocked
bool setSpawn = false;		// checks is spawnpoint is set in level
bool newMap = true;			// checks is level loaded is a new level

// Console object
Console g_Console(100, 50, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

	g_sChar.m_cLocation.X = (g_Console.getConsoleSize().X / 2) - 40;
	g_sChar.m_cLocation.Y = (g_Console.getConsoleSize().Y / 2) - 23;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Raster Fonts");
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{    
g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
g_abKeyPressed[K_1] = isKeyPressed(VK_1);
g_abKeyPressed[K_2] = isKeyPressed(VK_2);
g_abKeyPressed[K_3] = isKeyPressed(VK_3);
g_abKeyPressed[K_4] = isKeyPressed(VK_4);
g_abKeyPressed[K_5] = isKeyPressed(VK_5);
g_abKeyPressed[K_6] = isKeyPressed(VK_6);
g_abKeyPressed[K_P] = isKeyPressed(VK_P);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
	// get the delta time
	g_dElapsedTime += dt;
	g_dDeltaTime = dt;

	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: splashScreenWait(); // game logic for the splash screen
		break;
	case S_GAME: gameplay(); // gameplay logic when we are in the game
		break;
	case S_MAINMENU: mainmenuwait();
		break;
	case S_INSTRUCTIONS: instructionwait();
		break;
	case S_DIFFICULTY: selectDifficulty();
		break;
	case S_LEVELS: selectLevel();
		break;
	case S_DEATH: deathwait();
		break;
	case S_SCORE: scorewait();
		break;
	}
}

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
	clearScreen();      // clears the current screen and draw from scratch 
	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: PrintSplashScreen();
		break;
	case S_GAME: 
		renderGame();
		render_clock(g_dDeltaTime);
		PrintDialogueBox();
		PrintDialogueText();
		break;
	case S_MAINMENU: PrintMainMenu();
		break;
	case S_INSTRUCTIONS: PrintInstructions();
		break;
	case S_DIFFICULTY: PrintDifficulty();
		break;
	case S_LEVELS: PrintLevelSelect();
		break;
	case S_SCORE: renderHighScore();
		break;
	case S_DEATH: PrintDeath();
		break;
	case S_FIGHT: PrintCombat();
		break;
	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void gameplay()            // gameplay logic
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveCharacter();	// moves the character, collision detection, physics, etc
						// sound can be played here too.
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
		g_eGameState = S_MAINMENU;
}
void mainmenuwait() // main menu logic
{
	if (g_abKeyPressed[K_1])
	{
		g_dBounceTime = g_dElapsedTime + 0.5; // 125ms should be enough
		g_eGameState = S_DIFFICULTY;
	}

	if (g_abKeyPressed[K_2])
	{
		g_dBounceTime = g_dElapsedTime + 0.5;
		g_eGameState = S_INSTRUCTIONS;
	}

	if (g_abKeyPressed[K_3])
	{
		g_dBounceTime = g_dElapsedTime + 0.5;
		g_bQuitGame = true;
	}
}
void instructionwait()
{
	if (g_abKeyPressed[K_P])
	{
		g_eGameState = S_MAINMENU;
	}
}
void selectDifficulty()	
{
	if (g_dBounceTime > g_dElapsedTime)
	{
		return;
	}
	if (g_abKeyPressed[K_1])
	{
		difficulty = 1;
		g_sChar.health = 20;
		g_sChar.attack = 5;
		g_sChar.defence = 5;
		g_dBounceTime = g_dElapsedTime + 0.5;
		g_eGameState = S_LEVELS;
	}
	if (g_abKeyPressed[K_2])
	{
		difficulty = 2;
		g_sChar.health = 15;
		g_sChar.attack = 5;
		g_sChar.defence = 5;
		g_dBounceTime = g_dElapsedTime + 0.5;
		g_eGameState = S_LEVELS;
	}
	if (g_abKeyPressed[K_3])
	{
		difficulty = 3;
		g_sChar.health = 7;
		g_sChar.attack = 5;
		g_sChar.defence = 5;
		g_dBounceTime = g_dElapsedTime + 0.5;
		g_eGameState = S_LEVELS;
	}
	if (g_abKeyPressed[K_4])
	{
		difficulty = 4;
		g_sChar.health = 3;
		g_sChar.attack = 15;
		g_sChar.defence = 5;
		g_dBounceTime = g_dElapsedTime + 0.5;
		g_eGameState = S_LEVELS;
	}
	if (g_abKeyPressed[K_P])
	{
		g_dBounceTime = g_dElapsedTime + 0.5;
		g_eGameState = S_MAINMENU;
	}
}
void selectLevel()
{	
	if (g_dBounceTime > g_dElapsedTime)
	{
		return;
	}
	if (g_abKeyPressed[K_1])
	{
		maps = 1;
		g_sChar.gold = 0;
		g_dBounceTime = g_dElapsedTime + 0.5;
		g_eGameState = S_GAME;
	}
	if (g_abKeyPressed[K_2])
	{
		if (unlocked > 1)
		{
			maps = 2;
			g_sChar.gold = 0;
			g_dBounceTime = g_dElapsedTime + 0.5;
			g_eGameState = S_GAME;
		}	
	}
	if (g_abKeyPressed[K_3])
	{
		if (unlocked > 2)
		{
			maps = 3;
			g_sChar.gold = 0;
			g_dBounceTime = g_dElapsedTime + 0.5;
			g_eGameState = S_GAME;
		}
	}
	if (g_abKeyPressed[K_4])
	{
		if (unlocked > 3)
		{
			maps = 4;
			g_sChar.gold = 0;
			g_dBounceTime = g_dElapsedTime + 0.5;
			g_eGameState = S_GAME;
		}
	}
	if (g_abKeyPressed[K_5])
	{
		if (unlocked > 4)
		{
			maps = 5;
			g_sChar.gold = 0;
			g_dBounceTime = g_dElapsedTime + 0.5;
			g_eGameState = S_GAME;
		}
	}
	if (g_abKeyPressed[K_6])
	{
		if (unlocked > 4)
		{
			maps = 6;
			g_sChar.gold = 0;
			g_dBounceTime = g_dElapsedTime + 0.5;
			g_eGameState = S_GAME;
		}
	}

	if (g_abKeyPressed[K_P])
	{
		g_dBounceTime = g_dElapsedTime + 0.5;
		g_eGameState = S_DIFFICULTY;
	}
}
void scorewait()
{
	if (g_abKeyPressed[K_ESCAPE])
	{
		g_eGameState = S_MAINMENU;
	}
}
void deathwait()
{
	if (g_abKeyPressed[K_SPACE])
	{
		g_eGameState = S_SCORE;
	}
}

void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;

	if (g_abKeyPressed[K_P])
	{
		g_sChar.m_cLocation.X = (g_Console.getConsoleSize().X / 2) - 40;
		g_sChar.m_cLocation.Y = (g_Console.getConsoleSize().Y / 2) - 23;
		g_eGameState = S_MAINMENU;
		newMap = true;
		setSpawn = false;
	}
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
	g_Console.clearBuffer();
}

void renderHighScore()
{
	points = g_sChar.gold;
	HighScore(points);
}
void renderGame()
{
	MapLayout(maps, &numberOfEnemy);	//Maps
	renderEnemy();						//Renders the enemy
    renderCharacter();					//Renders the player
	renderFog(difficulty);				//Renders Fog of War
	Portal();							//Renders the End Portals
}
void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)64, charColor);
}
void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

	// displays the elapsed time
	ss.str("");
	ss << g_dElapsedTime << "secs";
	c.X = 0;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0x59);

}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}
void renderEnemy()
{
	for (int x = 0; x < numberOfEnemy; x++)
	{
		if (g_sEnemy[0][x].m_bActive && !g_sEnemy[0][x].bIsDead && !g_sEnemy[0][x].bIsFighting)
		{
			g_Console.writeToBuffer(g_sEnemy[0][x].m_cLocation, (char)158);
			g_sEnemy[0][x].bIsDead = false;
			g_sEnemy[0][x].bIsFighting = false;
			g_sEnemy[0][x].health = 15;
			g_sEnemy[0][x].defence = x;
			enemyMove();
		}
	}
}