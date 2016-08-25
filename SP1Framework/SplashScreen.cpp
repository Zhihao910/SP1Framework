#include "loadText.h"

bool LoadSplash = false;

void PrintSplashScreen()
{
	if (!LoadSplash)
	{
		SplashScreen();
		LoadSplash = true;
	}

	COORD c = g_Console.getConsoleSize();
	c.X = (c.X / 2) - 25;
	c.Y /= 3;
	string line = "";

	for (int y = 0; y < 30; y++)
	{
		line = text[y];
		g_Console.writeToBuffer(c, line, 0xE);
		c.Y++;
	}
}

void SplashScreen()
{
	int height = 0;
	int width;
	string line = "";
	ifstream myfile("Screens/Splashscreen.txt");

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