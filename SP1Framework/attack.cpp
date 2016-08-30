#include "attack.h"

void PrintCombat()
{
	CombatScreen(); // Always first to render.
	UIStats();		// Prints player stats.
	UIChoice();		// Prints player options and highlights selected one. (Attack, Inventory, Escape)
	UISelected();	// Logic for Selected Options

	AttStats();
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

void UIStats()		// Prints out Player Stats in the UI.
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
			Used = true;
			IsBack = false;

			Wait = g_dElapsedTime + 0.125;
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
	if (!IsBack)
	{
		if (ActionChoice == 0)
		{
			AttChoice();
		}

		else if (ActionChoice == 1)
		{
			InvChoice();
		}

		else if (ActionChoice == 2)
		{
			RunAway();
		}
	}
}

///////////////////
// Player Attack //
///////////////////

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
	vector <string> Attacks{ "Flame Rage", "Storm Flash", "Fortify", "= Back ="};

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

	c.X = 29;
	c.Y = 32;

	oss << Attacks.at(3);
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	/////////////////////////////////////////
	//                                     //
	//     Controls for selected Attack    //
	//									   //
	/////////////////////////////////////////

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
			AttackSelection = 3;
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
			AttackSelection = 3;
		}
	}

	if (AttackSelection == 3)					// Escape Selected
	{
		if (g_abKeyPressed[K_UP])
		{
			AttackSelection = 1;
		}
		if (g_abKeyPressed[K_LEFT])
		{
			AttackSelection = 2;
		}
	}

	if (g_abKeyPressed[K_RETURN])				// Confirms Highlighted Attack
	{
		AttackChoice = AttackSelection;
		AttSelected();
	}

	/////////////////////////////////////////
	//                                     //
	//     Highlights selected Attack      //
	//									   //
	/////////////////////////////////////////

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

	case 3:
		c.X = 29;
		c.Y = 32;
		oss << Attacks.at(AttackSelection);
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");
		break;
	}
}
void AttSelected()
{
	/////////////////////////////////////////
	//                                     //
	//     Logic for Selected Attack       //
	//									   //
	/////////////////////////////////////////

	if (AttackChoice == 0 && !Attacked)
	{
		for (int u = 0; u < numberOfEnemy; u++)
		{
			if (g_sEnemy[0][u].bIsFighting)
			{
				g_sEnemy[0][u].health = g_sEnemy[0][u].health - (g_sChar.attack + AttackChoice);
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
				g_sEnemy[0][u].health = g_sEnemy[0][u].health - (g_sChar.attack + AttackChoice);
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

	if (AttackChoice == 3)
	{
		ActionSelection = 0;
		AttackSelection = 0;
		IsBack = true;
		Used = false;

		UIChoice();
	}
	
}

///////////////////
//  Enemy Attack //
///////////////////

void eAttSelected()
{
	if (Attacked)
	{
		if (!SetAttack)
		{
			MonsterChoice = rand() % 3;
			SetAttack = true;
		}

		if (MonsterChoice == 0)
		{
			g_sChar.health = g_sChar.health - 17;
		}

		if (MonsterChoice == 1)
		{
			g_sChar.health = g_sChar.health - 10;
		}

		if (MonsterChoice == 2)
		{
			g_sChar.health = g_sChar.health - 5;
		}
	}
}

///////////////////
//  Attack Stats //
///////////////////

void AttStats()
{
	COORD c;
	c.X = 50;
	c.Y = 25;

	int fontColor;
	ostringstream oss;
	vector <string> Attacks{ "Flame Rage", "Storm Flash", "Fortify", "" };

	if (!Attacked)
	{
		if (AttackChoice != 3)
		{
			oss << "Player used " << Attacks.at(AttackChoice);
			fontColor = 0xA;
		}
		else if (AttackChoice == 3)
		{
			oss << Attacks.at(AttackChoice);
		}
	}

	g_Console.writeToBuffer(c, oss.str(), fontColor);
	oss.str("");

}

//////////////////////
// Inventory System //
//////////////////////

void InvChoice()
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
	vector <string> Potions{ "Potion of Heal", "Potion of Armour", "Potion of Strength", "" };

	oss << Potions.at(0);
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 29;

	oss << Potions.at(1);
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 5;
	c.Y = 32;

	oss << Potions.at(2);
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	if (Wait > g_dElapsedTime)
		return;

	if (InvSelection == 0)					// Attack Selected
	{
		if (g_abKeyPressed[K_DOWN])
		{
			InvSelection = 2;
		}
		if (g_abKeyPressed[K_RIGHT])
		{
			InvSelection = 1;
		}
	}

	if (InvSelection == 1)					// Inventory Selected
	{
		if (g_abKeyPressed[K_LEFT])
		{
			InvSelection = 0;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			InvSelection = 2;
		}
	}

	if (InvSelection == 2)					// Escape Selected
	{
		if (g_abKeyPressed[K_UP])
		{
			InvSelection = 0;
		}
		if (g_abKeyPressed[K_RIGHT])
		{
			InvSelection = 2;
		}
	}

	if (g_abKeyPressed[K_ESCAPE])
	{
		Wait = g_dElapsedTime + 0.125;
		PrintCombat();
	}

	if (g_abKeyPressed[K_RETURN])
	{
		InventoryChoice = InvSelection;
		InvSelected();
		Wait = g_dElapsedTime + 0.125;
	}

	switch (InvSelection)
	{
	case 0:
		c.X = 5;
		c.Y = 26;
		oss << Potions.at(InvSelection);
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");
		break;

	case 1:
		c.X = 29;
		c.Y = 26;
		oss << Potions.at(InvSelection);
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");
		break;

	case 2:
		c.X = 5;
		c.Y = 32;
		oss << Potions.at(InvSelection);
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");
		break;

	case 3:
		c.X = 29;
		c.Y = 32;
		oss << Potions.at(InvSelection);
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");
		break;
	}
}
void InvSelected()
{
	if (InventoryChoice == 0 && g_sChar.health <= 20)
	{
		g_sChar.health = g_sChar.health + 4;
	}

	if (InventoryChoice == 1 && g_sChar.defence <= 16)
	{
		g_sChar.defence = g_sChar.defence + 3;
	}

	if (InventoryChoice == 2 && g_sChar.attack <= 18)
	{
		g_sChar.attack = g_sChar.attack + 2;
	}
}

///////////////////
// Escape System //
///////////////////

void RunAway()
{
	int Luck = rand() % 6 - 1;

	if (Luck < 6 && Luck > 4)
	{
		for (int u = 0; u < numberOfEnemy; u++)
		{
			if (g_sEnemy[0][u].bIsFighting)
			{
				g_sEnemy[0][u].bIsDead = true;
				g_eGameState = S_GAME;
			}
		}
	}

	else
	{
		g_eGameState = S_DEATH;
	}
}