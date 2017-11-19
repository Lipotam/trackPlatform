#pragma once

class MainManager
{
	static MainManager* manager;

	MainManager();
	MainManager(MainManager&);

	

public:
	static MainManager* get_manager();

	void run();
};
