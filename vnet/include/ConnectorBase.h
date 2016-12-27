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
	virtual int connect(StreamBaseSptr sptr) = 0;
};

class ConnectorTCP
		: public ConnectorBase {
public:
	ConnectorTCP();
	virtual ~ConnectorTCP();
	int connect(StreamBaseSptr sptr);
};

#endif /* INCLUDE_CONNECTORBASE_H_ */
