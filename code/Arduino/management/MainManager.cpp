#include "../utils/ErrorManager.h"
#include "../connection/ConnectionManager.h"
#include "../connection/DebugSerial.h"
#include "../config/Constants.h"
#include "../peripheral/display/DisplayManager.h"
#include "CommandManager.h"

#include "MainManager.h"

MainManager* MainManager::manager_ = nullptr;

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
	if (!manager_)
	{
		manager_ = new MainManager();
	}

	return manager_;
}

void MainManager::run()
{
	ErrorManager::get_manager().reset_error();

	DisplayManager* display = DisplayManager::get_manager();
	display->repaint();

	String command = ConnectionManager::get_manager()->read_command();
	if (!command.length())
	{
		return;
	}
	
	DEBUG_PRINT("Command was getted: ");
	DEBUG_PRINTLNHEX(command);

	display->set_processing_status(processing);
	display->repaint();

	String answer = CommandManager::getManager()->parse_and_execute_command(command);

	if (ErrorManager::get_manager().is_error_gotten())
	{
		ConnectionManager::get_manager()->write_answer(Constants::kBadAnswer);
		display->set_processing_status(error);
		display->repaint();
		return;
	}

	if (answer.length() > 0)
	{
		ConnectionManager::get_manager()->write_answer(answer);
	}

	ConnectionManager::get_manager()->write_answer(Constants::kGoodAnswer);
	display->set_processing_status(success);
	display->repaint();
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
