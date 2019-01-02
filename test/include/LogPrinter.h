/*
 * LogPrinter.h
 *
 *  Created on: Dec 28, 2018
 *      Author: hvr1hc
 */

#ifndef SOURCE_LOGPRINTER_H_
#define SOURCE_LOGPRINTER_H_

#include "VHandler.h"
#include "VQueue.h"
#include <condition_variable>

class LogPrinter:
		public VHandler
{


public:
	LogPrinter() ;
	virtual ~LogPrinter() ;

	virtual int init();
	virtual void process();
	string push(const char* pattern, ...) ;

protected:
	VQueue<string> 				_msgQueue;
	std::mutex 					_mtx;
	std::condition_variable 	_cv;


};

#endif /* SOURCE_LOGPRINTER_H_ */
