/*
 * Receiver.h
 *
 *  Created on: Dec 27, 2016
 *      Author: htqvinh
 */

#ifndef INCLUDE_RECEIVER_H_
#define INCLUDE_RECEIVER_H_

#include "defines.h"
#include "general.h"
#include "VMap.h"
#include "VQueue.h"
#include "VHandler.h"
#include "AcceptorBase.h"
#include <functional>
#include <condition_variable>

using namespace std;

class Receiver:
		public VHandler
{

	friend class Processor;

public:
	Receiver(
			AcceptorBaseSptr acceptor, unsigned port, unsigned num_of_threads = 1);

	virtual ~Receiver();

protected:
	int init();
	void process();
	void pushToQueue(const CPackage& p);
	void waitToPopFromQueue(CPackage& p);

protected:
	VMap<StreamInfo, StreamBaseSptr> 	_StreamMap;
	VQueue<CPackage> 					_Pool;
	AcceptorBaseSptr 					_Acceptor;
	unsigned 							_Port;

	std::mutex 							_mtx;
	std::condition_variable 			_cv;
};

#endif /* INCLUDE_RECEIVER_H_ */
