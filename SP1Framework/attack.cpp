#include "attack.h"

void PrintCombat()
{
	CombatScreen(); // Always first to render.
}

void CombatScreen()
{
	COORD c = g_Console.getConsoleSize();
	c.X = 0;
	c.Y = 1;

	loadCombatScreen();

	string print = "";


	for (int y = 0; y < 35; y++)
	{
		print = text[y];
		g_Console.writeToBuffer(c, print, 0xE);
		c.Y++;
	}
}
void loadCombatScreen()
{
	int height = 0;
	int width;
	string line = "";
	ifstream myfile("Screens/Combat.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (width = 0; width < 80; width++)
			{
				text[height][width] = line[width];
			}
			height++;
		}
		myfile.close();
	}
}