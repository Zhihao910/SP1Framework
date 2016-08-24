#include "loadText.h"

void PrintDialogueBox()
{
	DialogueBox();

	COORD c = g_Console.getConsoleSize();
	c.X = 0;
	c.Y = 22;
	string line = "";

	for (int y = 0; y < 16; y++)
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
	ifstream myfile("Dialogue.txt");

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
	c.Y = 24;

	string healthText =		"Health: ";
	string goldText	=		"Amount of Gold: ";
	string redText =		"Number of Red Keys: ";
	string blueText =		"Number of Blue Keys: ";
	string deathText =		"You Died! ";

	g_Console.writeToBuffer(c, healthText);
	c.X = sizeof(goldText);
	for (int i = 0; i < g_sChar.health; i++)
	{
		g_Console.writeToBuffer(c, char(3), 0xC);				//Prints out amount of health.
		c.X += 2;
	}

	c.X = 4;
	c.Y += 4;

	g_Console.writeToBuffer(c, goldText);
	c.X = sizeof(goldText);
	g_Console.writeToBuffer(c, g_sChar.gold + '0', 0xE);		//Prints out number of Gold.

	c.X = 4;
	c.Y += 2;

	g_Console.writeToBuffer(c, redText);
	c.X = sizeof(redText);
	g_Console.writeToBuffer(c, g_sChar.redKey + '0', 0xC);		//Prints out number of Red Keys.

	c.X = 4;
	c.Y += 2;

	g_Console.writeToBuffer(c, blueText);
	c.X = sizeof(blueText);
	g_Console.writeToBuffer(c, g_sChar.blueKey + '0', 0x9);		//Prints out number of Blue Keys.
}