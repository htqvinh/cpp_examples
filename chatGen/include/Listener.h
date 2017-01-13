/*
 * Listener.h
 *
 *  Created on: Jan 12, 2017
 *      Author: htqvinh
 */

#ifndef LISTENER_H_
#define LISTENER_H_

#include "general.h"
#include "VHandler.h"

class Listener
	: public VHandler
{
public:
	Listener(StreamBaseSptr stream_ptr, FunctionProcessMessage method, unsigned num_of_threads = 1);
	virtual ~Listener();

protected:
	void process();

protected:
	StreamBaseSptr 	_StreamPtr;
	FunctionProcessMessage 	_Process_Method;
};

#endif /* INCLUDE_LISTENER_H_ */
