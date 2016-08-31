#include "highScore.h"


void HighScore(int score)
{
	COORD c = g_Console.getConsoleSize();
	c.X /= 3;
	c.Y = (c.Y / 3) - 2;

	HighScoreBox();

	int highScore;
	ostringstream oss;

	ifstream InFile("Screens/HighScore.txt");
	if (InFile.is_open())
	{
		InFile >> highScore;

		if (score < highScore)
		{
			oss << "You didn't beat the previous highscore!";
			g_Console.writeToBuffer(c, oss.str(), 0xC);
			oss.str("");

			c.Y += 2;

			oss << "Your Score: " << score;
			g_Console.writeToBuffer(c, oss.str());
			oss.str("");

			c.Y += 2;

			oss << "Current Highscore: " << highScore;
			g_Console.writeToBuffer(c, oss.str());
			oss.str("");

			c.Y += 2;

			oss << "Press 'ESC' to go back to Main Menu.";
			g_Console.writeToBuffer(c, oss.str(), 0x3);
			oss.str("");
		}

		if (score >= highScore)
		{
			oss << "You beat the previous highscore!";
			g_Console.writeToBuffer(c, oss.str(), 0xA);
			oss.str("");

			c.Y += 2;

			oss << "Your Score: " << score;
			g_Console.writeToBuffer(c, oss.str());
			oss.str("");

			c.Y += 2;

			oss << "Previous Highscore: " << highScore;
			g_Console.writeToBuffer(c, oss.str());
			oss.str("");

			c.Y += 2;

			oss << "Press 'ESC' to go back to Main Menu.";
			g_Console.writeToBuffer(c, oss.str(), 0x3);
			oss.str("");

			highScore = score;
		}
		InFile.close();
	}

	ofstream OutFile("Screens/HighScore.txt");
	if (OutFile.is_open())
	{
		OutFile << highScore;
	}

	OutFile.close();
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