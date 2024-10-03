#include "GameManager.h"
#include "SceneManager.h"
#include "BufferManager.h"
#include <sstream>
using namespace std;

int main()
{
	srand(time(NULL));
	if (MAX_GAME_COUNT < 1)
		return 0;
	BufferManager::GetInstance().Init();
	SceneManager::GetInstance().Init();
	GameManager::GetInstance().GameStart();
}
