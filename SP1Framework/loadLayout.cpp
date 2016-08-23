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
					map[width][height] = char(32);
				}
				if (map[width][height] == '#')
				{
					map[width][height] = char(219);
				}
				if (map[width][height] == 'O')
				{
					map[width][height] = char(240);
				}
				if (map[width][height] == 'A')
				{
					map[width][height] = char(178);
				}
				if (map[width][height] == 'B')
				{
					map[width][height] = char(177);
				}
				if (map[width][height] == '1')
				{
					map[width][height] = char(169);
				}
				if (map[width][height] == '2')
				{
					map[width][height] = char(170);
				}
				width++;
			}
			width = 0;
			height++;
		}

		myfile.close();
	}
}