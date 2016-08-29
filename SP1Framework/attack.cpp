#include "attack.h"

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

	AttStats();
	MonsterAtt();
}
void UIStats()
{
	COORD c;
	c.X = 55;
	c.Y = 3;

	ostringstream oss;

	for (int u = 0; u < numberOfEnemy; u++)
	{
		if (g_sEnemy[0][u].bIsFighting && !g_sEnemy[0][u].bIsDead)
		{
			oss << "Health: ";
			g_Console.writeToBuffer(c, oss.str());
			oss.str("");

			c.X += 15;

			oss << g_sEnemy[0][u].health;
			g_Console.writeToBuffer(c, oss.str());
			oss.str("");
		}
	}

	c.X = 50;
	c.Y = 28;

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

void AttStats()
{
	COORD c;
	c.X = 50;
	c.Y = 25;

	ostringstream oss;
	vector <string> Attacks{ "Flame Rage", "Storm Flash", "Fortify", "" };

	if (AttackChoice == 3)
	{
		oss << Attacks.at(AttackChoice);
	}
	else if (AttackChoice != 3 && Attacked)
	{
		oss << "Player used " << Attacks.at(AttackChoice);
	}

	g_Console.writeToBuffer(c, oss.str(), 0xA);
	oss.str("");
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
	vector <string> Attacks{ "Flame Rage", "Storm Flash", "Fortify", " "};

	oss << Attacks.at(0) << " - 4HP";
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 29;

	oss << Attacks.at(1) << " - 5HP";
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 5;
	c.Y = 32;

	oss << Attacks.at(2) << " + 2DEF";
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
		AttSelected();	
		Wait = g_dElapsedTime + 0.125;
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
	if (AttackChoice == 0 && !Attacked)
	{
		for (int u = 0; u < numberOfEnemy; u++)
		{
			if (g_sEnemy[0][u].bIsFighting)
			{
				g_sEnemy[0][u].health -= 10;
			}
			if (g_sEnemy[0][u].health <= 0)
			{
				g_sEnemy[0][u].bIsDead = true;
				g_eGameState = S_GAME;
			}
		}

		Attacked = true;
	}
	if (AttackChoice == 1 && !Attacked)
	{
		for (int u = 0; u < numberOfEnemy; u++)
		{
			if (g_sEnemy[0][u].bIsFighting)
			{
				g_sEnemy[0][u].health -= 20;
			}
			if (g_sEnemy[0][u].health <= 0)
			{
				g_sEnemy[0][u].bIsDead = true;
				g_eGameState = S_GAME;
			}
		}

		Attacked = true;
	}
	if (AttackChoice == 2 && !Attacked)
	{
		for (int u = 0; u < numberOfEnemy; u++)
		{
			if (g_sEnemy[0][u].bIsFighting)
			{
				if (g_sChar.defence < 16)
				{
					g_sChar.defence += 2;
				}
			}
			if (g_sEnemy[0][u].health <= 0)
			{
				g_sEnemy[0][u].bIsDead = true;
				g_eGameState = S_GAME;
			}
		}

		Attacked = true;
	}
}

void MonsterAtt()
{
	COORD c;
	c.X = 50;
	c.Y = 25;

	ostringstream oss;
	vector <string> MonsterAtt{ "Piercing Rage", "Ghostly Ghibus", "Acid Bile", ""};
	
	if (MonsterChoice == 3)
	{
		oss << MonsterAtt.at(MonsterChoice);
		g_Console.writeToBuffer(c, oss.str());
		oss.str("");
	}
	else if (MonsterChoice != 3)
	{
		oss << "Monster used " << MonsterAtt.at(MonsterChoice);
		g_Console.writeToBuffer(c, oss.str(), 0xA);
		oss.str("");
	}
}
void MonsterSelect()
{
	int Choice = rand() % 4 + 1;
	MonsterChoice = Choice;


}