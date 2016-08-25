#include "loadText.h"

void PrintMainMenu()
{
	MainMenu();

	COORD c = g_Console.getConsoleSize();
	c.X = 0;
	c.Y = 0;
	string line = "";

	for (int y = 0; y < 38; y++)
	{
		int color;
		int time = g_dElapsedTime;

		if (time % 4 == 0 || time % 3 == 0)
		{
			if (time % 2 == 0)
			{
				if (y % 3 == 0)
				{
					color = 0xC;
				}

				if (y % 3 != 0)
				{
					color = 0x4;
				}
			}

			if (time % 2 != 0)
			{
				if (y % 2 == 0)
				{
					color = 0xC;
				}

				if (y % 2 != 0)
				{
					color = 0xD;
				}
			}
		}
		
		else
		{
			if (time % 2 == 0)
			{
				if (y % 3 == 0)
				{
					color = 0x3;
				}

				if (y % 3 != 0)
				{
					color = 0xB;
				}
			}

			if (time % 2 != 0)
			{
				if (y % 2 == 0)
				{
					color = 0x3;
				}

				if (y % 2 != 0)
				{
					color = 0x1;
				}
			}
		}
		

		line = text[y];
		g_Console.writeToBuffer(c, line, color);
		c.Y++;
	}
}

void MainMenu()
{
	int height = 0;
	int width;
	string line = "";
	ifstream myfile("Screens/Mainmenu.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (width = 0; width < 92; width++)
			{
				text[height][width] = line[width];
			}
			height++;
		}
		myfile.close();
	}
}