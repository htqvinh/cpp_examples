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
#include "VQueue.h"
#include "VHandler.h"
#include "AcceptorBase.h"
#include <functional>

class Receiver:
		public VHandler
{

	friend class Processor;

public:
	Receiver(
			AcceptorBaseSptr acceptor, unsigned port,
			std::function<int (StreamBaseSptr, CMessage&)> recv_method = recv_and_keep,
			unsigned num_of_threads = 1
			);

	virtual ~Receiver();

protected:
	int init();
	void process();

protected:
	VQueue<CPackage> _Pool;
	AcceptorBaseSptr _Acceptor;
	unsigned _Port;
	std::function<int (StreamBaseSptr, CMessage& )> _Recv_Method;
};

#endif /* INCLUDE_RECEIVER_H_ */
