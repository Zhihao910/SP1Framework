#include "game.h"

void Portal()
{
	 if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == 'A')
	{
		g_sChar.m_cLocation.X = 9;
		g_sChar.m_cLocation.Y = 9;
	}
	 if ((map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1]) == 'B')
	 {
		 g_sChar.m_cLocation.X = 7;
		 g_sChar.m_cLocation.Y = 6;
	 }
}