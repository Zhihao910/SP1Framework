#include "loadText.h"

void PrintDeath()
{
	Death();

	setSpawn = false;
	newMap = true;

	COORD c = g_Console.getConsoleSize();
	c.X = 10;
	c.Y /= 3;
	string line = "";

	for (int y = 0; y < 11; y++)
	{
		line = text[y];
		g_Console.writeToBuffer(c, line, 0xC);
		c.Y++;
	}
}

void Death()
{
	int height = 0;
	int width;
	string line = "";
	ifstream myfile("Screens/YouDied.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (width = 0; width < 70; width++)
			{
				text[height][width] = line[width];
			}
			height++;
		}
		myfile.close();
	}
}