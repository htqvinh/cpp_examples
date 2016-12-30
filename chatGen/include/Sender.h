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
#include "../../vutil/include/VQueue.h"
#include "general.h"

using namespace std;

class Sender
{
public:
	Sender();
	virtual ~Sender();
	void push(CPackage p);
	void active(bool f = true);

protected:
	void process();

protected:
	VQueue<CPackage> _queue;
	bool _isActive;
};

#endif /* INCLUDE_SENDER_H_ */
