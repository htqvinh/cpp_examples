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
	virtual StreamBaseSptr accept() = 0;

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
	StreamBaseSptr accept();
};

class AcceptorUDP
		:public AcceptorBase
{
public:
	AcceptorUDP();
	~AcceptorUDP();
	int init(int port);
	StreamBaseSptr accept();
};

#endif /* INCLUDE_ACCEPTORBASE_H_ */
