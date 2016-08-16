#include<iostream>
#include<string>
#include "Logger.h"
#include"ThreadPool.h"
using namespace std;
void func(const void *arg){
	//cout << "---hello---" <<endl;
	static int cnt = 0;
	const char* str = (char*)arg;
	cout << str << ":" << cnt++ <<endl;
}
int main(){
	ThreadPool *tp = new ThreadPool(5);
	cout << "test begin" << endl;
	tp->setjobsize(2);
	for(int i=0 ; i<1000 ; i++){
		Job *job = new Job(func, "func print ");
		if(!tp->add_job(job))
			printf("---------------add job fail-----------------\n");
	}
	string str;
	cin >> str;
	delete tp;
	cout << "test end" << endl;
	return 0;
}
