#include "loadText.h"

void PrintWin()
{
	Win();

	COORD c = g_Console.getConsoleSize();
	c.X = 20;
	c.Y /= 3;
	string line = "";

	for (int y = 0; y < 14; y++)
	{
		line = text[y];
		g_Console.writeToBuffer(c, line, 0xC);
		c.Y++;
	}
}

void Win()
{
	int height = 0;
	int width;
	string line = "";
	ifstream myfile("Screens/YouWin.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (width = 0; width < 55; width++)
			{
				text[height][width] = line[width];
			}
			height++;
		}
		myfile.close();
	}
}