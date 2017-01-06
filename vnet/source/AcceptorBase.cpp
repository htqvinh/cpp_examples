/*
 * AcceptorBase.cpp
 *
 *  Created on: Dec 21, 2016
 *      Author: vinhhtq
 */


#include "AcceptorBase.h"

AcceptorBase::AcceptorBase()
	:_sockId(-1){ }

AcceptorBase::~AcceptorBase() 	{}

AcceptorTCP::AcceptorTCP()		{}

AcceptorTCP::~AcceptorTCP()		{}

AcceptorUDP::AcceptorUDP()		{}

AcceptorUDP::~AcceptorUDP()		{}

int AcceptorTCP::init(int port){

	if(_sockId > 0) return _sockId;

    int sockid = socket(AF_INET, SOCK_STREAM, 0);
	if(sockid == -1){
		cout << NET_ERR("Can't initialize a socket(%i)", sockid);
		return -1;
	}

    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(port);

    if(bind(sockid, (struct sockaddr *)&serv, sizeof(struct sockaddr)) == -1){
    	cout << NET_ERR("Can't bind socket on port(%i)\n", port);
    	return -1;
    }

    if(listen(sockid, 1) == -1){
    	cout << NET_ERR("Can't listen socket\n", "");
    	return -1;
    }

    _sockId = sockid;

    return _sockId;
}

StreamBaseSptr AcceptorTCP::accept(){

	if(_sockId < 0) return nullptr;

	struct sockaddr_in dest;
	socklen_t socksize = sizeof(struct sockaddr_in);

	int consocket = ::accept(_sockId, (struct sockaddr *)&dest, &socksize);

	StreamBaseSptr ptr(new StreamTCP(inet_ntoa(dest.sin_addr), htons(dest.sin_port), consocket));

	return ptr;
}

int AcceptorUDP::init(int port){

	if(_sockId > 0) return _sockId;

	int sockid = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockid == -1){
		cout << NET_ERR("Can't initialize a socket(%i)", sockid);
		return -1;
	}

    struct sockaddr_in serv;
	memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(port);

	if(bind(sockid, (struct sockaddr *)&serv, sizeof(struct sockaddr)) == -1){
		cout << NET_ERR("Can't bind socket on port(%i)\n", port);
		return -1;
	}

    _sockId = sockid;

	return _sockId;
}

StreamBaseSptr AcceptorUDP::accept(){

	if(_sockId < 0) return nullptr;

	char tmp;
	struct sockaddr_in dest;
	socklen_t socksize = sizeof(struct sockaddr_in);

	/*
	 * To receive 1 byte from client
	 * When client connected, will sent 1 bytes, not be used
	 */
	recvfrom(_sockId, &tmp, sizeof(char), 0, (struct sockaddr *)&dest, &socksize);

	StreamBaseSptr ptr(new StreamUDP(inet_ntoa(dest.sin_addr), htons(dest.sin_port), _sockId));

	return ptr;
}

