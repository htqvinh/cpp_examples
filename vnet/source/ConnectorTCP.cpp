/*
 * ConnectorTCP.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: htqvinh
 */

#include "ConnectorTCP.h"

using namespace std;
extern VLog NetLog;

ConnectorTCP::ConnectorTCP() {
	// TODO Auto-generated constructor stub

}

ConnectorTCP::~ConnectorTCP() {
	// TODO Auto-generated destructor stub
}

StreamBase* ConnectorTCP::connect(const char* ip, int port){

	int sockid = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in dest;
	memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(ip);
	dest.sin_port = htons(port);

	if(::connect(sockid, (struct sockaddr *)&dest, sizeof(struct sockaddr_in))){
		NET_ERR("connecting to IP(%s), port(%i) failed", ip, port);
		return NULL;
	}

	return new StreamTCP(sockid, &dest);
}
