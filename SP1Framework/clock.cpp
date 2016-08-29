#include "global.h"
#include <string>

void render_clock(double g_dDeltaTime)
{
	string str = "";
	COORD c;

	// displays time left
	c.X = 40;
	c.Y = 0;
	static double time = 120; // Time duration
	double Wait = g_dBounceTime;



	if (time > 0)
	{
		time -= g_dDeltaTime; // Time minus delta time.
	}
	str += to_string(time); // String must be placed one sentance at a time unlike cout.
	str += " Time left "; 
	

	if (g_dElapsedTime > Wait && g_dElapsedTime != 0) // Safety bounce time.
	{
		Wait = g_dElapsedTime + 1.0;
	}

	g_Console.writeToBuffer(c, str, 0xb0); // Cyan colour timer.

	if (time <= 0) // death screen.
	{
		g_eGameState = S_DEATH;
		PrintDeath();
		if (g_eGameState)
		{
			time = 3;
		}
	}
}