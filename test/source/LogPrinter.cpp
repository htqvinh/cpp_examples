/*
 * LogPrinter.cpp
 *
 *  Created on: Dec 28, 2018
 *      Author: hvr1hc
 */

#include "LogPrinter.h"
#include "VUtil.h"
#include <cstdarg>
#include <iostream>

using namespace std;

LogPrinter::LogPrinter() :VHandler(1) {
	// TODO Auto-generated constructor stub
}

LogPrinter::~LogPrinter() {
	// TODO Auto-generated destructor stub
}

int LogPrinter::init(){
	return 1;
}

void LogPrinter::process(){

    std::unique_lock<std::mutex> lk(_mtx);
	_cv.wait(lk, [this]() -> bool {
		if(_msgQueue.isEmpty()){
			cout << "LogPrinter is waiting...\n";
			return false;
		}
		return true;
	});

	string content;
	_msgQueue.pop(content);
	cout << content;
}

string LogPrinter::push(const char* pattern, ...){

	va_list args;
	va_start(args, pattern);
	char *cont = NULL;
	vasprintf(&cont, pattern, args);
	string log = getContent("[%s] %s", getCurrentTime().c_str(), cont);
	free(cont);
	va_end(args);

    std::unique_lock<std::mutex> lk(_mtx);
    _msgQueue.push(log);
	_cv.notify_one();

	return log;
}

