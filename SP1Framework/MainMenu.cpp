#include "loadText.h"

void MainMenu()
{

	int height = 0;
	int width;
	string line = "";
	ifstream myfile("Mainmenu.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (width = 0; width < 92; width++)
			{
				text[height][width] = line[width];
			}
			height++;
		}
		myfile.close();
	}
}