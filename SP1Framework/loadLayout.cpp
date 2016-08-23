#include "loadLayout.h"

void readMap(int level, int height, int width)
{
	string mapname = " ";
	g_sChar.redKey = 0;
	g_sChar.blueKey = 0;
	switch (level)
	{
	case 1: mapname = "MapLayout.txt";
		break;
	case 2: mapname = "MapLayout2.txt";
		break;
	case 3: mapname = "MapLayout3.txt";
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
				if (map[width][height] == 'A') //Red Door
				{
					map[width][height] = char(178);
				}
				if (map[width][height] == 'B') //Blue Door
				{
					map[width][height] = char(177);
				}
				if (map[width][height] == '1') //Red Key
				{
					map[width][height] = char(169);
				}
				if (map[width][height] == '2') //Blue Key
				{
					map[width][height] = char(170);
				}
				if (map[width][height] == 'G') // Gold
				{
					map[width][height] = char(233);
				}
				width++;
			}
			width = 0;
			height++;
		}

		myfile.close();
	}
}