#ifndef _Logger_H_
#define _Logger_H_

#include <fstream>

#define LOG_PATH "./log.txt"
#define LOG_MAX_LEN 1024
#define DATE_MAX_LEN 100
class Logger{
public:
	static Logger* getLogger();
	void error(const char* str, ...);
	void info(const char* str, ...);
	void debug(const char* str, ...);
	void warn(const char* str, ...);
	
	~Logger();
private:
	Logger(){};

	const char* date_format;
	ofstream outfile;
	static Logger* logger;
};
Logger* Logger::logger = NULL;
#endif