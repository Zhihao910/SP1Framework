#include "game.h"

extern Console g_Console;
extern SEnemyChar g_sEnemy[2][totalEnemy];
extern EGAMESTATES g_eGameState;
extern EGAMESTATES g_eCombatState;
extern struct SGameChar g_sChar;
extern char map[100][50];
extern char text[50][100];
extern bool bSomethingHappened;
extern bool g_abKeyPressed[K_COUNT];
extern bool	setSpawn;
extern bool	newMap;
extern int difficulty;
extern int maps;
extern int unlocked;
extern int enemyType;
extern int numberOfEnemy;
extern double g_dBounceTime;
extern double g_dElapsedTime;
