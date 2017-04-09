#ifndef LOGGER_H
# define LOGGER_H
# include <string>

class Logger
{
public:
	Logger(void);
	Logger(Logger const & src);
	virtual ~Logger();
	Logger & operator=(Logger const &rhs);
	static void LogToFile(const std::string &message);
	static void LogToFile(int);
	static std::string MakeLogEntry(const std::string &message);
private:
	static std::string const _filename;
};

#endif
