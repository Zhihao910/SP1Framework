#include "loadText.h"

void Instructions()
{

	int height = 0;
	int width;
	string line = "";
	ifstream myfile("Instructions.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (width = 0; width < 85; width++)
			{
				text[height][width] = line[width];
			}
			height++;
		}
		myfile.close();
	}
}