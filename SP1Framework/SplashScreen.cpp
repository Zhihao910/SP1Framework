#include "loadText.h"

void SplashScreen()
{

	int height = 0;
	int width;
	string line = "";
	ifstream myfile("Splashscreen.txt");

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