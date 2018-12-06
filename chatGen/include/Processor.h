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
	Processor(Receiver &recv, FunctionProcessPackage method, unsigned num_of_threads = 1);
	virtual ~Processor();

protected:
	virtual int init();
	virtual void process();

protected:
	Receiver& _Receiver;
	FunctionProcessPackage _Process_Method;
};

#endif /* PROCESSOR_H_ */
