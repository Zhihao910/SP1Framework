#include "loadText.h"

void PrintDialogueBox()
{
	DialogueBox();

	COORD c = g_Console.getConsoleSize();
	c.X = 0;
	c.Y = 22;
	string line = "";

	for (int y = 0; y < 26; y++)
	{
		line = text[y];
		g_Console.writeToBuffer(c, line);
		c.Y++;
	}
}

void DialogueBox()
{
	int height = 0;
	int width;
	string line = "";
	ifstream myfile("Screens/Dialogue.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (width = 0; width < 81; width++)
			{
				text[height][width] = line[width];
			}
			height++;
		}
		myfile.close();
	}
}

void PrintDialogueText()
{
	COORD c = g_Console.getConsoleSize();
	c.X = 4;
	c.Y = 30;

	ostringstream oss;
	string healthText =		"Health: ";
	string goldText	=		"Amount of Gold: ";
	string redText =		"Number of Red Keys: ";
	string greenText =		"Number of Green Keys: ";
	string deathText =		"You Died! ";
	string mapLevel =		"Current Level: ";

	g_Console.writeToBuffer(c, healthText);
	c.X = sizeof(goldText);
	for (int i = 0; i < g_sChar.health; i++)
	{
		g_Console.writeToBuffer(c, char(3), 0xC);				//Prints out amount of health.
		c.X++;
	}

	c.X = 4;
	c.Y += 4;

	g_Console.writeToBuffer(c, mapLevel);
	c.X = sizeof(mapLevel) + 4;

	oss << maps;
	g_Console.writeToBuffer(c, maps + '0', 0xC);		//Prints out Map Level.
	oss.str("");

	c.X = 4;
	c.Y += 4;

	g_Console.writeToBuffer(c, goldText);
	c.X = sizeof(goldText) + 4;

	oss << g_sChar.gold;
	g_Console.writeToBuffer(c, oss.str(), 0xE);		//Prints out number of Gold.
	oss.str("");

	c.X = 4;
	c.Y += 2;

	g_Console.writeToBuffer(c, redText);
	c.X = sizeof(redText) + 4;

	oss << g_sChar.redKey;
	g_Console.writeToBuffer(c, oss.str(), 0xC);		//Prints out number of Red Keys.
	oss.str("");

	c.X = 4;
	c.Y += 2;

	g_Console.writeToBuffer(c, greenText);
	c.X = sizeof(greenText) + 4;

	oss << g_sChar.greenKey;
	g_Console.writeToBuffer(c, g_sChar.greenKey + '0', 0xA);		//Prints out number of Green Keys.
	oss.str("");
}