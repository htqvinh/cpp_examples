/*
 * StreamTCP.h
 *
 *  Created on: Dec 19, 2016
 *      Author: htqvinh
 */

#ifndef INCLUDE_STREAMTCP_H_
#define INCLUDE_STREAMTCP_H_

#include "StreamBase.h"

class StreamTCP
		: public StreamBase {
public:
	StreamTCP();
	StreamTCP(int sockid, struct sockaddr_in* address);
	virtual ~StreamTCP();
	int send(char* buff, size_t len);
	int recv(char* buff, size_t len);
};

#endif /* INCLUDE_STREAMTCP_H_ */
