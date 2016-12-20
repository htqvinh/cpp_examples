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

	string log(const char* pattern, ...);
	string wrn(const char* pattern, ...);
	string err(const char* pattern, ...);

protected:
	const char* _fileName;
};

#endif /* INCLUDE_VLOG_H_ */
