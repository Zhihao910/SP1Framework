#include "printLayout.h"

void MapLayout() // Prints out Maze1
{
	COORD c;
	c.X = 0;
	c.Y = 0;
	int height = 0;
	int width = 0;
	if (newMap)
	{
		newMap = false;
		readMap(1, height, width);
	}

	for (int y = 0; y < 20; y++)
	{
		c.Y = y + 1;
		for (int x = 0; x < 80; x++)
		{
			c.X = x;

			if (map[x][y] == 'P' && !setSpawn)
			{
				g_Console.writeToBuffer(c, unsigned char(233));
				g_sChar.m_cLocation.X = x;
				g_sChar.m_cLocation.Y = y + 1;
				setSpawn = true;
			}
			if (map[x][y] == char(219))
			{
				g_Console.writeToBuffer(c, map[x][y], 0xA); //Prints walls in Green.
			}
			if (map[x][y] == char(176))
			{
				g_Console.writeToBuffer(c, map[x][y], 0x0); //Prints Floor in Black.
			}
			if (map[x][y] == char(169) || map[x][y] == char(178))
			{
				g_Console.writeToBuffer(c, map[x][y], 0xC); //Prints Red Doors and Keys in Bright Red.
			}
			if (map[x][y] == char(170) || map[x][y] == char(177))
			{
				g_Console.writeToBuffer(c, map[x][y], 0x9); //Prints Blue Doors and Keys in Bright Blue.
			}
			if (map[x][y] == char(233))
			{
				g_Console.writeToBuffer(c, map[x][y], 0xCE); //Prints Gold in Bright Yellow.
			}
			if (map[x][y] == char(240))
			{
				g_Console.writeToBuffer(c, map[x][y], 0xB); //Prints Staircase in Cyan.
			}
		}
	}
}
void MapLayout2() // Prints out Maze2
{
	COORD c;
	c.X = 0;
	c.Y = 0;
	int height = 0;
	int width = 0;
	if (newMap)
	{
		newMap = false;
		readMap(2, height, width);
	}
	for (int y = 0; y < 15; y++)
	{
		c.Y = y + 1;
		for (int x = 0; x < 80; x++)
		{
			c.X = x;
			if (map[x][y] == 'P' && !setSpawn)
			{
				g_Console.writeToBuffer(c, unsigned char(233));
				g_sChar.m_cLocation.X = x;
				g_sChar.m_cLocation.Y = y + 1;
				setSpawn = true;
			}
			if (map[x][y] == char(219))
			{
				g_Console.writeToBuffer(c, map[x][y], 0x2);
			}
			if (map[x][y] == char(169) || map[x][y] == char(178))
			{
				g_Console.writeToBuffer(c, map[x][y], 0x4);
			}
		}
	}
}
void MapLayout3() //Prints out Maze3
{
	COORD c;
	c.X = 0;
	c.Y = 0;
	int height = 0;
	int width = 0;
	if (newMap)
	{
		newMap = false;
		readMap(3, height, width);
	}

	for (int y = 0; y < 15; y++)
	{
		c.Y = y + 1;
		for (int x = 0; x < 80; x++)
		{
			c.X = x;
			if (map[x][y] == 'P' && !setSpawn)
			{
				g_Console.writeToBuffer(c, unsigned char(233));
				g_sChar.m_cLocation.X = x;
				g_sChar.m_cLocation.Y = y + 1;
				setSpawn = true;
			}
			else
			{
				g_Console.writeToBuffer(c, map[x][y]);
			}
		}
	}
}