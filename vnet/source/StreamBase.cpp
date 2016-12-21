/*
 * StreamBase.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: htqvinh
 */

#include "StreamBase.h"

StreamBase::StreamBase(int sockid, int port, string ip):
	_sockId(sockid), _peerPort(port), _peerIP(ip)
{

}

StreamBase::~StreamBase() {

}

int StreamBase::getSockId(){
	return _sockId;
}

int StreamBase::getPort(){
	return _peerPort;
}

string StreamBase::getIP(){
	return _peerIP;
}

StreamTCP::StreamTCP(int sockid, sockaddr_in* address)
	:StreamBase(sockid, ntohs(address->sin_port), inet_ntoa(address->sin_addr))
{

}

StreamTCP::~StreamTCP() {

}

int StreamTCP::send(char* buff, size_t len){
	return 0;
}

int StreamTCP::recv(char* buff, size_t len){
	return 0;
}
