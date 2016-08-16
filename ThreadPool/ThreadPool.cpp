#include"ThreadPool.h"
#include"Logger.h"

Job::Job(void (*_func)(const void *arg), const void *_arg):
	func	(_func),
	arg	(_arg)
{}

Logger *log = Logger::getLogger();
ThreadPool::~ThreadPool(){
	tp_delete();
}
ThreadPool::ThreadPool(const int size):
	keep_alive	(true),
	job_mutex	(PTHREAD_MUTEX_INITIALIZER)
{
	log->info("threadpool initial size : %d", size);
	int ans = 0;
	threads = std::vector<pthread_t>(size,0);
	for(int i=0;i<size;i++){
		
		if(pthread_create(&threads[i],NULL,do_job,(void *)this)){
			log->error("threadpool initial thread %d request error", i);
			ans = 1;
			break;
		}
	}

	max_job_size = MAX_JOB_NUM;
	if(sem_init(&jobSem,0,0)){
		log->error("threadpool initial jobSem request error");
		ans = 1;
	}
	if(ans)
		tp_delete();
	log->info("threadpool initial success size : %d", size);
	printf("threadpool initial complete alive : %d  ans: %d jobsize:%d \n", keep_alive, ans, max_job_size);
}

void* ThreadPool::do_job(void *arg){
	ThreadPool *tp = (ThreadPool*)arg;
	Job *job = NULL;
	//printf("thread begin %d alive  %d \n", getpid(), tp->getalive());
	while( tp->getalive() ){
		if(sem_wait( &(tp->jobSem)) )
			log->error("threadpool do_job() waiting for sem error");
		if( tp->getalive() ){
			pthread_mutex_lock (&(tp->job_mutex));
			job = tp->jobs.front();
			tp->jobs.pop_front();
			pthread_mutex_unlock (&(tp->job_mutex));

			job->func(job->arg);
			delete job;
			job = NULL;
		}
	}
	//printf("thread end:  %d \n", getpid());
	return NULL;
}

bool ThreadPool::add_job(Job *job){
	if(!keep_alive || jobs.size()==max_job_size)
		return false;
	jobs.push_back(job);
	sem_post(&jobSem);
	return true;
}
bool ThreadPool::getalive(){
	return keep_alive;
}
void ThreadPool::setjobsize(int size){
	max_job_size = size;
}
void ThreadPool::tp_delete(){
	//printf("ThreadPool tp_delete()\n");
	log->info("threadpool is destroying");
	keep_alive = false;
	while(!jobs.empty()){
		delete jobs.front();
		jobs.pop_front();
	}

	for(int i=0;i<threads.size();i++){
		if(sem_post(&jobSem))
			log->error("tp_delete() : could not bypass sem_wait ()");
	}

	for(int i=0 ; i<threads.size() ; i++){
		pthread_join(threads[i], NULL);
	}

	if (sem_destroy(&jobSem))
        	log->error("thpool_destory () : could not destroy semaphore");
	log->info("threadpool destroy ok");
	//printf("tp_delete() ok\n");
}
