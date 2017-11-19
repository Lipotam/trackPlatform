#include "../utils/ErrorManager.h"
#include "../connection/ConnectionManager.h"
#include "../connection/DebugSerial.h"
#include "../config/Constants.h"

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
	ErrorManager::get_manager().reset_error();

	String command = ConnectionManager::get_manager()->read_command();
	if (!command.length())
	{
		return;
	}

	DEBUG_PRINT("Command was getted: ");
	DEBUG_PRINTLNHEX(command);

	//TODO: parse & execute command, write answer to varaible
	String answer;

	if (ErrorManager::get_manager().is_error_gotten())
	{
		ConnectionManager::get_manager()->write_answer(Constants::bad_answer);
		return;
	}

	if (answer.length() > 0)
	{
		ConnectionManager::get_manager()->write_answer(answer);
	}

	ConnectionManager::get_manager()->write_answer(Constants::good_answer);
}
