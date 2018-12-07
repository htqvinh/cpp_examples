/*
 * AcceptorBase.h
 *
 *  Created on: Dec 21, 2016
 *      Author: vinhhtq
 */

#ifndef INCLUDE_ACCEPTORBASE_H_
#define INCLUDE_ACCEPTORBASE_H_

#include "StreamBase.h"
#define MAX_CLIENTS 30

class AcceptorBase;
typedef shared_ptr<AcceptorBase> AcceptorBaseSptr;

class AcceptorBase {
public:
	AcceptorBase();
	virtual ~AcceptorBase();
	virtual int init(int port) = 0;
	virtual int process(StreamBaseSptr& stream, string& data) = 0;

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
	int process(StreamBaseSptr& stream, string& data);

protected:
	fd_set _readfds; //set of socket descriptors
	int _client_socket[MAX_CLIENTS];
};

class AcceptorUDP
		:public AcceptorBase
{
public:
	AcceptorUDP();
	~AcceptorUDP();
	int init(int port);
	int process(StreamBaseSptr& stream, string& data);
};

#endif /* INCLUDE_ACCEPTORBASE_H_ */
