#include<iostream>
#include "Logger.h"
using namespace std;
int main(){
	cout << "server" << endl;
	Logger *p = Logger::getLogger();
	
	return 0;
}