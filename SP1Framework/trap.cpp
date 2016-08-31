#include "traps.h"	

void spikeTrap()		// Gray color
{
	g_sChar.health -= 1;

	if (g_sChar.health < 1)
	{
		g_eGameState = S_DEATH;
	}
}

void fireTrap()			// Red color
{
	g_sChar.health -= 2;

	if (g_sChar.health < 1)
	{
		g_eGameState = S_DEATH;
	}
}

void poisonTrap()		// Purple color
{
	g_sChar.health -= 3;
	if (g_sChar.health < 1)
	{
		g_eGameState = S_DEATH;
	}
}

void pitTrap()			// Brown Floor color
{
	g_sChar.health = 0;
	g_eGameState = S_DEATH;
}