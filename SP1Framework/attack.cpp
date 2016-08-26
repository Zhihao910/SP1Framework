#include "global.h"

bool loadCombat = false;

void combat()
{
	COORD c = g_Console.getConsoleSize();
	c.X = 4;
	c.Y = 30;

	PrintCombat();

	vector<string> words{ "difficult", "grand", "correspondence", "whip", "rabbit", "punish", "secular", "honest", "examination", "steam", "hope", "tray", "breathe", "customer", "self", "pedestrian", "courtship", "fruit", "ceremony" };
	string Output;
	string Input;
	ostringstream oss;

	oss << "Type out the words that appear below!";
	g_Console.writeToBuffer(c, oss.str(), 0xB);
	oss.str("");

	c.Y += 2;

	Output = words.at(2);
	oss << words.at(2);
	g_Console.writeToBuffer(c, oss.str(), 0xC);
	oss.str("");
}

void PrintCombat()
{
	CombatScreen();	
}

void CombatScreen()
{
	COORD c = g_Console.getConsoleSize();
	c.X = 0;
	c.Y = 1;
	
	if (!loadCombat)
	{
		loadCombatScreen();
		loadCombat = true;
	}

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