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
	virtual int connect(string ip, unsigned port, int& fd) = 0;
};

class ConnectorTCP
		: public ConnectorBase {
public:
	ConnectorTCP();
	virtual ~ConnectorTCP();
	int connect(string ip, unsigned port, int& fd);
};

class ConnectorUDP
		: public ConnectorBase {
public:
	ConnectorUDP();
	virtual ~ConnectorUDP();
	int connect(string ip, unsigned port, int& fd);
};

#endif /* INCLUDE_CONNECTORBASE_H_ */
