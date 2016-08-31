#include "attack.h"

void PrintCombat()
{
	CombatScreen(); // Always first to render.
	PlayerStats();

	switch (g_eCombatState)
	{
	case C_UI: UserInterface();
		break;

	case C_ATTACK: Attack();
		break;

	case C_INVENTORY: Inventory();
		break;

	case C_ESCAPE: RunAway();
		break;

	case C_ENEMYATTACK: EnemyAttack();
		break;

	case A_ATTACK: PlayerAttack();
		break;
	}
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

void PlayerStats()
{
	COORD c;
	c.X = 50;
	c.Y = 26;

	ostringstream oss;
	
	oss << "Health: " << g_sChar.health;
	g_Console.writeToBuffer(c, oss.str(), 0xA);
	oss.str("");

	c.X = 50;
	c.Y = 29;

	oss << "Defence: " << g_sChar.defence;
	g_Console.writeToBuffer(c, oss.str(), 0x3);
	oss.str("");

	c.X = 50;
	c.Y = 32;

	oss << "Attack: " << g_sChar.attack;
	g_Console.writeToBuffer(c, oss.str(), 0xC);
	oss.str("");

	c.X = 35;
	c.Y = 4;

	for (int i = 0; i < numberOfEnemy; i++)
	{
		if (g_sEnemy[0][i].bIsFighting)
		{
			oss << "Health: " << g_sEnemy[0][i].health;
			g_Console.writeToBuffer(c, oss.str(), 0xC);
			oss.str("");
		}
	}
}

void UserInterface()
{
	COORD c;
	c.X = 4;
	c.Y = 26;

	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_RETURN] = isKeyPressed(VK_RETURN);

	EnterPressed = false;
	ostringstream oss;
	vector <string> UserInter{ "Attack", "Potions", "Run Away" };

	oss << UserInter.at(0);					// Displays the option: Attack
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 27;
	c.Y = 26;

	oss << UserInter.at(1);					// Displayers the option: Potions
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 4;
	c.Y = 32;

	oss << UserInter.at(2);					// Displayers the option: Run
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	///////////////////////////////////////////////////////////
	// 1. Prints out Highlighted Option over normal options. //
	// 2. Logic for moving Highlight if arrowkeys pressed.   //
	///////////////////////////////////////////////////////////

	switch (Highlighted)
	{
	case 0:		// ATTACK OPTION is currently highlighted.
		c.X = 4;
		c.Y = 26;
		if (g_abKeyPressed[K_RIGHT])
		{
			Highlighted = 1;
			c.X = 27;
			c.Y = 26;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			Highlighted = 2;
			c.X = 4;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_RETURN])
		{
			if (EnterWait < g_dElapsedTime)
			{
				Highlighted = 0;
				g_eCombatState = C_ATTACK;
				EnterPressed = true;
			}	
		}
		break;

	case 1:		// POTIONS OPTION is currently highlighted.
		c.X = 27;
		c.Y = 26;
		if (g_abKeyPressed[K_LEFT])
		{
			Highlighted = 0;
			c.X = 4;
			c.Y = 26;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			Highlighted = 2;
			c.X = 4;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_RETURN])
		{
			if (EnterWait < g_dElapsedTime)
			{
				Highlighted = 0;
				g_eCombatState = C_INVENTORY;
				EnterPressed = true;
			}
		}
		break;

	case 2:		// RUN AWAY OPTION is currently highlighted.
		c.X = 4;
		c.Y = 32;
		if (g_abKeyPressed[K_UP])
		{
			Highlighted = 0;
			c.X = 4;
			c.Y = 26;
		}
		if (g_abKeyPressed[K_RIGHT])
		{
			Highlighted = 1;
			c.X = 27;
			c.Y = 26;
		}
		if (g_abKeyPressed[K_RETURN])
		{
			if (EnterWait < g_dElapsedTime)
			{
				Highlighted = 0;
				g_eCombatState = C_ESCAPE;
				EnterPressed = true;
			}		
		}
		break;
	}

	if (EnterPressed)
	{
		EnterWait = g_dElapsedTime + 0.5;
	}

	oss << UserInter.at(Highlighted);		// Displays the highlighted option
	g_Console.writeToBuffer(c, oss.str(), 0xA);
	oss.str("");
}

void Attack()
{
	COORD c;
	c.X = 4;
	c.Y = 26;

	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_RETURN] = isKeyPressed(VK_RETURN);

	EnterPressed = false;
	ostringstream oss;
	vector <string> Attacks{ "Ice Strike", "Extrapolated Mass", "Inception", "== BACK ==" };

	oss << Attacks.at(0);					// Displays the option: Ice Strike 
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 27;

	oss << Attacks.at(1);					// Displayers the option: Extrapolated Mass
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 4;
	c.Y = 32;

	oss << Attacks.at(2);					// Displayers the option: Inception
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 27;
	c.Y = 32;

	oss << Attacks.at(3);					// Displayers the option: == BACK ==
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	///////////////////////////////////////////////////////////
	// 1. Prints out Highlighted Option over normal options. //
	// 2. Logic for moving Highlight if arrowkeys pressed.   //
	///////////////////////////////////////////////////////////

	switch (Highlighted)
	{
	case 0:		// ICE STRIKE is currently highlighted.
		c.X = 4;
		c.Y = 26;
		if (g_abKeyPressed[K_RIGHT])
		{
			Highlighted = 1;
			c.X = 27;
			c.Y = 26;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			Highlighted = 2;
			c.X = 4;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_RETURN])
		{
			if (EnterWait < g_dElapsedTime && !EnterPressed)
			{
				AttackDamage = 10;
				g_eCombatState = A_ATTACK;
				EnterPressed = true;
			}	
		}
		break;

	case 1:		// EXTRAPOLATED MASS is currently highlighted.
		c.X = 27;
		c.Y = 26;
		if (g_abKeyPressed[K_LEFT])
		{
			Highlighted = 0;
			c.X = 4;
			c.Y = 26;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			Highlighted = 3;
			c.X = 27;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_RETURN])
		{
			if (EnterWait < g_dElapsedTime && !EnterPressed)
			{
				AttackDamage = 6;
				g_eCombatState = A_ATTACK;
				EnterPressed = true;
			}
		}
		break;

	case 2:		// INCEPTION is currently highlighted.
		c.X = 4;
		c.Y = 32;
		if (g_abKeyPressed[K_UP])
		{
			Highlighted = 0;
			c.X = 4;
			c.Y = 26;
		}
		if (g_abKeyPressed[K_RIGHT])
		{
			Highlighted = 3;
			c.X = 27;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_RETURN])
		{
			if (EnterWait < g_dElapsedTime && !EnterWait)
			{
				AttackDamage = 5;
				g_eCombatState = A_ATTACK;
				EnterPressed = true;
			}	
		}
		break;

	case 3:		// == BACK == is currently highlighted.
		c.X = 27;
		c.Y = 32;
		if (g_abKeyPressed[K_UP])
		{
			Highlighted = 1;
			c.X = 27;
			c.Y = 26;
		}
		if (g_abKeyPressed[K_LEFT])
		{
			Highlighted = 2;
			c.X = 4;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_RETURN])
		{
			if (EnterWait < g_dElapsedTime)
			{
				Highlighted = 0;
				g_eCombatState = C_UI;
				EnterPressed = true;
			}		
		}
		break;
	}

	if (EnterPressed)
	{
		EnterWait = g_dElapsedTime + 0.5;
	}

	oss << Attacks.at(Highlighted);		// Displays the highlighted option
	g_Console.writeToBuffer(c, oss.str(), 0xA);
	oss.str("");
}
void Inventory()
{
	COORD c;
	c.X = 4;
	c.Y = 26;

	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_RETURN] = isKeyPressed(VK_RETURN);

	EnterPressed = false;
	ostringstream oss;
	vector <string> Potions{ "Health Elixir", "Lug of Strength", "Shielded Ward", "== BACK ==" };

	oss << Potions.at(0);					// Displays the option: Ice Strike 
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 27;

	oss << Potions.at(1);					// Displayers the option: Extrapolated Mass
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 4;
	c.Y = 32;

	oss << Potions.at(2);					// Displayers the option: Inception
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 27;
	c.Y = 32;

	oss << Potions.at(3);					// Displayers the option: == BACK ==
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	///////////////////////////////////////////////////////////
	// 1. Prints out Highlighted Option over normal options. //
	// 2. Logic for moving Highlight if arrowkeys pressed.   //
	///////////////////////////////////////////////////////////

	switch (Highlighted)
	{
	case 0:		// HEALTH ELIXIR is currently highlighted.
		c.X = 4;
		c.Y = 26;
		if (g_abKeyPressed[K_RIGHT])
		{
			Highlighted = 1;
			c.X = 27;
			c.Y = 26;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			Highlighted = 2;
			c.X = 4;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_RETURN])
		{
			if (EnterWait < g_dElapsedTime)
			{
				if (g_sChar.health <= 30)
				{
					g_sChar.health = g_sChar.health + 10;
				}
				if (g_sChar.health > 30)
				{
					g_sChar.health = 30;
				}
				EnterPressed = true;
				g_eCombatState = C_ENEMYATTACK;
			}
		}
		break;

	case 1:		// LUG OF STRENGTH is currently highlighted.
		c.X = 27;
		c.Y = 26;
		if (g_abKeyPressed[K_LEFT])
		{
			Highlighted = 0;
			c.X = 4;
			c.Y = 26;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			Highlighted = 3;
			c.X = 27;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_RETURN])
		{
			if (EnterWait < g_dElapsedTime)
			{
				if (g_sChar.attack <= 15)
				{
					g_sChar.attack = g_sChar.attack + 4;
				}
				if (g_sChar.attack > 15)
				{
					g_sChar.attack = 15;
				}
				EnterPressed = true;
				g_eCombatState = C_ENEMYATTACK;
			}
		}
		break;

	case 2:		// SHIELDED WARD is currently highlighted.
		c.X = 4;
		c.Y = 32;
		if (g_abKeyPressed[K_UP])
		{
			Highlighted = 0;
			c.X = 4;
			c.Y = 26;
		}
		if (g_abKeyPressed[K_RIGHT])
		{
			Highlighted = 3;
			c.X = 27;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_RETURN])
		{
			if (EnterWait < g_dElapsedTime)
			{
				if (g_sChar.defence <= 16)
				{
					g_sChar.defence = g_sChar.defence + 5;
				}
				if (g_sChar.defence > 16)
				{
					g_sChar.defence = 16;
				}
				EnterPressed = true;
				g_eCombatState = C_ENEMYATTACK;
			}
		}
		break;

	case 3:		// == BACK == is currently highlighted.
		c.X = 27;
		c.Y = 32;
		if (g_abKeyPressed[K_UP])
		{
			Highlighted = 1;
			c.X = 27;
			c.Y = 26;
		}
		if (g_abKeyPressed[K_LEFT])
		{
			Highlighted = 2;
			c.X = 4;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_RETURN])
		{
			if (EnterWait < g_dElapsedTime)
			{
				Highlighted = 0;
				g_eCombatState = C_UI;
				EnterPressed = true;
			}
		}
		break;
	}

	if (EnterPressed)
	{
		EnterWait = g_dElapsedTime + 0.5;
	}

	oss << Potions.at(Highlighted);		// Displays the highlighted option
	g_Console.writeToBuffer(c, oss.str(), 0xA);
	oss.str("");
}
void RunAway()
{
	for (int i = 0; i < numberOfEnemy; i++)
	{
		if (g_sChar.health > 0 && g_sEnemy[0][i].health > 0 && g_sEnemy[0][i].bIsFighting)
		{
			g_sEnemy[0][i].bIsFighting = false;
			g_sEnemy[0][i].bIsDead = true;
			g_eGameState = S_GAME;
		}
	}
}

void PlayerAttack()
{
	for (int i = 0; i < numberOfEnemy; i++)
	{
		if (g_sEnemy[0][i].bIsFighting && !g_sEnemy[0][i].bIsDead)
		{
			Damage = (g_sChar.attack + AttackDamage) - g_sEnemy[0][i].defence;

			if (Damage <= 0)
			{
				Damage = 0;
			}

			eHealthLeft = g_sEnemy[0][i].health - Damage;
			g_sEnemy[0][i].health = eHealthLeft;

			if (g_sEnemy[0][i].health <= 0)
			{
				g_sEnemy[0][i].bIsFighting = false;
				g_sEnemy[0][i].bIsDead = true;
				g_eGameState = S_GAME;
			}

			else if (g_sEnemy[0][i].health > 0)
			{
				EnterPressed2 = true;
				g_eCombatState = C_ENEMYATTACK;
			}
		}
	}
}
void EnemyAttack()
{
	COORD c;
	c.X = 4;
	c.Y = 26;

	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	ostringstream oss;

	if (EnterPressed)
	{
		if (!SetAttack)
		{
			srand(time(NULL));
			RandomAttack = rand() % 4;
			RandomDamage = rand() % 10 + 1;
			SetAttack = true;
		}

		switch (RandomAttack)
		{
		case 0:
			Damage = RandomDamage + g_sChar.attack;
			break;
		case 1:
			Damage = RandomDamage + g_sChar.gold;
			break;
		case 2:
			Damage = RandomDamage + g_sChar.redKey;
			break;
		case 3:
			Damage = RandomDamage + 7;
			break;
		}

		DamageLeft = Damage - g_sChar.defence;

		if (DamageLeft <= 0)
		{
			DamageLeft = 0;
		}

		oss << "PRESS";
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");

		c.X = 27;
		c.Y = 26;

		oss << "SPACE";
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");

		c.X = 4;
		c.Y = 32;

		oss << "TO";
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");

		c.X = 26;
		c.Y = 32;

		oss << "CONTINUE.";
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");

		c.X = 21;
		c.Y = 22;

		oss << "Monster attacked with " << DamageLeft << " damage!";
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");
		
		if (EnterPressed2)
		{
			EnterWait = g_dElapsedTime + 0.125;
			EnterPressed2 = false;
		}

		if (g_abKeyPressed[K_SPACE])
		{
			if (EnterWait < g_dElapsedTime)
			{
				HealthLeft = g_sChar.health - DamageLeft;
				g_sChar.health = HealthLeft;

				if (g_sChar.health <= 0)
				{
					g_eGameState = S_DEATH;
				}
				SetAttack = false;
				g_eCombatState = C_UI;
			}	
		}
	}
}