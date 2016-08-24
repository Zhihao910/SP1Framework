#include "game.h"

void Portal()
{
	if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == 'A') // LEVEL 4
	{
		g_sChar.m_cLocation.X = 69;
		g_sChar.m_cLocation.Y = 8;
	}
	if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == 'B') // LEVEL 4
	{
		g_sChar.m_cLocation.X = 30;
		g_sChar.m_cLocation.Y = 4;
	}

	if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == 'C') // LEVEL 5
	{
		g_sChar.m_cLocation.X = 60;
		g_sChar.m_cLocation.Y = 16;
	}
	if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == 'D') // LEVEL 5
	{
		g_sChar.m_cLocation.X = 9;
		g_sChar.m_cLocation.Y = 4;
	}

	if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == 'E') // LEVEL 5
	{
		g_sChar.m_cLocation.X = 9;
		g_sChar.m_cLocation.Y = 19;
	}

	if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == 'F') // LEVEL 5
	{
		g_sChar.m_cLocation.X = 72;
		g_sChar.m_cLocation.Y = 4;
	}
}