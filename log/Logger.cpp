#include "Logger.h"


pthread_mutex_t Logger::mutex = PTHREAD_MUTEX_INITIALIZER;
Logger::Logger():
	date_format("%d-%d-%d %d:%d:%d"){
	outfile = fopen(LOG_PATH, "w+");
	fprintf(outfile,"logger init\n");
}

Logger::Logger(const Logger& log){}
void Logger::operator= (const Logger& log){}

Logger::~Logger(){
	fclose(outfile);
}
Logger* Logger::getLogger(){
	pthread_mutex_lock (&mutex);
	static Logger logger;
	pthread_mutex_unlock (&mutex);
	return &logger;
}
void Logger::error(const char* str, ...){
	char date[DATE_MAX_LEN];
	time_t now = time(NULL);
	struct tm * ti = localtime(&now);
	sprintf(date, date_format, ti->tm_year,ti->tm_mon, ti->tm_mday, ti->tm_hour, ti->tm_min, ti->tm_sec);
	
	char msg[LOG_MAX_LEN];
	va_list args;
	va_start(args, str);
	vsprintf (msg, str, args) ;
	va_end(args);

	fprintf(outfile,"%s [%d] error: %s\n", date, (int)getpid(), msg);

}
void Logger::info(const char* str, ...){
	char date[DATE_MAX_LEN];
	time_t now = time(NULL);
	struct tm * ti = localtime(&now);
	sprintf(date, date_format, ti->tm_year,ti->tm_mon, ti->tm_mday, ti->tm_hour, ti->tm_min, ti->tm_sec);
	
	char msg[LOG_MAX_LEN];
	va_list args;
	va_start(args, str);
	vsprintf (msg, str, args) ;
	va_end(args);
	
	fprintf(outfile,"%s [%d] info: %s\n", date, (int)getpid(), msg);
}
void Logger::debug(const char* str, ...){
	char date[DATE_MAX_LEN];
	time_t now = time(NULL);
	struct tm * ti = localtime(&now);
	sprintf(date, date_format, ti->tm_year,ti->tm_mon, ti->tm_mday, ti->tm_hour, ti->tm_min, ti->tm_sec);
	
	char msg[LOG_MAX_LEN];
	va_list args;
	va_start(args, str);
	vsprintf (msg, str, args) ;
	va_end(args);
	
	fprintf(outfile,"%s [%d] debug: %s\n", date, (int)getpid(), msg);
}
void Logger::warn(const char* str, ...){
	char date[DATE_MAX_LEN];
	time_t now = time(NULL);
	struct tm * ti = localtime(&now);
	sprintf(date, date_format, ti->tm_year,ti->tm_mon, ti->tm_mday, ti->tm_hour, ti->tm_min, ti->tm_sec);
	
	char msg[LOG_MAX_LEN];
	va_list args;
	va_start(args, str);
	vsprintf (msg, str, args) ;
	va_end(args);
	
	fprintf(outfile,"%s [%d] warn: %s\n", date, (int)getpid(), msg);
}
