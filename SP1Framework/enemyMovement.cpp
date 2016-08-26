#include "collisionDetection.h"

void enemyMove() // Enemy Random Movement
{
	for (int i = 0; i < enemyType; i++)
	{
		for (int x = 0; x < numberOfEnemy; x++)
		{
			g_sEnemy[i][x].bSomethingHappened = false;
			if (g_sEnemy[i][x].slowDownTime > g_dElapsedTime)
				return;

			switch (g_sEnemy[i][x].random)
			{
			case 1: //Enemy Up Movement
			{
				if ((map[g_sEnemy[i][x].m_cLocation.X][g_sEnemy[i][x].m_cLocation.Y - 2]) != char(219)) // Check if it's a wall.
				{
					if ((g_sEnemy[i][x].m_cLocation.X != g_sChar.m_cLocation.X) && (g_sEnemy[i][x].m_cLocation.Y - 2 != g_sChar.m_cLocation.Y - 1)) // Check Enemy X/Y and Player X/Y
					{
						g_sEnemy[i][x].m_cLocation.Y--;
					}

					else
					{
						g_sEnemy[i][x].m_cLocation.Y++;
					}
				}

				else
				{
					while (g_sEnemy[i][x].random == g_sEnemy[i][x].tempCheck)
					{
						g_sEnemy[i][x].random = rand() % 4 + 1;
					}
				}
				g_sEnemy[i][x].bSomethingHappened = true;
				break;
			}
			case 2: //Enemy Down Movement
			{
				if ((map[g_sEnemy[i][x].m_cLocation.X][g_sEnemy[i][x].m_cLocation.Y]) != char(219))
				{
					if ((g_sEnemy[i][x].m_cLocation.X != g_sChar.m_cLocation.X) && (g_sEnemy[i][x].m_cLocation.Y != g_sChar.m_cLocation.Y - 1)) 
					{
						g_sEnemy[i][x].m_cLocation.Y++;
					}
					else
					{
						g_sEnemy[i][x].m_cLocation.Y--;
					}
				}
				else
				{
					while (g_sEnemy[i][x].random == g_sEnemy[i][x].tempCheck)
					{
						g_sEnemy[i][x].random = rand() % 4 + 1;
					}
				}

				g_sEnemy[i][x].bSomethingHappened = true;
				break;
			}
			case 3: //Enemy Right Movement			
			{
				if ((map[g_sEnemy[i][x].m_cLocation.X + 1][g_sEnemy[i][x].m_cLocation.Y - 1]) != char(219))
				{
					if ((g_sEnemy[i][x].m_cLocation.X + 1 != g_sChar.m_cLocation.X) && (g_sEnemy[i][x].m_cLocation.Y != g_sChar.m_cLocation.Y - 1))
					{
						g_sEnemy[i][x].m_cLocation.X++;
					}
					else
					{
						g_sEnemy[i][x].m_cLocation.X--;
					}
				}
				else
				{
					while (g_sEnemy[i][x].random == g_sEnemy[i][x].tempCheck)
					{
						g_sEnemy[i][x].random = rand() % 4 + 1;
					}
				}
				g_sEnemy[i][x].bSomethingHappened = true;
				break;
			}
			case 4: //Enemy Left Movement
			{
				if ((map[g_sEnemy[i][x].m_cLocation.X - 1][g_sEnemy[i][x].m_cLocation.Y - 1]) != char(219))
				{
					if ((g_sEnemy[i][x].m_cLocation.X - 1 != g_sChar.m_cLocation.X) && (g_sEnemy[i][x].m_cLocation.Y != g_sChar.m_cLocation.Y - 1))
					{
						g_sEnemy[i][x].m_cLocation.X--;
					}
					else
					{
						g_sEnemy[i][x].m_cLocation.X++;
					}
				}
				else
				{
					while (g_sEnemy[i][x].random == g_sEnemy[i][x].tempCheck)
					{
						g_sEnemy[i][x].random = rand() % 4 + 1;
					}
				}
				g_sEnemy[i][x].bSomethingHappened = true;
				break;
			}
			}
			if (g_sEnemy[i][x].bSomethingHappened)
			{
				// set the bounce time to some time in the future to prevent accidental triggers
				g_sEnemy[i][x].slowDownTime = g_dElapsedTime + 0.5f; // Speed.
			}
			g_sEnemy[i][x].tempCheck = g_sEnemy[i][x].random;
		}
	}
}