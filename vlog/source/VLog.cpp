/*
 * VLog.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: htqvinh
 */

#include <stdio.h>
#include <cstdarg>
#include "VLog.h"

#define MAX 1000

VLog::VLog(const char* fileName)
	:_fileName(fileName)
{

}

VLog::~VLog() {
	// TODO Auto-generated destructor stub
}

string VLog::log(const char* pattern, ...){

	char content[MAX];

	va_list args;
	va_start(args, pattern);
	vsprintf(content, pattern, args);
	va_end(args);

	return string(content);
}
