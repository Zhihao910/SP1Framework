#include "loadLayout.h"

void readMap(int level, int height, int width, int *numberOfEnemy)
{
	string mapname = " ";
	int typeOne = 0;
	int typeTwo = 0;
	g_sChar.redKey = 0;
	g_sChar.blueKey = 0;
	g_sChar.health = 10;
	switch (level)
	{
	case 1: mapname = "Maps/MapLayout1.txt";
		break;
	case 2: mapname = "Maps/MapLayout2.txt";
		break;
	case 3: mapname = "Maps/MapLayout3.txt";
		break;
	case 4: mapname = "Maps/MapLayout4.txt";
		break;
	case 5: mapname = "Maps/MapLayout5.txt";
		break;
	case 6: mapname = "Maps/MapLayout6.txt";
		break;
	}
	memset(map, '\0', sizeof(map[0][0]) * 100 * 50); // clear array
	ifstream myfile(mapname);
	if (myfile.is_open())
	{
		while (height < 20)
		{
			while (width < 80)
			{
				myfile >> map[width][height];
				if (map[width][height] == '.')
				{
					map[width][height] = char(176); //Floor
				}
				if (map[width][height] == '#') //Wall
				{
					map[width][height] = char(219);
				}
				if (map[width][height] == 'O') //Staircase
				{
					map[width][height] = char(240);
				}
				if (map[width][height] == '(') //Red Door
				{
					map[width][height] = char(178);
				}
				if (map[width][height] == ')') //Blue Door
				{
					map[width][height] = char(177);
				}
				if (map[width][height] == '-') //Red Key
				{
					map[width][height] = char(169);
				}
				if (map[width][height] == '+') //Blue Key
				{
					map[width][height] = char(170);
				}
				if (map[width][height] == 'G') // Gold
				{
					map[width][height] = char(233);
				}
				if (map[width][height] == 'A') // Portal level 4
				{
					map[width][height] = char(65);
				}
				if (map[width][height] == 'B') // Portal level 4
				{
					map[width][height] = char(66);
				}
				if (map[width][height] == 'C') // Portal level 4
				{
					map[width][height] = char(67);
				}
				if (map[width][height] == 'D') // Portal level 4
				{
					map[width][height] = char(68);
				}
				if (map[width][height] == 'E') // Portal level 4
				{
					map[width][height] = char(69);
				}
				if (map[width][height] == 'F') // Portal level 4
				{
					map[width][height] = char(70);
				}
				if (map[width][height] == 'f') // Fire Trap
				{
					map[width][height] = char(102);
				}
				if (map[width][height] == 'p') // Poison Trap
				{
					map[width][height] = char(112);
				}
				if (map[width][height] == 'v') // Pitfall Trap
				{
					map[width][height] = char(118);
				}
				if (map[width][height] == '^') // Spike Trap
				{
					map[width][height] = char(94);
				}
				if (map[width][height] == 'X') //Enemy type 1
				{
					g_sEnemy[0][typeOne].m_cLocation.X = width;
					g_sEnemy[0][typeOne].m_cLocation.Y = height + 1;
					g_sEnemy[0][typeOne].m_bActive = true;
					map[width][height] = char(176);
					typeOne++;
				}
				if (map[width][height] == 'T') //Enemy type 2
				{
					g_sEnemy[1][typeTwo].m_cLocation.X = width;
					g_sEnemy[1][typeTwo].m_cLocation.Y = height + 1;
					g_sEnemy[1][typeTwo].m_bActive = true;
					map[width][height] = char(176);
					typeTwo++;
				}
				width++;
			}
			width = 0;
			height++;
		}

		myfile.close();
	}
	*numberOfEnemy = typeOne + typeTwo;
}