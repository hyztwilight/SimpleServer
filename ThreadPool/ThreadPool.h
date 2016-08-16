#ifndef _ThreadPool_H_
#define _ThreadPool_H_

#include<list>
#include<vector>
#include<semaphore.h>
#include <pthread.h>

#define MAX_JOB_NUM 10000
class Job{
public:
	Job(void (*func)(const void *arg), const void *arg);
	void (*func)(const void *arg);
	const void *arg;
};
class ThreadPool{
public:
	~ThreadPool();
	ThreadPool(const int size);
	bool add_job(Job *job);
	bool getalive();
	void setjobsize(int size);
private:
	ThreadPool();
	static void* do_job(void *arg);
	void tp_delete();

	bool keep_alive;
	pthread_mutex_t job_mutex;
	sem_t jobSem;
	std::vector<pthread_t> threads;
	std::list<Job*> jobs;
	int max_job_size;
};
#endif
