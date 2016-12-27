/*
 * StreamBase.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: htqvinh
 */

#include "StreamBase.h"

StreamBase::StreamBase(string ip, int port, int fd)
	:_Ip(ip), _Port(port), _Fd(fd){ }

StreamBase::~StreamBase() { }

StreamTCP::StreamTCP(string ip, int port, int fd)
	:StreamBase(ip, port, fd){ }

StreamTCP::~StreamTCP() { }

int StreamTCP::send(char* buff, size_t len){

	if(_Fd == -1){
		cout << NET_ERR("this stream IP(%s), port(%i) is not connected\n", _Ip.c_str(), _Port);
		return -1;
	}

	for(size_t t = 0, r = 0; len > 0; len -= r, t += r){
		r = :: send(_Fd, buff + t, len, 0);
		if(r == -1){
			cout << NET_ERR("send to IP(%s), port(%i). are failure\n", _Ip.c_str(), _Port);
			return -1;
		}
	}

	return len;
}

int StreamTCP::recv(char* buff, size_t len){

	if(_Fd == -1){
		cout << NET_ERR("this stream IP(%s), port(%i) is not connected\n", _Ip.c_str(), _Port);
		return -1;
	}

	for(size_t t = 0, r = 0; len > 0; len -= r, t += r){
		r = :: recv(_Fd, buff + t, len, 0);
		if(r == -1){
			cout << NET_ERR("receive from IP(%s), port(%i). are failure\n", _Ip.c_str(), _Port);
			return -1;
		}
	}
	return len;
}
