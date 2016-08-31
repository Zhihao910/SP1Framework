#include "collisionDetection.h"

bool bSomethingHappened = false;
bool enableGod = false;

void moveCharacter()
{
	COORD c;
	c.X = 4;
	c.Y = 24;

	if (g_dBounceTime > g_dElapsedTime)
	{
		return;
	}
	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	/*== == == == == == == == == == == == == == == == == == == == UP MOVEMENT == == == == == == == == == == == == == == == == == == == ==*/
	if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0) //Move Up
	{
		g_sChar.m_cLocation.Y--;
		bSomethingHappened = true;
		if (!enableGod)
		{
			if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(219)) // Checks Collisions Against Wall.
			{
				g_sChar.m_cLocation.Y++;
			}
			for (int i = 0; i < enemyType; i++) // Checks Collisions Against Enemy.
			{
				for (int x = 0; x < numberOfEnemy; x++)
				{
					if ((g_sChar.m_cLocation.X == g_sEnemy[i][x].m_cLocation.X) && (g_sChar.m_cLocation.Y - 1 == g_sEnemy[i][x].m_cLocation.Y - 1))
					{
						if (g_sEnemy[i][x].health > 0)
						{
							if (AnimUsed)
							{
								AnimUsed = false;
							}

							else if (!AnimUsed)
							{
								AnimUsed = true;
							}
							g_sEnemy[i][x].bIsFighting = true;
							g_eCombatState = C_UI;
							g_eGameState = S_FIGHT;
						}
					}
				}
			}
			if (g_sChar.health < 1)
			{
				g_eGameState = S_DEATH;
			}
			if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(240)) //Portal
			{
				maps++;
				unlocked++;
				newMap = true;
				setSpawn = false;
				if (maps > 6)
				{
					g_eGameState = S_WIN;
				}
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(178)) //Red Door
			{
				if (g_sChar.redKey != 0)
				{
					g_sChar.redKey--;
					map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ':';
				}

				if (g_sChar.redKey == 0)
				{
					g_sChar.m_cLocation.Y++;
				}
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(177)) //Green Door
			{
				if (g_sChar.greenKey != 0)
				{
					g_sChar.greenKey--;
					map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ':';
				}

				if (g_sChar.greenKey == 0)
				{
					g_sChar.m_cLocation.Y++;
				}
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(169)) //Red Key
			{
				g_sChar.redKey++;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(170)) //Green Key
			{
				g_sChar.greenKey++;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(233)) //Gold
			{
				g_sChar.gold++;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(102)) //FireTrap
			{
				fireTrap();
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(112)) //PoisonTrap
			{
				poisonTrap();
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(118)) //PitfallTrap
			{
				pitTrap();
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(94)) //SpikeTrap
			{
				spikeTrap();
			}
		}
	}
	/*== == == == == == == == == == == == == == == == == == == == LEFT MOVEMENT == == == == == == == == == == == == == == == == == == == ==*/
	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0) //Move Left
	{
		g_sChar.m_cLocation.X--;
		bSomethingHappened = true;
		if (!enableGod)
		{
			if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(219)) // Checks Collisions Against Wall.
			{
				g_sChar.m_cLocation.X++;
			}
			for (int i = 0; i < enemyType; i++) // Checks Collisions Against Enemy.
			{
				for (int x = 0; x < numberOfEnemy; x++)
				{
					if ((g_sChar.m_cLocation.X == g_sEnemy[i][x].m_cLocation.X) && (g_sChar.m_cLocation.Y - 1 == g_sEnemy[i][x].m_cLocation.Y - 1) && g_sEnemy[0][x].health > 0)
					{
						if (g_sEnemy[i][x].health > 0)
						{
							if (AnimUsed)
							{
								AnimUsed = false;
							}

							else if (!AnimUsed)
							{
								AnimUsed = true;
							}
							g_sEnemy[i][x].bIsFighting = true;
							g_eCombatState = C_UI;
							g_eGameState = S_FIGHT;
						}
					}
				}
			}
			if (g_sChar.health < 1)
			{
				g_eGameState = S_DEATH;
			}
			if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(240)) //Portal
			{
				maps++;
				unlocked++;
				newMap = true;
				setSpawn = false;
				if (maps > 6)
				{
					g_eGameState = S_WIN;
				}
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(178)) //Red Door
			{
				if (g_sChar.redKey != 0)
				{
					g_sChar.redKey--;
					map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ':';
				}

				if (g_sChar.redKey == 0)
				{
					g_sChar.m_cLocation.X++;
				}
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(177)) //Green Door
			{
				if (g_sChar.greenKey != 0)
				{
					g_sChar.greenKey--;
					map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ':';

				}

				if (g_sChar.greenKey == 0)
				{
					g_sChar.m_cLocation.X++;
				}
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(169)) //Red Key
			{
				g_sChar.redKey++;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(170)) //Green Key
			{
				g_sChar.greenKey++;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(233)) //Gold
			{
				g_sChar.gold++;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(102)) //FireTrap
			{
				fireTrap();
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(112)) //PoisonTrap
			{
				poisonTrap();
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(118)) //PitfallTrap
			{
				pitTrap();
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(94)) //SpikeTrap
			{
				spikeTrap();
			}
		}
	}
	/*== == == == == == == == == == == == == == == == == == == == DOWN MOVEMENT == == == == == == == == == == == == == == == == == == == ==*/
	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y > 0) //Move Down
	{
		g_sChar.m_cLocation.Y++;
		bSomethingHappened = true;
		if (!enableGod)
		{
			if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(219)) // Checks Collisions Against Wall.
			{
				g_sChar.m_cLocation.Y--;
			}
			for (int i = 0; i < enemyType; i++) // Checks Collisions Against Enemy.
			{
				for (int x = 0; x < numberOfEnemy; x++)
				{
					if ((g_sChar.m_cLocation.X == g_sEnemy[i][x].m_cLocation.X) && (g_sChar.m_cLocation.Y - 1 == g_sEnemy[i][x].m_cLocation.Y - 1) && g_sEnemy[0][x].health > 0)
					{
						if (g_sEnemy[i][x].health > 0)
						{
							if (AnimUsed)
							{
								AnimUsed = false;
							}

							else if (!AnimUsed)
							{
								AnimUsed = true;
							}
							g_sEnemy[i][x].bIsFighting = true;
							g_eCombatState = C_UI;
							g_eGameState = S_FIGHT;
						}
					}
				}
			}
			if (g_sChar.health < 1)
			{
				g_eGameState = S_DEATH;
			}
			if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(240)) //Portal
			{
				maps++;
				unlocked++;
				newMap = true;
				setSpawn = false;
				if (maps > 6)
				{
					g_eGameState = S_WIN;
				}
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(178)) //Red Door
			{
				if (g_sChar.redKey != 0)
				{
					g_sChar.redKey--;
					map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ':';
				}

				if (g_sChar.redKey == 0)
				{
					g_sChar.m_cLocation.Y--;
				}
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(177)) //Green Door
			{
				if (g_sChar.greenKey != 0)
				{
					g_sChar.greenKey--;
					map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ':';
				}

				if (g_sChar.greenKey == 0)
				{
					g_sChar.m_cLocation.Y--;
				}
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(169)) //Red Key
			{
				g_sChar.redKey++;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}

			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(170)) //Green Key
			{
				g_sChar.greenKey++;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(233)) //Gold
			{
				g_sChar.gold++;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(102)) //FireTrap
			{
				fireTrap();
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(112)) //PoisonTrap
			{
				poisonTrap();
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(118)) //PitfallTrap
			{
				pitTrap();
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(94)) //SpikeTrap
			{
				spikeTrap();
			}
		}
	}
	/*== == == == == == == == == == == == == == == == == == == == RIGHT MOVEMENT == == == == == == == == == == == == == == == == == == == ==*/
	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X > 0) //Move Right
	{
		g_sChar.m_cLocation.X++;
		bSomethingHappened = true;
		if (!enableGod)
		{
			if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(219)) // Checks Collisions Against Wall.
			{
				g_sChar.m_cLocation.X--;
			}
			for (int i = 0; i < enemyType; i++) // Checks Collisions Against Enemy.
			{
				for (int x = 0; x < numberOfEnemy; x++)
				{
					if ((g_sChar.m_cLocation.X == g_sEnemy[i][x].m_cLocation.X) && (g_sChar.m_cLocation.Y - 1 == g_sEnemy[i][x].m_cLocation.Y - 1) && g_sEnemy[0][x].health > 0)
					{
						if (g_sEnemy[i][x].health > 0)
						{
							if (AnimUsed)
							{
								AnimUsed = false;
							}

							else if (!AnimUsed)
							{
								AnimUsed = true;
							}
							g_sEnemy[i][x].bIsFighting = true;
							g_eCombatState = C_UI;
							g_eGameState = S_FIGHT;
						}
					}
				}
			}
			if (g_sChar.health < 1)
			{
				g_eGameState = S_DEATH;
			}
			if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(240))
			{
				maps++;
				unlocked++;
				newMap = true;
				setSpawn = false;
				if (maps > 6)
				{
					g_eGameState = S_WIN;
				}
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(178)) //Red Door
			{
				if (g_sChar.redKey != 0)
				{
					g_sChar.redKey--;
					map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ':';
				}

				if (g_sChar.redKey == 0)
				{
					g_sChar.m_cLocation.X--;
				}
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(177)) //Green Door
			{
				if (g_sChar.greenKey != 0)
				{
					g_sChar.greenKey--;
					map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ':';
				}

				if (g_sChar.greenKey == 0)
				{
					g_sChar.m_cLocation.X--;
				}
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(169)) //Red Key
			{
				g_sChar.redKey++;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}

			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(170)) //Green Key
			{
				g_sChar.greenKey++;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(233)) //Gold
			{
				g_sChar.gold++;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(102)) //FireTrap
			{
				fireTrap();
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(112)) //PoisonTrap
			{
				poisonTrap();
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(118)) //PitfallTrap
			{
				pitTrap();
			}
			if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(94)) //SpikeTrap
			{
				spikeTrap();
			}
		}
	}
	if (g_abKeyPressed[K_SPACE])
	{
		if (enableGod)
		{
			enableGod = false;
		}
		else if (!enableGod)
		{
			enableGod = true;
			unlocked = 5;
		}
		g_sChar.m_bActive = !g_sChar.m_bActive;
		bSomethingHappened = true;
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}