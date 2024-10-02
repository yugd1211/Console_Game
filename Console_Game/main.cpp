#include "GameManager.h"

int main()
{
	srand(time(NULL));
	GameManager::GetInstance().GameStart();
}
