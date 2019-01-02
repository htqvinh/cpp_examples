/*
 * AcceptorBase.h
 *
 *  Created on: Dec 21, 2016
 *      Author: vinhhtq
 */

#ifndef INCLUDE_ACCEPTORBASE_H_
#define INCLUDE_ACCEPTORBASE_H_

#include "StreamBase.h"
#include "VUtil.h"
#define MAX_CLIENTS 30

class AcceptorBase;
typedef shared_ptr<AcceptorBase> AcceptorBaseSptr;

class AcceptorBase {
public:
	AcceptorBase():_listenSocket(-1){}
	virtual ~AcceptorBase(){};
	virtual int init(int port) = 0;
	virtual int process(
			std::function<int(const StreamBaseSptr&)> processNewConnection,
			std::function<int(const StreamInfo&)> processDisconnected,
			std::function<int(const StreamInfo&, ByteBuffer&)> processNewData) = 0;

protected:
	int _listenSocket;
};

class AcceptorTCP
		:public AcceptorBase
{
public:
	AcceptorTCP(){
		memset(_connectSocket, 0, sizeof(_connectSocket));
	};
	~AcceptorTCP(){};
	int init(int port);
	int process(
			std::function<int(const StreamBaseSptr&)> processNewConnection,
			std::function<int(const StreamInfo&)> processDisconnected,
			std::function<int(const StreamInfo&, ByteBuffer&)> processNewData);

protected:
	fd_set _readfds; //set of socket descriptors
	int _connectSocket[MAX_CLIENTS];
};

class AcceptorUDP
		:public AcceptorBase
{
public:
	AcceptorUDP(){};
	~AcceptorUDP(){};
	int init(int port);
	int process(
			std::function<int(const StreamBaseSptr&)> processNewConnection,
			std::function<int(const StreamInfo&)> processDisconnected,
			std::function<int(const StreamInfo&, ByteBuffer&)> processNewData);
};

#endif /* INCLUDE_ACCEPTORBASE_H_ */
