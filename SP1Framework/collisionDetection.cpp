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

	if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0) // Up movement
	{
		g_sChar.m_cLocation.Y--;
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
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(177)) //Blue Door
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
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(170)) //Blue Key
		{
			g_sChar.blueKey++;
			map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
		}
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(233)) //Gold
		{
			g_sChar.gold++;
			map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
		}
	}
	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0) //left movement
	{
		g_sChar.m_cLocation.X--;
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
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(177)) //Blue Door
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
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(170)) //Blue Key
		{
			g_sChar.blueKey++;
			map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
		}
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(233)) //Gold
		{
			g_sChar.gold++;
			map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
		}
	}
	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y > 0) //down movement
	{
		g_sChar.m_cLocation.Y++;
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
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(177)) //Blue Door
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

		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(170)) //Blue Key
		{
			g_sChar.blueKey++;
			map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
		}
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(233)) //Gold
		{
			g_sChar.gold++;
			map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
		}
	}
	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X > 0) //right movement
	{
		g_sChar.m_cLocation.X++;
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
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(177)) //Blue Door
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

		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(170)) //Blue Key
		{
			g_sChar.blueKey++;
			map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
		}
		if (map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == char(233)) //Gold
		{
			g_sChar.gold++;
			map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] = ' ';
		}
	}
	if (g_abKeyPressed[K_SPACE])
	{
		g_sChar.m_bActive = !g_sChar.m_bActive;
		bSomethingHappened = true;
		//PlaySound(TEXT("allahuakbar.wav"), NULL, SND_SYNC); play sounds
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}