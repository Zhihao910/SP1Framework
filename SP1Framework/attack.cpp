#include "attack.h"

void PrintCombat()
{
	int AnimTime = g_dElapsedTime;

	CombatScreen(); // Always first to render.
	if (AnimTime % 2 == 0)
	{
		if (AnimUsed)
			MonsterAnim3();
		else
			MonsterAnim1();
	}
	if (AnimTime % 3 == 0)
	{
		if (AnimUsed)
			MonsterAnim4();
	}
	if (AnimTime % 2 != 0)
	{
		if (AnimUsed)
			MonsterAnim5();
		else
			MonsterAnim2();
	}
	if (AnimTime % 3 != 0)
	{
		if (AnimUsed)
			MonsterAnim6();
	}
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


	for (int y = 0; y < 41; y++)
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
	c.X = 64;
	c.Y = 32;

	ostringstream oss;
	
	oss << "Health: " << g_sChar.health;
	g_Console.writeToBuffer(c, oss.str(), 0xA);
	oss.str("");

	c.X = 64;
	c.Y = 35;

	oss << "Defence: " << g_sChar.defence;
	g_Console.writeToBuffer(c, oss.str(), 0x3);
	oss.str("");

	c.X = 64;
	c.Y = 38;

	oss << "Attack: " << g_sChar.attack;
	g_Console.writeToBuffer(c, oss.str(), 0xC);
	oss.str("");

	c.X = 35;
	c.Y = 3;

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
	c.Y = 32;

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

	c.X = 33;
	c.Y = 32;

	oss << UserInter.at(1);					// Displayers the option: Potions
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 4;
	c.Y = 38;

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
		c.Y = 32;
		if (g_abKeyPressed[K_RIGHT])
		{
			Highlighted = 1;
			c.X = 33;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			Highlighted = 2;
			c.X = 4;
			c.Y = 38;
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
		c.X = 33;
		c.Y = 32;
		if (g_abKeyPressed[K_LEFT])
		{
			Highlighted = 0;
			c.X = 4;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			Highlighted = 2;
			c.X = 4;
			c.Y = 38;
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
		c.Y = 38;
		if (g_abKeyPressed[K_UP])
		{
			Highlighted = 0;
			c.X = 4;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_RIGHT])
		{
			Highlighted = 1;
			c.X = 33;
			c.Y = 32;
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
	c.Y = 32;

	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_RETURN] = isKeyPressed(VK_RETURN);

	EnterPressed = false;
	ostringstream oss;
	vector <string> Attacks{ "Ice Strike - 5 ATK", "Extrapolated Mass - 7 ATK", "Inception - 4 ATK", "== BACK ==" };

	oss << Attacks.at(0);					// Displays the option: Ice Strike 
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 33;
	c.Y = 32;

	oss << Attacks.at(1);					// Displayers the option: Extrapolated Mass
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 4;
	c.Y = 38;

	oss << Attacks.at(2);					// Displayers the option: Inception
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.X = 33;
	c.Y = 38;

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
		c.Y = 32;
		if (g_abKeyPressed[K_RIGHT])
		{
			Highlighted = 1;
			c.X = 33;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			Highlighted = 2;
			c.X = 4;
			c.Y = 38;
		}
		if (g_abKeyPressed[K_RETURN])
		{
			if (EnterWait < g_dElapsedTime && !EnterPressed)
			{
				AttackDamage = 5;
				g_eCombatState = A_ATTACK;
				EnterPressed = true;
			}	
		}
		break;

	case 1:		// EXTRAPOLATED MASS is currently highlighted.
		c.X = 33;
		c.Y = 32;
		if (g_abKeyPressed[K_LEFT])
		{
			Highlighted = 0;
			c.X = 4;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			Highlighted = 3;
			c.X = 33;
			c.Y = 38;
		}
		if (g_abKeyPressed[K_RETURN])
		{
			if (EnterWait < g_dElapsedTime && !EnterPressed)
			{
				AttackDamage = 7;
				g_eCombatState = A_ATTACK;
				EnterPressed = true;
			}
		}
		break;

	case 2:		// INCEPTION is currently highlighted.
		c.X = 4;
		c.Y = 38;
		if (g_abKeyPressed[K_UP])
		{
			Highlighted = 0;
			c.X = 4;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_RIGHT])
		{
			Highlighted = 3;
			c.X = 33;
			c.Y = 38;
		}
		if (g_abKeyPressed[K_RETURN])
		{
			if (EnterWait < g_dElapsedTime && !EnterPressed)
			{
				AttackDamage = 4;
				g_eCombatState = A_ATTACK;
				EnterPressed = true;
			}	
		}
		break;

	case 3:		// == BACK == is currently highlighted.
		c.X = 33;
		c.Y = 38;
		if (g_abKeyPressed[K_UP])
		{
			Highlighted = 1;
			c.X = 33;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_LEFT])
		{
			Highlighted = 2;
			c.X = 4;
			c.Y = 38;
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
	c.Y = 32;

	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_RETURN] = isKeyPressed(VK_RETURN);

	EnterPressed = false;
	ostringstream oss;
	vector <string> Potions{ "Health Elixir", "Lug of Strength", "Shielded Ward", "== BACK ==" };

	oss << Potions.at(0);					// Displays the option: Health Elixir 
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.Y += 2;

	oss << "+ 5 HEALTH";
	g_Console.writeToBuffer(c, oss.str(), 0xA);
	oss.str("");

	c.X = 33;
	c.Y = 32;

	oss << Potions.at(1);					// Displayers the option: Lug of Strength
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.Y += 2;

	oss << "+ 1 ATTACK";
	g_Console.writeToBuffer(c, oss.str(), 0xC);
	oss.str("");

	c.X = 4;
	c.Y = 38;

	oss << Potions.at(2);					// Displayers the option: Shielded 
	g_Console.writeToBuffer(c, oss.str());
	oss.str("");

	c.Y += 2;

	oss << "+ 5 DEFENCE";
	g_Console.writeToBuffer(c, oss.str(), 0xB);
	oss.str("");

	c.X = 33;
	c.Y = 38;

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
		c.Y = 32;
		if (g_abKeyPressed[K_RIGHT])
		{
			Highlighted = 1;
			c.X = 33;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			Highlighted = 2;
			c.X = 4;
			c.Y = 38;
		}
		if (g_abKeyPressed[K_RETURN])
		{
			if (EnterWait < g_dElapsedTime)
			{
				if (g_sChar.health <= 20)
				{
					g_sChar.health = g_sChar.health + 5;
				}
				if (g_sChar.health > 20)
				{
					g_sChar.health = 20;
				}
				EnterPressed = true;
				g_eCombatState = C_ENEMYATTACK;
			}
		}
		break;

	case 1:		// LUG OF STRENGTH is currently highlighted.
		c.X = 33;
		c.Y = 32;
		if (g_abKeyPressed[K_LEFT])
		{
			Highlighted = 0;
			c.X = 4;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			Highlighted = 3;
			c.X = 33;
			c.Y = 38;
		}
		if (g_abKeyPressed[K_RETURN])
		{
			if (EnterWait < g_dElapsedTime)
			{
				if (g_sChar.attack <= 10)
				{
					g_sChar.attack = g_sChar.attack + 1;
				}
				if (g_sChar.attack > 10)
				{
					g_sChar.attack = 10;
				}
				EnterPressed = true;
				g_eCombatState = C_ENEMYATTACK;
			}
		}
		break;

	case 2:		// SHIELDED WARD is currently highlighted.
		c.X = 4;
		c.Y = 38;
		if (g_abKeyPressed[K_UP])
		{
			Highlighted = 0;
			c.X = 4;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_RIGHT])
		{
			Highlighted = 3;
			c.X = 33;
			c.Y = 38;
		}
		if (g_abKeyPressed[K_RETURN])
		{
			if (EnterWait < g_dElapsedTime)
			{
				if (g_sChar.defence <= 15)
				{
					g_sChar.defence = g_sChar.defence + 5;
				}
				if (g_sChar.defence > 15)
				{
					g_sChar.defence = 15;
				}
				EnterPressed = true;
				g_eCombatState = C_ENEMYATTACK;
			}
		}
		break;

	case 3:		// == BACK == is currently highlighted.
		c.X = 33;
		c.Y = 38;
		if (g_abKeyPressed[K_UP])
		{
			Highlighted = 1;
			c.X = 33;
			c.Y = 32;
		}
		if (g_abKeyPressed[K_LEFT])
		{
			Highlighted = 2;
			c.X = 4;
			c.Y = 38;
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
		if (g_sEnemy[0][i].health > 0 && g_sEnemy[0][i].bIsFighting)
		{
			g_sEnemy[0][i].health = 0;
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
		if (g_sEnemy[0][i].bIsFighting && g_sEnemy[0][i].health > 0)
		{
			AttackDamage = AttackDamage + g_sChar.attack;
			eHealthLeft = g_sEnemy[0][i].health - AttackDamage;
			g_sEnemy[0][i].health = eHealthLeft;
			
			if (g_sEnemy[0][i].health > 0)
			{
				g_sEnemy[0][i].bIsDead = false;
				g_sEnemy[0][i].bIsFighting = true;
				g_eCombatState = C_ENEMYATTACK;
			}

			if (g_sEnemy[0][i].health <= 0)
			{
				g_sEnemy[0][i].health = 0;
				g_sEnemy[0][i].bIsDead = true;
				g_sEnemy[0][i].bIsFighting = false;
				g_sChar.gold += 10;
				g_eCombatState = C_UI;
				g_eGameState = S_GAME;
			}
		}
	}
}
void EnemyAttack()
{
	COORD c;
	c.X = 4;
	c.Y = 32;

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
			DamageLeft = 5;
		}

		oss << "PRESS";
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");

		c.X = 33;
		c.Y = 32;

		oss << "SPACE";
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");

		c.X = 4;
		c.Y = 38;

		oss << "TO";
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");

		c.X = 33;
		c.Y = 38;

		oss << "CONTINUE.";
		g_Console.writeToBuffer(c, oss.str(), 0xC);
		oss.str("");

		c.X = 21;
		c.Y = 28;

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
					newMap = true;
					setSpawn = false;
					g_eGameState = S_DEATH;
				}
				SetAttack = false;
				g_eCombatState = C_UI;
			}	
		}
	}
}

void MonsterAnim1()
{
	COORD c;
	c.X = 15;
	c.Y = 5;

	int height = 0;
	int width;
	string print = "";
	string line = "";

	ifstream myfile("Animations/MonsterAnim1.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (width = 0; width < 45; width++)
			{
				text[height][width] = line[width];
			}
			height++;
		}
		myfile.close();
	}

	for (int y = 0; y < 23; y++)
	{
		print = text[y];
		g_Console.writeToBuffer(c, print, 0xC);
		c.Y++;
	}
}
void MonsterAnim2()
{
	COORD c;
	c.X = 15;
	c.Y = 5;

	int height = 0;
	int width;
	string print = "";
	string line = "";

	ifstream myfile("Animations/MonsterAnim2.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (width = 0; width < 45; width++)
			{
				text[height][width] = line[width];
			}
			height++;
		}
		myfile.close();
	}

	for (int y = 0; y < 23; y++)
	{
		print = text[y];
		g_Console.writeToBuffer(c, print, 0xC);
		c.Y++;
	}
}
void MonsterAnim3()
{
	COORD c;
	c.X = 32;
	c.Y = 14;

	int height = 0;
	int width;
	string print = "";
	string line = "";

	ifstream myfile("Animations/MonsterAnim3.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (width = 0; width < 20; width++)
			{
				text[height][width] = line[width];
			}
			height++;
		}
		myfile.close();
	}

	for (int y = 0; y < 7; y++)
	{
		print = text[y];
		g_Console.writeToBuffer(c, print, 0xC);
		c.Y++;
	}
}
void MonsterAnim4()
{
	COORD c;
	c.X = 32;
	c.Y = 14;

	int height = 0;
	int width;
	string print = "";
	string line = "";

	ifstream myfile("Animations/MonsterAnim4.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (width = 0; width < 20; width++)
			{
				text[height][width] = line[width];
			}
			height++;
		}
		myfile.close();
	}

	for (int y = 0; y < 7; y++)
	{
		print = text[y];
		g_Console.writeToBuffer(c, print, 0xC);
		c.Y++;
	}
}
void MonsterAnim5()
{
	COORD c;
	c.X = 32;
	c.Y = 14;

	int height = 0;
	int width;
	string print = "";
	string line = "";

	ifstream myfile("Animations/MonsterAnim5.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (width = 0; width < 20; width++)
			{
				text[height][width] = line[width];
			}
			height++;
		}
		myfile.close();
	}

	for (int y = 0; y < 7; y++)
	{
		print = text[y];
		g_Console.writeToBuffer(c, print, 0xC);
		c.Y++;
	}
}
void MonsterAnim6()
{
	COORD c;
	c.X = 32;
	c.Y = 14;

	int height = 0;
	int width;
	string print = "";
	string line = "";

	ifstream myfile("Animations/MonsterAnim6.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (width = 0; width < 20; width++)
			{
				text[height][width] = line[width];
			}
			height++;
		}
		myfile.close();
	}

	for (int y = 0; y < 7; y++)
	{
		print = text[y];
		g_Console.writeToBuffer(c, print, 0xC);
		c.Y++;
	}
}