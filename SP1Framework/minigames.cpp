#include "minigames.h"

bool setMaze = false;
bool setMazeSpawn = false;

void timer()
{

}

void mazeRunner()
{

}

void snake()
{

}

void spaceInvader()
{

}

void loadMaze()
{
	string mapName = "";
	int mapSelect;
	int height = 0;
	int width = 0;

	mapSelect = rand() % 4 + 1;

	switch (mapSelect)
	{
	case 1: mapName = "Maps/MazeRunner1";
		break;
	case 2: mapName = "Maps/MazeRunner2";
		break;
	case 3: mapName = "Maps/MazeRunner3";
		break;
	case 4: mapName = "Maps/MazeRunner4";
		break;
	case 5: mapName = "Maps/MazeRunner5";
		break;
	default:
		break;
	}

	memset(text, '\0', sizeof(text[0][0]) * 100 * 50);

	ifstream mazeFile(mapName);
	if (mazeFile.is_open())
	{
		while (height < 41)
		{
			while (width < 92)
			{
				mazeFile >> text[width][height];
				if (text[width][height] == '.')
				{
					map[width][height] = char(176); //Floor
				}
				if (map[width][height] == '#') //Wall
				{
					map[width][height] = char(219);
				}
				if (map[width][height] == 'O') //Staircase
				{
					map[width][height] = char(240);
				}
				width++;
			}
			width = 0;
			height++;
		}
		mazeFile.close();
	}
}
void printMaze()
{
	COORD c;
	c.X = 0;
	c.Y = 0;
	int height = 0;
	int width = 0;

	if (!setMaze)
	{
		loadMaze();
		setMaze = true;
	}

	for (int y = 0; y < 20; y++)
	{
		c.Y = y + 1;
		for (int x = 0; x < 80; x++)
		{
			c.X = x;

			if (text[x][y] == 'P' && !setMazeSpawn)
			{
				g_sChar.m_cLocation.X = x;
				g_sChar.m_cLocation.Y = y + 1;
				setMazeSpawn = true;
			}
			if (text[x][y] == char(219))
			{
				g_Console.writeToBuffer(c, map[x][y], 0x9); //Prints walls in Blue.
			}
			if (map[x][y] == char(240))
			{
				g_Console.writeToBuffer(c, map[x][y], 0xB); //Prints Staircase in Cyan.
			}
		}
	}
}