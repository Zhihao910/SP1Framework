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

			if (map[x][y] == 'P'&& !setSpawn)
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
			if (map[x][y] == 'P'&&!setSpawn)
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
			if (map[x][y] == 'P'&&!setSpawn)
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