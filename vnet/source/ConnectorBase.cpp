/*
 * ConnectorBase.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: htqvinh
 */

#include "ConnectorBase.h"

ConnectorBase::ConnectorBase()	{}

ConnectorBase::~ConnectorBase()	{}

ConnectorTCP::ConnectorTCP() 	{}

ConnectorTCP::~ConnectorTCP() 	{}

int ConnectorTCP::connect(string ip, unsigned port, int& fd){

	int sockid = socket(AF_INET, SOCK_STREAM, 0);
	if(sockid == -1){
		cout << NET_ERR("Can't initialize a socket", "");
		return -1;
	}

	struct sockaddr_in dest;
	memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(ip.c_str());
	dest.sin_port = htons(port);

	if(::connect(sockid, (struct sockaddr *)&dest, sizeof(struct sockaddr_in))){
		cout << NET_ERR("connecting to IP(%s), port(%i) failed\n", ip.c_str(), port);
		return -1;
	}

	fd = sockid;

	return 0;
}
