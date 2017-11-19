#include "MainManager.h"

MainManager* MainManager::manager = nullptr;

MainManager::MainManager()
{
}

MainManager::MainManager(MainManager&)
{
}

MainManager::~MainManager()
{
}

MainManager* MainManager::get_manager()
{
	if (!manager)
	{
		manager = new MainManager();
	}

	return manager;
}

void MainManager::run()
{
	//TODO
}
