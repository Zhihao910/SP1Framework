#include "highScore.h"

void HighScore(int score)
{
	COORD c = g_Console.getConsoleSize();
	c.X = 15;
	c.Y = 12;

	HighScoreBox();

	int prevScore[5];
	int tempArray[4];
	int temp;
	ostringstream oss;

	ifstream InFile("Screens/HighScore.txt");
	if (InFile.is_open())
	{
		for (int i = 0; i < 5; i++)		// Reads scores from file and puts into an array.
		{
			InFile >> prevScore[i];
		}
		InFile.close();
	}

	for (int i = 0; i < 5; i++)			// Sorts the array
	{
		for (int x = i + 1; x < 5; x++)
		{
			if (prevScore[i] < prevScore[x])
			{
				temp = prevScore[x];
				prevScore[x] = prevScore[i];
				prevScore[i] = temp;
			}
		}
	}

	if (score > prevScore[0])			// If Current Score is greater than previous Highscore, rearrange Array.
	{
		int temp0 = prevScore[0];
		int temp1 = prevScore[1];
		int temp2 = prevScore[2];
		int temp3 = prevScore[3];

		prevScore[0] = score;
		prevScore[1] = temp0;
		prevScore[2] = temp1;
		prevScore[3] = temp2;
		prevScore[4] = temp3;
	}

	oss << "Your Score:" << " " << score;
	g_Console.writeToBuffer(c, oss.str(), 0xC);
	oss.str("");

	c.Y += 2;

	oss << "High Scores:";
	g_Console.writeToBuffer(c, oss.str(), 0xA);
	oss.str("");

	c.Y += 4;

	for (int i = 0; i < 5; i++)
	{
		oss << "Score" << " " << i + 1 << ":" << " " << prevScore[i];
		g_Console.writeToBuffer(c, oss.str(), 0xB);
		oss.str("");

		c.X += 15;
	}

	c.X = 15;
	c.Y = 23;

	oss << "PRESS 'ESCAPE' TO GO BACK TO MAIN MENU";
	g_Console.writeToBuffer(c, oss.str(), 0xA);
	oss.str("");

	ofstream OutFile("Screens/HighScore.txt");
	if (OutFile.is_open())
	{
		for (int i = 0; i < 5; i++)
		{
			OutFile << prevScore[i] << " ";
		}
		OutFile.close();
	}
}

void HighScoreBox()
{
	COORD c = g_Console.getConsoleSize();
	c.X = 0;
	c.Y = 0;

	int height = 0;
	int width;
	int color;
	int time = g_dElapsedTime;
	string loadLine = "";
	ifstream myfile("Screens/HighScoreLayout.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, loadLine))
		{
			for (width = 0; width < 100; width++)
			{
				text[height][width] = loadLine[width];
			}
			height++;
		}
		myfile.close();
	}

	string printLine = "";

	for (int y = 0; y < 36; y++)
	{
		if (time % 2 == 0)
		{
			if (y % 3 == 0)
			{
				color = 0x3;
			}

			if (y % 3 != 0)
			{
				color = 0x1;
			}
		}

		if (time % 2 != 0)
		{
			if (y % 2 == 0)
			{
				color = 0x9;
			}

			if (y % 2 != 0)
			{
				color = 0xB;
			}
		}

		printLine = text[y];
		g_Console.writeToBuffer(c, printLine, color);
		c.Y++;
	}
}