#include "game.h"

extern Console g_Console;
extern SGameChar g_sChar;
extern SEnemyChar g_sEnemy[2][totalEnemy];
extern EGAMESTATES g_eGameState;
extern bool bSomethingHappened;
extern bool g_abKeyPressed[K_COUNT];
extern bool	setSpawn;
extern bool	newMap;
extern int maps;
extern int enemyType;
extern int numberOfEnemy;
extern double g_dBounceTime;
extern double  g_dElapsedTime;