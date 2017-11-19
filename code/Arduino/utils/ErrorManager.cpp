#include "ErrorManager.h"

ErrorManager::ErrorManager()
{
}

ErrorManager::ErrorManager(ErrorManager&)
{
}

ErrorManager::~ErrorManager()
{
}

void ErrorManager::set_error()
{
	is_error_now = true;
}

void ErrorManager::reset_error()
{
	is_error_now = false;
}

bool ErrorManager::is_error_gotten() const
{
	return is_error_now;
}
