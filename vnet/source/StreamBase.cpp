/*
 * StreamBase.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: htqvinh
 */

#include "StreamBase.h"
#include "ConnectorBase.h"

int StreamTCP::send(void* buff, size_t len){

	if(_Info._Fd == -1){
		NET_ERR("this stream IP(%s), port(%i) is not connected\n", _Info._Ip.c_str(), _Info._Port);
		return -1;
	}

	char* dataptr = (char*)buff;
	for(size_t t = 0, r = 0; len > 0; len -= r, t += r){
		r = :: send(_Info._Fd, dataptr + t, len, 0);
		if(r == -1){
			NET_ERR("send to IP(%s), port(%i). are failure\n", _Info._Ip.c_str(), _Info._Port);
			return -1;
		}
	}
	return 0;
}

int StreamTCP::recv(void* buff, size_t len){

	if(_Info._Fd == -1){
		NET_ERR("this stream IP(%s), port(%i) is not connected\n", _Info._Ip.c_str(), _Info._Port);
		return -1;
	}

	char* dataptr = (char*)buff;
	for(size_t t = 0, r = 0; len > 0; len -= r, t += r){
		r = :: recv(_Info._Fd, dataptr + t, len, 0);
		if(r == -1){
			NET_ERR("receive from IP(%s), port(%i). are failure\n", _Info._Ip.c_str(), _Info._Port);
			return -1;
		}
	}
	return 0;
}

int StreamTCP::connect(){
	if(_Info._Fd == -1){
		ConnectorTCP tcp;
		tcp.connect(_Info._Ip, _Info._Port, _Info._Fd);
	}
	return _Info._Fd;
}

int StreamTCP::close(){
	if(_Info._Fd > 0){
		::close(_Info._Fd);
		_Info._Fd = -1;
	}
	return 0;
}

int StreamUDP::send(void* buff, size_t len){

	if(_Info._Fd == -1){
		NET_ERR("this stream IP(%s), port(%i) is not connected\n", _Info._Ip.c_str(), _Info._Port);
		return -1;
	}

	struct sockaddr_in dest;
	socklen_t socksize = sizeof(struct sockaddr_in);

	memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(_Info._Ip.c_str());
	dest.sin_port = htons(_Info._Port);

	int r = sendto(_Info._Fd, buff, len, 0, (struct sockaddr *)&dest, socksize);
	if(r < len){
		NET_LOG("send real length(%i) < expect length(%i)\n", r, len);
		return -1;
	}

	return 0;
}

int StreamUDP::recv(void* buff, size_t len){

	if(_Info._Fd == -1){
		NET_ERR("this stream IP(%s), port(%i) is not connected\n", _Info._Ip.c_str(), _Info._Port);
		return -1;
	}

	struct sockaddr_in dest;
	socklen_t socksize = sizeof(struct sockaddr_in);

	int r = recvfrom(_Info._Fd, buff, len, 0, (struct sockaddr *)&dest, &socksize);
	if(r < len){
		NET_LOG("receive real length(%i) < expect length(%i)\n", r, len);
		return -1;
	}

	return 0;
}

int StreamUDP::connect(){
	if(_Info._Fd == -1){
		ConnectorUDP tcp;
		tcp.connect(_Info._Ip, _Info._Port, _Info._Fd);
	}
	return _Info._Fd;
}

int StreamUDP::close(){
	if(_Info._Fd > 0){
		::close(_Info._Fd);
		_Info._Fd = -1;
	}
	return 0;
}
