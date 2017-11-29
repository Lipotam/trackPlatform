#include "../utils/ErrorManager.h"
#include "../connection/ConnectionManager.h"
#include "../connection/DebugSerial.h"
#include "../config/Constants.h"
#include "CommandManager.h"

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

	String answer = CommandManager::getManager()->parse_and_execute_command(command);

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

void MainManager::stop_all()
{
	CommandManager::getManager()->stop_all();
}

void MainManager::reset_current_connection()
{
	ConnectionManager::get_manager()->reset_current_connection();
}

void MainManager::set_current_connection()
{
	ConnectionManager::get_manager()->set_current_connection();
}

void MainManager::reset_timer()
{
	ConnectionManager::get_manager()->reset_timer();
}

bool MainManager::is_connected()
{
	return ConnectionManager::get_manager()->is_connected();
}
