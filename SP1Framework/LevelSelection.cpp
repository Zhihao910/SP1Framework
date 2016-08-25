#include "loadText.h"

void PrintLevelSelect()
{
	LevelSelect();

	COORD c = g_Console.getConsoleSize();
	c.X /= 3;
	c.Y = 3;
	string line = "";

	for (int y = 0; y < 23; y++)
	{
		if (y < 6)
		{
			line = text[y];
			g_Console.writeToBuffer(c, line, 0xC);
		}
		else if (y > 5)
		{
			line = text[y];
			g_Console.writeToBuffer(c, line);
		}		
		c.Y++;
	}
}


void LevelSelect()
{

	int height = 0;
	int width;
	string line = "";
	ifstream myfile("LevelSelection.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (width = 0; width < 50; width++)
			{
				text[height][width] = line[width];
			}
			height++;
		}
		myfile.close();
	}
}