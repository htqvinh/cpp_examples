/*
 * AcceptorBase.cpp
 *
 *  Created on: Dec 21, 2016
 *      Author: vinhhtq
 */


#include "AcceptorBase.h"
#include "VUtil.h"
#include <fcntl.h>
#include <sstream>
using namespace std;

#define MAX_LEN 1024

int AcceptorTCP::init(int port){

	if(_listenSocket > 0) return _listenSocket;

    int sockid = socket(AF_INET, SOCK_STREAM, 0);
	if(sockid == -1){
		NET_ERR("Can't initialize a socket(%i)", sockid);
		return -1;
	}

    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(port);

    if(bind(sockid, (struct sockaddr *)&serv, sizeof(struct sockaddr)) == -1){
    	NET_ERR("Can't bind socket on port(%i)\n", port);
    	return -1;
    }

    if(listen(sockid, 1) == -1){
    	NET_ERR("Can't listen socket(%d)\n", sockid);
    	return -1;
    }

    _listenSocket = sockid;

    return _listenSocket;
}

/**
 * @name		: AcceptorTCP::process
 * @input		:
 * @output		:
 * StreamBaseSptr& 	stream 	//return stream once a new connection is coming
 * string& 			data 	//return data once client send data
 */
int AcceptorTCP::process(
		std::function<int(const StreamBaseSptr&)> processNewConnection,
		std::function<int(const StreamInfo&)> processDisconnected,
		std::function<int(const StreamInfo&, ByteBuffer&)> processNewData){

	if(_listenSocket < 0) return -1;

    //clear the socket set
    FD_ZERO(&_readfds);

    //add master socket to set
    FD_SET(_listenSocket, &_readfds);

    int max_sd = _listenSocket;
    //add child sockets to set
    for (unsigned i = 0 ; i < MAX_CLIENTS ; i++) {

        //socket descriptor
        int sd = _connectSocket[i];

        //if valid socket descriptor then add to read list
        if (sd > 0)
        	FD_SET(sd , &_readfds);

        //highest file descriptor number, need it for the select function
        if (sd > max_sd)
        	max_sd = sd;
    }

    //wait for an activity on one of the sockets, timeout is NULL, so wait indefinitely
    int activity = select(max_sd + 1 , &_readfds , NULL , NULL , NULL);
    if ((activity < 0) && (errno != EINTR)) {
    	NET_ERR("select activity(%d), error(%d)\n", activity, errno);
    	return -2;
    }

    //If something happened on the master socket, then its an incoming connection
    if (FD_ISSET(_listenSocket, &_readfds)){

        struct sockaddr_in address;
        int addrlen = sizeof(address);

        int new_socket = accept(_listenSocket, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            NET_ERR("accept error(%d)\n", new_socket);
            return -3;
        }

        fcntl(new_socket, F_SETFL, O_NONBLOCK);
        StreamBaseSptr new_stream(new StreamTCP(
    			inet_ntoa(address.sin_addr), htons(address.sin_port), new_socket));
        processNewConnection(new_stream);

        //add new socket to array of sockets
        for (unsigned i = 0; i < MAX_CLIENTS; ++i) {
            //if position is empty
            if(_connectSocket[i] == 0 ) {
                _connectSocket[i] = new_socket;
                NET_LOG("Adding socket(%d) to list at (%d)\n" , new_socket, i);
                break;
            }
        }

        return 1; //return new connection
    }

    //else its some IO operation on some other socket
    int valread;
    char buffer[MAX_LEN];
    ByteBuffer new_data;
    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        int sd = _connectSocket[i];

        if (FD_ISSET( sd , &_readfds))
        {
			while((valread = read( sd , buffer, MAX_LEN)) > 0){
				new_data.append(buffer, valread);
			}

			//get detail from client
		    struct sockaddr_in address;
		    int addrlen = sizeof(address);
			getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);

			StreamInfo connectInfo(inet_ntoa(address.sin_addr), ntohs(address.sin_port), sd);

			switch (valread){
			case 	-1: //read to end of stream
	            NET_LOG("client IP(%s) PORT(%d) --> send data(length=%u)\n"
	            		, connectInfo._Ip.c_str(), connectInfo._Port, new_data.length());
	            processNewData(connectInfo, new_data);
				break;
			case 	 0: //some client disconnected
	            NET_LOG("client IP(%s) PORT(%d) --> disconnect\n"
	            		, connectInfo._Ip.c_str(), connectInfo._Port);
				processDisconnected(connectInfo);
				close(sd);
				_connectSocket[i] = 0;
				break;
			default:
				NET_LOG("client IP(%s) PORT(%d) --> error(%d)\n"
						, connectInfo._Ip.c_str(), connectInfo._Port, valread);
				break;
			}
        }
    }

	return 2;
}

int AcceptorUDP::init(int port){

	if(_listenSocket > 0) return _listenSocket;

	int sockid = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockid == -1){
		NET_ERR("Can't initialize a socket(%i)", sockid);
		return -1;
	}

    struct sockaddr_in serv;
	memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(port);

	if(bind(sockid, (struct sockaddr *)&serv, sizeof(struct sockaddr)) == -1){
		NET_ERR("Can't bind socket on port(%i)\n", port);
		return -1;
	}

    _listenSocket = sockid;

	return _listenSocket;
}

int AcceptorUDP::process(
		std::function<int(const StreamBaseSptr&)> processNewConnection,
		std::function<int(const StreamInfo&)> processDisconnected,
		std::function<int(const StreamInfo&, ByteBuffer&)> processNewData){

	if(_listenSocket < 0) return -1;

	char tmp;
	struct sockaddr_in dest;
	socklen_t socksize = sizeof(struct sockaddr_in);

	/*
	 * To receive 1 byte from client
	 * When client connected, will sent 1 bytes, not be used
	 */
	recvfrom(_listenSocket, &tmp, sizeof(char), 0, (struct sockaddr *)&dest, &socksize);

	StreamBaseSptr new_stream(new StreamUDP(
			inet_ntoa(dest.sin_addr), htons(dest.sin_port), _listenSocket));
	processNewConnection(new_stream);

	return 1;
}

