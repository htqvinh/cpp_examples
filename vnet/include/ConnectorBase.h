/*
 * ConnectorBase.h
 *
 *  Created on: Dec 19, 2016
 *      Author: htqvinh
 */

#ifndef INCLUDE_CONNECTORBASE_H_
#define INCLUDE_CONNECTORBASE_H_

#include "StreamBase.h"

class ConnectorBase {
public:
	ConnectorBase();
	virtual ~ConnectorBase();
	virtual StreamBase* connect(const char* ip, int port) = 0;
};

class ConnectorTCP
		: public ConnectorBase {
public:
	ConnectorTCP();
	virtual ~ConnectorTCP();
	StreamBase* connect(const char* ip, int port);
};

#endif /* INCLUDE_CONNECTORBASE_H_ */
