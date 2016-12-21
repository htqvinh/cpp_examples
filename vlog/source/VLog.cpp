/*
 * VLog.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: htqvinh
 */

#include <stdio.h>
#include <cstdarg>
#include <stdlib.h>

#include "VLog.h"
#include "VUtil.h"

#define MAX 1000

VLog::VLog(const char* fileName)
	:_fileName(fileName)
{

}

VLog::~VLog() {

}

string VLog::out(const char* type, const char* func, int line, const char* pattern, ...){

	va_list args;
	va_start(args, pattern);

	char *cont = NULL;
	vasprintf(&cont, pattern, args);
	string log = getContent("[%s][%s:%i]\t%s",
			getCurrentTime().c_str(), func, line, cont);
	free(cont);

	va_end(args);
	return log;
}
