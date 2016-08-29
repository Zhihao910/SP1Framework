#include "global.h"

int ActionSelection = 0;
int AttackSelection = 0;
int ActionChoice = 3;
int AttackChoice = 3;
bool Used = false;
double Wait;

void PrintCombat()
{
	CombatScreen(); // Always first to render.
	CombatUI();
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

void CombatUI()
{
	UIStats();
	UIChoice();
	UISelected();
}
void UIStats()
{
	COORD c;
	c.X = 50;
	c.Y = 28;

	ostringstream oss;

	oss << "Health: ";
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X += sizeof(oss.str()) - 4;

	oss << g_sChar.health;
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.Y += 2;
	c.X = 50;

	oss << "Attack: ";
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X += sizeof(oss.str()) - 4;

	oss << g_sChar.attack;
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.Y += 2;
	c.X = 50;

	oss << "Defence: ";
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X += sizeof(oss.str()) - 4;

	oss << g_sChar.defence;
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");
}
void UIChoice()
{
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_RETURN] = isKeyPressed(VK_RETURN);

	COORD c;
	c.X = 5;
	c.Y = 26;

	ostringstream oss;
	vector <string> Choice{ "Attack", "Inventory", "Escape" };

	oss << Choice.at(0);
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 29;

	oss << Choice.at(1);
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 5;
	c.Y = 32;

	oss << Choice.at(2);
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	if (ActionSelection == 0)					// Attack Selected
	{
		if (g_abKeyPressed[K_DOWN])
		{
			ActionSelection = 2;
		}
		if (g_abKeyPressed[K_RIGHT])
		{
			ActionSelection = 1;
		}
	}

	if (ActionSelection == 1)					// Inventory Selected
	{
		if (g_abKeyPressed[K_LEFT])
		{
			ActionSelection = 0;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			ActionSelection = 2;
		}
	}

	if (ActionSelection == 2)					// Escape Selected
	{
		if (g_abKeyPressed[K_UP])
		{
			ActionSelection = 0;
		}
		if (g_abKeyPressed[K_RIGHT])
		{
			ActionSelection = 1;
		}
	}

	if (g_abKeyPressed[K_RETURN])
	{
		if (!Used)
		{
			ActionChoice = ActionSelection;
			Wait = g_dElapsedTime + 0.125;
			Used = true;
		}
	}

	switch (ActionSelection)
	{
	case 0:
		c.X = 5;
		c.Y = 26;
		oss << Choice.at(ActionSelection);
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");
		break;

	case 1:
		c.X = 29;
		c.Y = 26;
		oss << Choice.at(ActionSelection);
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");
		break;

	case 2:
		c.X = 5;
		c.Y = 32;
		oss << Choice.at(ActionSelection);
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");
		break;
	}
}
void UISelected()
{
	if (ActionChoice == 0)
	{
		AttChoice();
	}

	if (ActionChoice == 1)
	{
		//Inventory();
	}

	if (ActionChoice == 2)
	{
		//Escape();
	}
}

void AttChoice()
{
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_RETURN] = isKeyPressed(VK_RETURN);

	COORD c;
	c.X = 5;
	c.Y = 26;

	ostringstream oss;
	vector <string> Attacks{ "Flame Rage", "Storm Flash", "Fortify" };

	oss << Attacks.at(0);
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 29;

	oss << Attacks.at(1);
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 5;
	c.Y = 32;

	oss << Attacks.at(2);
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	if (Wait > g_dElapsedTime)
		return;

	if (AttackSelection == 0)					// Attack Selected
	{
		if (g_abKeyPressed[K_DOWN])
		{
			AttackSelection = 2;
		}
		if (g_abKeyPressed[K_RIGHT])
		{
			AttackSelection = 1;
		}
	}

	if (AttackSelection == 1)					// Inventory Selected
	{
		if (g_abKeyPressed[K_LEFT])
		{
			AttackSelection = 0;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			AttackSelection = 2;
		}
	}

	if (AttackSelection == 2)					// Escape Selected
	{
		if (g_abKeyPressed[K_UP])
		{
			AttackSelection = 0;
		}
		if (g_abKeyPressed[K_RIGHT])
		{
			AttackSelection = 1;
		}
	}

	if (g_abKeyPressed[K_RETURN])
	{
		AttackChoice = AttackSelection;
		Wait = g_dElapsedTime + 0.125;

		AttSelected();
	}

	switch (AttackSelection)
	{
	case 0:
		c.X = 5;
		c.Y = 26;
		oss << Attacks.at(AttackSelection);
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");
		break;

	case 1:
		c.X = 29;
		c.Y = 26;
		oss << Attacks.at(AttackSelection);
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");
		break;

	case 2:
		c.X = 5;
		c.Y = 32;
		oss << Attacks.at(AttackSelection);
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");
		break;
	}
}
void AttSelected()
{
	if (AttackChoice == 0)
	{
		g_sEnemy[1][1].health -= 4;

		if (g_sEnemy[1][1].health <= 0)
		{
			g_eGameState = S_DEATH;
		}
	}

	if (AttackChoice == 1)
	{
		g_sEnemy[2][8].health -= 3;

		if (g_sEnemy[2][8].health <= 0)
		{
			g_eGameState = S_DEATH;
		}
	}

	if (AttackChoice == 2)
	{
		g_sChar.defence += 2;
	}
}