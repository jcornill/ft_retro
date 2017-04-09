#include "Logger.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string const Logger::_filename = "log.txt";

Logger::Logger(){

}

Logger::Logger(Logger const & src) {
	*this = src;
}

Logger::~Logger() {

}

Logger & Logger::operator=(Logger const & rhs) {
	if (this != &rhs) {

	}
	return *this;
}

void Logger::LogToFile(int message)
{
	std::ofstream ofs(_filename, std::ofstream::app);

	ofs << message << std::endl;
	ofs.close();
}

void Logger::LogToFile(const std::string &message)
{
	std::ofstream ofs(_filename, std::ofstream::app);

	ofs << Logger::MakeLogEntry(message);
	ofs.close();
}

std::string Logger::MakeLogEntry(const std::string &message)
{
	std::time_t result = std::time(nullptr);
  	std::stringstream ss;

	ss << "[" << std::put_time(std::localtime(&result), "%d %B %H:%M:%S") << "] " << message << std::endl;
	return ss.str();
}
