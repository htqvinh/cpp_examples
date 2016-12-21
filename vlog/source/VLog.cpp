/*
 * VLog.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: htqvinh
 */

#include <stdio.h>
#include <cstdarg>
#include <stdlib.h>
#include <fstream>

#include "VLog.h"
#include "VUtil.h"

#define MAX 1000

VLog::VLog(const char* fileName)
	:_fileName(fileName)
{

}

VLog::~VLog() {

}

int VLog::write(string log){

	ofstream myfile (_fileName, ios::out | ios::app );
	if (myfile.is_open()){
		myfile << log;
		myfile.close();
		return 1;
	}
	return 0;
}

string VLog::out(const char* type, const char* func, int line, const char* pattern, ...){

	va_list args;
	va_start(args, pattern);

	char *cont = NULL;
	vasprintf(&cont, pattern, args);
	string log = getContent("[%s][%s][%s:%i] %s",
			getCurrentTime().c_str(), type, func, line, cont);

	write(log);
	free(cont);
	va_end(args);

	return log;
}
