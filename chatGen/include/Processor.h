/*
 * Processor.h
 *
 *  Created on: Jan 3, 2017
 *      Author: htqvinh
 */

#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include "general.h"
#include "VHandler.h"


class Receiver;
class Processor
		: public VHandler
{
public:
	Processor(Receiver &recv, FunctionProc method, unsigned num_of_threads = 1);
	virtual ~Processor();

protected:
	void process();

protected:
	FunctionProc _Process_Method;
	Receiver& _Receiver;
};

#endif /* PROCESSOR_H_ */
