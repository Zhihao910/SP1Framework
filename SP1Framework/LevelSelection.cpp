#include "loadText.h"

void LevelSelect()
{

	int height = 0;
	int width;
	string line = "";
	ifstream myfile("LevelSelection.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (width = 0; width < 50; width++)
			{
				text[height][width] = line[width];
			}
			height++;
		}
		myfile.close();
	}
}