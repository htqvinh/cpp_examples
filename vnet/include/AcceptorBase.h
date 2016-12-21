/*
 * AcceptorBase.h
 *
 *  Created on: Dec 21, 2016
 *      Author: vinhhtq
 */

#ifndef INCLUDE_ACCEPTORBASE_H_
#define INCLUDE_ACCEPTORBASE_H_

#include "StreamBase.h"

class AcceptorBase {
public:
	AcceptorBase();
	virtual ~AcceptorBase();
	virtual int init(int port) = 0;
	virtual StreamBase* accept() = 0;

protected:
	int _sockId;
};

class AcceptorTCP
		:public AcceptorBase
{
public:
	AcceptorTCP();
	~AcceptorTCP();
	int init(int port);
	StreamBase* accept();
};

class AcceptorUDP
		:public AcceptorBase
{
public:
	AcceptorUDP();
	~AcceptorUDP();
	int init(int port);
	StreamBase* accept();
};

#endif /* INCLUDE_ACCEPTORBASE_H_ */
