#include "GameManager.h"

int main()
{
	srand(time(NULL));
	if (MAX_GAME_COUNT < 1)
		return 0;
	GameManager::GetInstance().GameStart();
}
