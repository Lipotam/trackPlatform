#ifndef _LOGGER_H_
#define _LOGGER_H_

/**
 * @brief If defined, log is on, else off
 */
// #define LOGGER_ON

#ifndef LOGGER_ON
#include <string>
class Logger
{
public:
	static void log(std::string s);
};

#else
#include <string>
#include <fstream>

class Logger
{
	static Logger* logger;

	const std::string way = "logger.log";
	std::ofstream file;

	Logger();
	void logOneString(std::string s);

public:
	static void log(std::string s);
};
#endif

#endif /* _LOGGER_H_ */
