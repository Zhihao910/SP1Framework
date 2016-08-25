#include "collisionDetection.h"

void moveCharacter()
{
	COORD c;
	c.X = 4;
	c.Y = 24;

	bool bSomethingHappened = false;

	if (g_dBounceTime > g_dElapsedTime)
		return;

	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character

	if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0) //Move Up
	{
		g_sChar.m_cLocation.Y--;
		if (g_sChar.health < 1)
		{
			g_eGameState = S_DEATH;
		}

		bSomethingHappened = true;
		if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(219))
		{
			g_sChar.m_cLocation.Y++;
		}
		if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(240))
		{
			maps++;
			newMap = true;
			setSpawn = false;
			if (maps > 6)
			{
				g_eGameState = S_SCORE;
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
			if (g_sChar.blueKey != 0)
			{
				g_sChar.blueKey--;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ':';
			}

			if (g_sChar.blueKey == 0)
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
			g_sChar.blueKey++;
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
	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0) //Move Left
	{
		g_sChar.m_cLocation.X--;
		if (g_sChar.health < 1)
		{
			g_eGameState = S_DEATH;
		}

		bSomethingHappened = true;
		if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(219))
		{
			g_sChar.m_cLocation.X++;
		}
		if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(240))
		{
			maps++;
			newMap = true;
			setSpawn = false;
			if (maps > 6)
			{
				g_eGameState = S_SCORE;
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
			if (g_sChar.blueKey != 0)
			{
				g_sChar.blueKey--;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ':';

			}

			if (g_sChar.blueKey == 0)
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
			g_sChar.blueKey++;
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
	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y > 0) //Move Down
	{
		g_sChar.m_cLocation.Y++;
		if (g_sChar.health < 1)
		{
			g_eGameState = S_DEATH;
		}

		bSomethingHappened = true;
		if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(219))
		{
			g_sChar.m_cLocation.Y--;
		}
		if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(240))
		{
			maps++;
			newMap = true;
			setSpawn = false;
			if (maps > 6)
			{
				g_eGameState = S_SCORE;
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
			if (g_sChar.blueKey != 0)
			{
				g_sChar.blueKey--;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ':';
			}

			if (g_sChar.blueKey == 0)
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
			g_sChar.blueKey++;
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
	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X > 0) //Move Right
	{
		g_sChar.m_cLocation.X++;
		if (g_sChar.health < 1)
		{
			g_eGameState = S_DEATH;
		}

		bSomethingHappened = true;
		if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(219))
		{
			g_sChar.m_cLocation.X--;
		}
		if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == char(240))
		{
			maps++;
			newMap = true;
			setSpawn = false;
			if (maps > 6)
			{
				g_eGameState = S_SCORE;
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
			if (g_sChar.blueKey != 0)
			{
				g_sChar.blueKey--;
				map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ':';
			}

			if (g_sChar.blueKey == 0)
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
			g_sChar.blueKey++;
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
	if (g_abKeyPressed[K_SPACE])
	{
		g_sChar.m_bActive = !g_sChar.m_bActive;
		bSomethingHappened = true;
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}