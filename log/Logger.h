#ifndef _Logger_H_
#define _Logger_H_

#include <fstream>
#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <unistd.h>
#include <pthread.h>

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
	Logger();
	Logger(const Logger& log);
	void operator = (const Logger& log);

	const char* date_format;
	static pthread_mutex_t  mutex;
	FILE* outfile;
};
#endif
