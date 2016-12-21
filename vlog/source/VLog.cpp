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

#define MAX 1000

VLog::VLog(const char* fileName)
	:_fileName(fileName)
{

}

VLog::~VLog() {

}

string VLog::log(const char* pattern, ...){
	char content[MAX];
	va_list args;
	va_start(args, pattern);
	vsprintf(content, pattern, args);
	va_end(args);
	return string(content);
}

string VLog::err(const char* pattern, ...){

	va_list args;
	va_start(args, pattern);

	char *content = NULL;
	vasprintf(&content, pattern, args);
	string ret(content);
	free(content);

	va_end(args);
	return ret;
}

string VLog::wrn(const char* pattern, ...){
	char content[MAX];
	va_list args;
	va_start(args, pattern);
	vsprintf(content, pattern, args);
	va_end(args);
	return string(content);
}
