#include "traps.h"	

void spikeTrap() // gray trap
{
	g_sChar.health -= 1;

	if (g_sChar.health < 1)
	{
		g_eGameState = S_DEATH;
	}
}

void fireTrap() // red trap
{
	g_sChar.health -= 2;

	if (g_sChar.health < 1)
	{
		g_eGameState = S_DEATH;
	}
}

void poisonTrap() // purple trap
{
	g_sChar.health -= 3;
	if (g_sChar.health < 1)
	{
		g_eGameState = S_DEATH;
	}
}

void pitTrap() // brown floor trap
{
	g_sChar.health = 0;
	g_eGameState = S_DEATH;
}