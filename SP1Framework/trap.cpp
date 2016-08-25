#include "traps.h"	

void spikeTrap()
{
	g_sChar.health -= 1;

	if (g_sChar.health < 1)
	{
		g_eGameState = S_DEATH;
	}
}

void fireTrap()
{
	g_sChar.health -= 2;

	if (g_sChar.health < 1)
	{
		g_eGameState = S_DEATH;
	}
}

void poisonTrap()
{
	g_sChar.health -= 3;
	if (g_sChar.health < 1)
	{
		g_eGameState = S_DEATH;
	}
}

void pitTrap()
{
	g_sChar.health = 0;
	g_eGameState = S_DEATH;
}