#include "Logger.h"

#ifndef LOGGER_ON

void Logger::log(std::string s)
{
}

#else

Logger* Logger::logger = new Logger();

Logger::Logger() : file(way, std::ios::out | std::ios::app)
{
}

void Logger::logOneString(std::string s)
{
	file << s << std::endl;
}

void Logger::log(std::string s)
{
	logger->logOneString(s);
}

#endif
