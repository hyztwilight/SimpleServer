#include "Logger.h"

Logger::Logger():
	date_format("%d-%d-%d %d:%d:%d"),
	outfile(LOG_PATH){
}
Logger::~Logger(){
	outfile.close();
}
Logger* Logger::getLogger(){
	if(logger == NULL)
		return (logger = new Logger());
	else
		return logger;
}
void Logger::error(const char* str, ...){
	char date[DATE_MAX_LEN];
	time_t now = time(NULL);
	struct tm * ti = localtime(now);
	sprintf(date, date_format, ti->tm_year,ti->tm_mon, ti->tm_mday, ti->tm_hour, ti->tm_min, ti->tm_sec)£»
	
	char msg[LOG_MAX_LEN];
	va_list args;
	va_start(args, str);
	vsprintf (msg, str, args) ;
	va_end(args);
	
	outfile <<"["<<(int)getpid()<<"]"<<" error:"<<" "<<date<<" "<<msg;
}
void Logger::info(const char* str, ...){
	char date[DATE_MAX_LEN];
	time_t now = time(NULL);
	struct tm * ti = localtime(now);
	sprintf(date, date_format, ti->tm_year,ti->tm_mon, ti->tm_mday, ti->tm_hour, ti->tm_min, ti->tm_sec)£»
	
	char msg[LOG_MAX_LEN];
	va_list args;
	va_start(args, str);
	vsprintf (msg, str, args) ;
	va_end(args);
	
	outfile <<"["<<(int)getpid()<<"]"<<" info:"<<" "<<date<<" "<<msg;
}
void Logger::debug(const char* str, ...){
	char date[DATE_MAX_LEN];
	time_t now = time(NULL);
	struct tm * ti = localtime(now);
	sprintf(date, date_format, ti->tm_year,ti->tm_mon, ti->tm_mday, ti->tm_hour, ti->tm_min, ti->tm_sec)£»
	
	char msg[LOG_MAX_LEN];
	va_list args;
	va_start(args, str);
	vsprintf (msg, str, args) ;
	va_end(args);
	
	outfile <<"["<<(int)getpid()<<"]"<<" debug:"<<" "<<date<<" "<<msg;
}
void Logger::warn(const char* str, ...){
	char date[DATE_MAX_LEN];
	time_t now = time(NULL);
	struct tm * ti = localtime(now);
	sprintf(date, date_format, ti->tm_year,ti->tm_mon, ti->tm_mday, ti->tm_hour, ti->tm_min, ti->tm_sec)£»
	
	char msg[LOG_MAX_LEN];
	va_list args;
	va_start(args, str);
	vsprintf (msg, str, args) ;
	va_end(args);
	
	outfile <<"["<<(int)getpid()<<"]"<<" warn:"<<" "<<date<<" "<<msg;
}