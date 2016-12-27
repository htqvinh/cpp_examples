/*
 * ConnectorBase.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: htqvinh
 */

#include "ConnectorBase.h"

ConnectorBase::ConnectorBase(){

}

ConnectorBase::~ConnectorBase(){

}

ConnectorTCP::ConnectorTCP() {

}

ConnectorTCP::~ConnectorTCP() {

}

int ConnectorTCP::connect(StreamBaseSptr sptr){

	if(!sptr) {
		cout << NET_ERR("StreamBaseSptr pointer is null", "");
		return -1;
	}

	sptr->_Fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sptr->_Fd == -1){
		cout << NET_ERR("Can't initialize a socket", "");
		return -1;
	}

	struct sockaddr_in dest;
	memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(sptr->_Ip.c_str());
	dest.sin_port = htons(sptr->_Port);

	if(::connect(sptr->_Fd, (struct sockaddr *)&dest, sizeof(struct sockaddr_in))){
		cout << NET_ERR("connecting to IP(%s), port(%i) failed\n", sptr->_Ip.c_str(), sptr->_Port);
		return -1;
	}

	return 0;
}
