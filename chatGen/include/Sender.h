/*
 * Sender.h
 *
 *  Created on: Dec 27, 2016
 *      Author: htqvinh
 */

#ifndef INCLUDE_SENDER_H_
#define INCLUDE_SENDER_H_

#include <thread>
#include <chrono>
#include "VQueue.h"
#include "VHandler.h"
#include "general.h"

using namespace std;

class Sender
	: public VHandler
{
public:
	Sender(unsigned num_of_threads = 1);
	virtual ~Sender();
	void push(CPackage p);

protected:
	virtual int init();
	virtual void process();

protected:
	VQueue<CPackage> _queue;
};

#endif /* INCLUDE_SENDER_H_ */
