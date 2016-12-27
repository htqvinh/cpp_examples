/*
 * AcceptorBase.cpp
 *
 *  Created on: Dec 21, 2016
 *      Author: vinhhtq
 */


#include "AcceptorBase.h"

AcceptorBase::AcceptorBase()
	:_sockId(-1){ }

AcceptorBase::~AcceptorBase() { }

AcceptorTCP::AcceptorTCP(){ }

AcceptorTCP::~AcceptorTCP(){ }

int AcceptorTCP::init(int port){

	if(_sockId > 0) return _sockId;

    _sockId = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(port);

    if(bind(_sockId, (struct sockaddr *)&serv, sizeof(struct sockaddr)) == -1){
    	cout << NET_ERR("Can't bind socket on port(%i)\n", port);
    	return -1;
    }

    if(listen(_sockId, 1) == -1){
    	cout << NET_ERR("Can't listen socket\n", "");
    	return -1;
    }

    return _sockId;
}

StreamBaseSptr AcceptorTCP::accept(){

	if(_sockId < 0) return nullptr;

	struct sockaddr_in dest;
	socklen_t socksize = sizeof(struct sockaddr_in);
	int consocket = ::accept(_sockId, (struct sockaddr *)&dest, &socksize);
	return StreamBaseSptr(new StreamTCP(inet_ntoa(dest.sin_addr), htons(dest.sin_port), consocket));
}

