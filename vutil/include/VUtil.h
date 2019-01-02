/*
 * VUtil.h
 *
 *  Created on: Dec 21, 2016
 *      Author: htqvinh
 */

#ifndef VUTIL_H_
#define VUTIL_H_
#define BYTE unsigned char

#include <string>
#include <vector>
#include <string.h>
using namespace std;

string getCurrentTime();
string getContent(const char* format, ...);
string printHexcimal(unsigned char &val);


struct ByteBuffer
{
	ByteBuffer(){}
	~ByteBuffer(){}

	BYTE* dataPtr()				{ return &_Bytes[0]; }
	unsigned length()			{ return _Bytes.size(); }
	string toString();

	int append(const void* const bytes, unsigned length);

protected:
	vector<BYTE> _Bytes;
};

#endif /* INCLUDE_VUTIL_H_ */
