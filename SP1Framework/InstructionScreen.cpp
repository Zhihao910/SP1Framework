#include "loadText.h"

void PrintInstructions()
{
	Instructions();

	COORD c = g_Console.getConsoleSize();
	c.X = 0;
	c.Y = 0;
	string line = "";

	for (int y = 0; y < 33; y++)
	{
		if (y < 6)
		{
			line = text[y];
			g_Console.writeToBuffer(c, line, 0xC);
		}

		else if (y > 14 && y < 22)
		{
			line = text[y];
			g_Console.writeToBuffer(c, line, 0xC);
		}

		else
		{
			line = text[y];
			g_Console.writeToBuffer(c, line);
		}

		c.Y++;
	}
}

void Instructions()
{

	int height = 0;
	int width;
	string line = "";
	ifstream myfile("Screens/Instructions.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (width = 0; width < 85; width++)
			{
				text[height][width] = line[width];
			}
			height++;
		}
		myfile.close();
	}
}