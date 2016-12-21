/*
 * VUtil.cpp
 *
 *  Created on: Dec 21, 2016
 *      Author: htqvinh
 */

#include <ctime>
#include <stdio.h>
#include <cstdarg>
#include <stdlib.h>
#include "VUtil.h"

#define MAX_LEN_TIME 80

string getCurrentTime(){

	time_t rawtime;
	struct tm * timeinfo;
	char buffer[MAX_LEN_TIME];

	time (&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, MAX_LEN_TIME,"%Y-%m-%d %I:%M:%S", timeinfo);

	return string(buffer);
}


string getContent(const char* format, ...){

	va_list args;
	va_start(args, format);

	char *content = NULL;
	vasprintf(&content, format, args);
	free(content);

	va_end(args);
	return string(content);
}
