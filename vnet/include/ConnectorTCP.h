/*
 * ConnectorTCP.h
 *
 *  Created on: Dec 19, 2016
 *      Author: htqvinh
 */

#ifndef INCLUDE_CONNECTORTCP_H_
#define INCLUDE_CONNECTORTCP_H_

#include "ConnectorBase.h"
#include "StreamTCP.h"

class ConnectorTCP
		: public ConnectorBase {
public:
	ConnectorTCP();
	virtual ~ConnectorTCP();
	StreamBase* connect(const char* ip, int port);
};

#endif /* INCLUDE_CONNECTORTCP_H_ */
