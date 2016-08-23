#include "loadText.h"

void PrintLevelSelect()
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