/**
 * @brief If defined, log is on, else off
 */
// #define LOGGER_ON

#if ! LOGGER_ON
public partial class Logger
{
#if ! LOGGER_ON
	public static void log(string s)
	{
	}
#endif
}

#else

public partial class Logger
{
	private static Logger logger = new Logger();

	private readonly string way = "logger.log";
	private std::ofstream file = new std::ofstream();

#if ! ! LOGGER_ON
	private Logger()
	{
		this.file = new std::ofstream(way, std::ios.@out | std::ios.app);
	}
	private void logOneString(string s)
	{
		file << s << std::endl;
	}

	public static void log(string s)
	{
		logger.logOneString(s);
	}
}
#endif





#endif
