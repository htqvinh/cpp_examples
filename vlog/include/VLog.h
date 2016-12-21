/*
 * VLog.h
 *
 *  Created on: Dec 19, 2016
 *      Author: htqvinh
 */

#ifndef INCLUDE_VLOG_H_
#define INCLUDE_VLOG_H_

#include <string>
using namespace std;

class VLog {
public:
	VLog(const char* fileName);
	virtual ~VLog();

	string out(const char* type, const char* func, int line, const char* pattern, ...);

protected:
	const char* _fileName;
};

#endif /* INCLUDE_VLOG_H_ */
