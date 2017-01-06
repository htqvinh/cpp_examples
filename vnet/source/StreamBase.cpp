/*
 * StreamBase.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: htqvinh
 */

#include "StreamBase.h"
#include "ConnectorBase.h"

StreamBase::StreamBase(string ip, int port, int fd)
	:_Ip(ip), _Port(port), _Fd(fd){ }

StreamBase::~StreamBase() { }

StreamTCP::StreamTCP(string ip, int port, int fd)
	:StreamBase(ip, port, fd){ }

StreamTCP::~StreamTCP() { }

StreamUDP::StreamUDP(string ip, int port, int fd)
	:StreamBase(ip, port, fd){ }

StreamUDP::~StreamUDP() { }

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
	return 0;
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
	return 0;
}

int StreamTCP::connect(){
	if(_Fd == -1){
		ConnectorTCP tcp;
		tcp.connect(_Ip, _Port, _Fd);
	}
	return _Fd;
}

int StreamTCP::close(){
	if(_Fd > 0){
		::close(_Fd);
		_Fd = -1;
	}
	return 0;
}

int StreamUDP::send(char* buff, size_t len){

	if(_Fd == -1){
		cout << NET_ERR("this stream IP(%s), port(%i) is not connected\n", _Ip.c_str(), _Port);
		return -1;
	}

	struct sockaddr_in dest;
	socklen_t socksize = sizeof(struct sockaddr_in);

	memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(_Ip.c_str());
	dest.sin_port = htons(_Port);

	int r = sendto(_Fd, buff, len, 0, (struct sockaddr *)&dest, socksize);
	if(r < len){
		cout << NET_LOG("send real length(%i) < expect length(%i)\n", r, len);
		return -1;
	}

	return 0;
}

int StreamUDP::recv(char* buff, size_t len){

	if(_Fd == -1){
		cout << NET_ERR("this stream IP(%s), port(%i) is not connected\n", _Ip.c_str(), _Port);
		return -1;
	}

	struct sockaddr_in dest;
	socklen_t socksize = sizeof(struct sockaddr_in);

	int r = recvfrom(_Fd, buff, len, 0, (struct sockaddr *)&dest, &socksize);
	if(r < len){
		cout << NET_LOG("receive real length(%i) < expect length(%i)\n", r, len);
		return -1;
	}

	return 0;
}

int StreamUDP::connect(){
	if(_Fd == -1){
		ConnectorUDP tcp;
		tcp.connect(_Ip, _Port, _Fd);
	}
	return _Fd;
}

int StreamUDP::close(){
	if(_Fd > 0){
		::close(_Fd);
		_Fd = -1;
	}
	return 0;
}
