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
	string str(content);
	free(content);

	va_end(args);
	return str;
}

string toHexString(unsigned char &val){

	static char HEX[] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F'
	};

	string s = "";
	s += HEX[(val << 4) & 0xF];
	s += HEX[val & 0xF];

	return s;
}

int ByteBuffer::append(const void* const bytes, unsigned length){

	unsigned old_len = _Bytes.size();
	unsigned new_len = old_len + length;

	_Bytes.resize(new_len);

	unsigned char* const ptr = &_Bytes[old_len];
	memcpy(ptr, bytes, length);

	return 1;
}

string ByteBuffer::toString(){
	string s = "";
	for(unsigned char c: _Bytes){
		s += toHexString(c) + " ";
	}
	return s;
}
