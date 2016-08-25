#include "Fog.h"

void renderFog(int diffLevel)
{
	short fogWidth;
	short fogHeight;

	switch (diffLevel)
	{
	case 1: 
		fogWidth = 100;
		fogHeight = 50;
		break;
	case 2:
		fogWidth = 20;
		fogHeight = 20;
		break;
	case 3:
		fogWidth = 10;
		fogHeight = 10;
		break;
	case 4:
		fogWidth = 4;
		fogHeight = 4;
		break;
	case 5:
		fogWidth = 150;
		fogHeight = 100;
		break;
	}

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