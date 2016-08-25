#include "Fog.h"

void renderFog()
{
	const short fogWidth = 10;
	const short fogHeight = 5;

	for (short row = 0; row < 100; row++)
	{
		for (short col = 0; col < 100; col++)
		{
			COORD playerPos = g_sChar.m_cLocation;

			if (playerPos.X >= (col - fogWidth) && playerPos.X <= (col + fogWidth) && playerPos.Y <= (row + fogHeight) && playerPos.Y >= (row - fogHeight))
			{
				continue;
			}

			else
			{
				g_Console.writeToBuffer(col, row, ' ', 0x0);
			}
		}
	}
}