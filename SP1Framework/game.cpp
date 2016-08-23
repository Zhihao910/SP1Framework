// This is the main file for the game logic and function
//
//
#include "game.h"

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];
bool	setSpawn = false;
bool	newMap = true;

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
char map[100][50];
char text[40][100];
int maps = 0;

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
g_abKeyPressed[K_P] = isKeyPressed(VK_P);
g_abKeyPressed[K_W] = isKeyPressed(VK_W);
g_abKeyPressed[K_A] = isKeyPressed(VK_A);
g_abKeyPressed[K_S] = isKeyPressed(VK_S);
g_abKeyPressed[K_D] = isKeyPressed(VK_D);
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
	case S_LEVELS: selectLevel();
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
	case S_SPLASHSCREEN: renderSplashScreen();
		break;

	case S_GAME: 
		renderGame();
		renderDialogue();
		break;

	case S_MAINMENU: renderMainMenuScreen();
		break;

	case S_INSTRUCTIONS: renderInstructionScreen();
		break;

	case S_LEVELS: renderLevelSelection();
		break;
	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void gameplay()            // gameplay logic
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveCharacter();    // moves the character, collision detection, physics, etc
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
		g_eGameState = S_LEVELS;
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
void selectLevel()
{	
	if (g_dBounceTime > g_dElapsedTime)
		return;
	if (g_abKeyPressed[K_1])
	{
		maps = 1;
		g_eGameState = S_GAME;
	}
	if (g_abKeyPressed[K_2])
	{
		maps = 2;
		g_eGameState = S_GAME;
	}
	if (g_abKeyPressed[K_3])
	{
		maps = 3;
		g_eGameState = S_GAME;
	}
	if (g_abKeyPressed[K_P])
	{
		g_eGameState = S_MAINMENU;
	}
}

void moveCharacter()
{
	COORD c;
	c.X = 4;
	c.Y = 24;

	bool bSomethingHappened = false;
	
	if (g_dBounceTime > g_dElapsedTime)
		return;
	
	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0) // Up movement
	{
		//Beep(1440, 30);
		g_sChar.m_cLocation.Y--;
		bSomethingHappened = true;
		if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(219))
		{
			g_sChar.m_cLocation.Y++;
		}
		if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(240))
		{
			maps++;
			newMap = true;
			setSpawn = false;
			if (maps == 4)
			{
				g_eGameState = S_MAINMENU;
			}
		}
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(178)) //Red Door
		{
			if (g_sChar.redKey != 0)
			{
				g_sChar.redKey--;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';    
			}

			if (g_sChar.redKey == 0)
			{
				g_sChar.m_cLocation.Y++;
			}
		}

		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(177)) //Blue Door
		{
			if (g_sChar.blueKey != 0)
			{
				g_sChar.blueKey--;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}

			if (g_sChar.blueKey == 0)
			{
				g_sChar.m_cLocation.Y++;
			}
		}

		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(169)) //Red Key
		{
			g_sChar.redKey++;
			map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
		}

		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(170)) //Blue Key
		{
			g_sChar.blueKey++;
			map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
		}
    }
    if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0) //left movement
    {
        //Beep(1440, 30);
		g_sChar.m_cLocation.X--;
		bSomethingHappened = true;
		if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(219))
		{
			g_sChar.m_cLocation.X++;
		}
		if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(240))
		{
			maps++;
			newMap = true;
			setSpawn = false;
			if (maps == 4)
			{
				g_eGameState = S_MAINMENU;
			}
		}
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(178)) //Red Door
		{
			if (g_sChar.redKey != 0)
			{
				g_sChar.redKey--;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}

			if (g_sChar.redKey == 0)
			{
				g_sChar.m_cLocation.X++;
			}
		}

		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(177)) //Blue Door
		{
			if (g_sChar.blueKey != 0)
			{
				g_sChar.blueKey--;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';

			}

			if (g_sChar.blueKey == 0)
			{
				g_sChar.m_cLocation.X++;
			}
		}

		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(169)) //Red Key
		{
			g_sChar.redKey++;
			map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
		}

		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(170)) //Blue Key
		{
			g_sChar.blueKey++;
			map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
		}
    }
    if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y > 0) //down movement
    {
        //Beep(1440, 30);
		g_sChar.m_cLocation.Y++;
		bSomethingHappened = true;
		if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(219))
		{
			g_sChar.m_cLocation.Y--;
		}
		if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(240))
		{
			maps++;
			newMap = true;
			setSpawn = false;
			if (maps == 4)
			{
				g_eGameState = S_MAINMENU;
			}
		}
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(178)) //Red Door
		{
			if (g_sChar.redKey != 0)
			{
				g_sChar.redKey--;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}

			if (g_sChar.redKey == 0)
			{
				g_sChar.m_cLocation.Y--;
			}
		}

		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(177)) //Blue Door
		{
			if (g_sChar.blueKey != 0)
			{
				g_sChar.blueKey--;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}

			if (g_sChar.blueKey == 0)
			{
				g_sChar.m_cLocation.Y--;
			}
		}

		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(169)) //Red Key
		{
			g_sChar.redKey++;
			map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
		}

		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(170)) //Blue Key
		{
			g_sChar.blueKey++;
			map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
		}
    }
    if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X > 0) //right movement
    {
        //Beep(1440, 30);
		g_sChar.m_cLocation.X++;
		bSomethingHappened = true;
		if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(219))
		{
			g_sChar.m_cLocation.X--;
		}
		if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(240))
		{
			maps++;
			newMap = true;
			setSpawn = false;
			if (maps == 4)
			{
				g_eGameState = S_MAINMENU;
			}
		}
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(178)) //Red Door
		{
			if (g_sChar.redKey != 0)
			{
				g_sChar.redKey--;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}

			if (g_sChar.redKey == 0)
			{
				g_sChar.m_cLocation.X--;
			}
		}

		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(177)) //Blue Door
		{
			if (g_sChar.blueKey != 0)
			{
				g_sChar.blueKey--;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}

			if (g_sChar.blueKey == 0)
			{
				g_sChar.m_cLocation.X--;
			}
		}

		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(169)) //Red Key
		{
			g_sChar.redKey++;
			map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
		}

		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(170)) //Blue Key
		{
			g_sChar.blueKey++;
			map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
		}
    }
    if (g_abKeyPressed[K_SPACE])
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
        bSomethingHappened = true;
    }
    if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
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
	g_Console.clearBuffer(/*0x1F*/);
}

void renderSplashScreen()  // renders the splash screen
{
	SplashScreen();

   	COORD c = g_Console.getConsoleSize();
	c.X = (c.X/2)-25;
	c.Y /= 3;
	string line = "";

	for (int y = 0; y < 30; y++)
	{
		line = text[y];
		g_Console.writeToBuffer(c, line);
		c.Y++;
	}
}
void renderMainMenuScreen() //renders main menu
{
	MainMenu();

	COORD c = g_Console.getConsoleSize();
	c.X = 0;
	c.Y = 0;
	string line = "";

	for (int y = 0; y < 38; y++)
	{
		line = text[y];
		g_Console.writeToBuffer(c, line);
		c.Y++;
	}
}
void renderInstructionScreen() //render instructions
{
	Instructions();

	COORD c = g_Console.getConsoleSize();
	c.X = 0;
	c.Y = 0;
	string line = "";

	for (int y = 0; y < 33; y++)
	{
		line = text[y];
		g_Console.writeToBuffer(c, line);
		c.Y++;
	}
}
void renderLevelSelection()
{
	LevelSelect();

	COORD c = g_Console.getConsoleSize();
	c.X = 0;
	c.Y = 0;
	string line = "";

	for (int y = 0; y < 21; y++)
	{
		line = text[y];
		g_Console.writeToBuffer(c, line);
		c.Y++;
	}
}

void renderGame()
{
	loadMap(maps);
    renderCharacter();  // renders the character into the buffer
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

void loadMap(int level)
{
	switch (level)
	{
	case 1:
		MapLayout();
		break;
	case 2:
		MapLayout2();
		break;
	case 3:
		MapLayout3();
		break;
	default:
		break;
	}
}

void renderDialogue()
{
	COORD c = g_Console.getConsoleSize();
	c.X = 4;
	c.Y = 24;

	string redText = "Number of Red Keys: ";
	string blueText = "Number of Blue Keys: ";
	string goldText = "Amount of Gold: ";

	g_Console.writeToBuffer(c, redText);
	c.X = sizeof(redText);
	g_Console.writeToBuffer(c, g_sChar.redKey + '0');

	c.X = 4;
	c.Y += 2;

	g_Console.writeToBuffer(c, blueText);
	c.X = sizeof(blueText);
	g_Console.writeToBuffer(c, g_sChar.blueKey + '0');

	c.X = 4;
	c.Y += 2;

	g_Console.writeToBuffer(c, goldText);
	c.X = sizeof(goldText);
	g_Console.writeToBuffer(c, g_sChar.gold + '0');
}