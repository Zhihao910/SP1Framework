#include "global.h"

void render_clock(double g_dDeltaTime)
{
	// displays time left
	COORD c = g_Console.getConsoleSize();
	c.X /= 3;
	c.Y = 0;

	ostringstream oss;
	static double time = 120; // Time duration
	double Wait = g_dBounceTime;

	if (time > 0)
	{
		time -= g_dDeltaTime; // Time minus delta time.
	}

	oss << fixed << setprecision(1);
	oss << "Time left: " << time << " seconds"; // String must be placed one sentance at a time unlike cout.

	if (g_dElapsedTime > Wait && g_dElapsedTime != 0) // Safety bounce time.
	{
		Wait = g_dElapsedTime + 1.0;
	}

	g_Console.writeToBuffer(c, oss.str(), 0xB); // Cyan colour timer.

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