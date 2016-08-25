#include "printLayout.h"

void MapLayout(int levels, int *numberOfEnemy) // Prints out Maze (depeneding on Level selected)
{
	COORD c;
	c.X = 0;
	c.Y = 0;
	int height = 0;
	int width = 0;
	if (newMap)
	{
		newMap = false;
		readMap(levels, height, width, numberOfEnemy);
	}

	for (int y = 0; y < 20; y++)
	{
		c.Y = y + 1;
		for (int x = 0; x < 80; x++)
		{
			c.X = x;

			if (map[x][y] == 'P' && !setSpawn)
			{
				g_sChar.m_cLocation.X = x;
				g_sChar.m_cLocation.Y = y + 1;
				setSpawn = true;
			}
			if (map[x][y] == char(219))
			{
				g_Console.writeToBuffer(c, map[x][y], 0x9); //Prints walls in Blue.
			}
			if (map[x][y] == char(169) || map[x][y] == char(178))
			{
				g_Console.writeToBuffer(c, map[x][y], 0xC); //Prints Red Doors and Keys in Bright Red.
			}
			if (map[x][y] == char(170) || map[x][y] == char(177))
			{
				g_Console.writeToBuffer(c, map[x][y], 0xA); //Prints Green Doors and Keys in Bright Green.
			}
			if (map[x][y] == char(233))
			{
				g_Console.writeToBuffer(c, map[x][y], 0xE); //Prints Gold in Bright Yellow.
			}
			if (map[x][y] == char(240))
			{
				g_Console.writeToBuffer(c, map[x][y], 0xB); //Prints Staircase in Cyan.
			}
			if (map[x][y] == ':')
			{
				g_Console.writeToBuffer(c, map[x][y], 0xB); //Prints Opened Doors in Cyan.
			}
			if (map[x][y] == char(65))
			{
				temp[x][y] = map[x][y];
				temp[x][y] = char(234);
				g_Console.writeToBuffer(c, temp[x][y], 0x5); //Prints LEVEL 4 PORTAL-IN in Magenta. First set
			}
			if (map[x][y] == char(66))
			{
				temp[x][y] = map[x][y];
				temp[x][y] = char(234);
				g_Console.writeToBuffer(c, temp[x][y], 0x5); //Prints LEVEL 4 PORTAL-OUT in Magenta. First set
			}

			if (map[x][y] == char(67))
			{
				temp[x][y] = map[x][y];
				temp[x][y] = char(234);
				g_Console.writeToBuffer(c, temp[x][y], 0xE); //Prints LEVEL 5 PORTAL-IN in Yellow. First set
			}
			if (map[x][y] == char(68))
			{
				temp[x][y] = map[x][y];
				temp[x][y] = char(234);
				g_Console.writeToBuffer(c, temp[x][y], 0xE); //Prints LEVEL 5 PORTAL-OUT in Yellow. First set
			}
			if (map[x][y] == char(69))
			{
				temp[x][y] = map[x][y];
				temp[x][y] = char(234);
				g_Console.writeToBuffer(c, temp[x][y], 0x3); //Prints LEVEL 5 PORTAL-IN in Cyan. Second set
			}
			if (map[x][y] == char(70))
			{
				temp[x][y] = map[x][y];
				temp[x][y] = char(234);
				g_Console.writeToBuffer(c, temp[x][y], 0x3); //Prints LEVEL 5 PORTAL-OUT in Cyan. Second set
			}
			if (map[x][y] == char(102))
			{
				temp[x][y] = map[x][y];
				temp[x][y] = char(94);
				g_Console.writeToBuffer(c, temp[x][y], 0x4); //Prints FireTrap in Red.
			}
			if (map[x][y] == char(112))
			{
				temp[x][y] = map[x][y];
				temp[x][y] = char(94);
				g_Console.writeToBuffer(c, temp[x][y], 0x5); //Prints PoisonTrap in Magenta.
			}
			if (map[x][y] == char(118))
			{
				temp[x][y] = map[x][y];
				temp[x][y] = char(219);
				g_Console.writeToBuffer(c, temp[x][y], 0x6); //Prints PitfallTrap in Brown.
			}
			if (map[x][y] == char(94))
			{
				g_Console.writeToBuffer(c, map[x][y], 0x7); //Prints SpikeTrap in White.
			}
		}
	}
}