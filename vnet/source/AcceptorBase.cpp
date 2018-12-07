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
    	cout << NET_ERR("Can't listen socket(%d)\n", sockid);
    	return -1;
    }

    _sockId = sockid;

    return _sockId;
}

int AcceptorTCP::process(StreamBaseSptr& stream, string& data){

	if(_sockId < 0) return -1;

    struct sockaddr_in address;
    int addrlen = sizeof(address);

    //clear the socket set
    FD_ZERO(&_readfds);

    //add master socket to set
    FD_SET(_sockId, &_readfds);
    int max_sd = _sockId;

    //add child sockets to set
    for (unsigned i = 0 ; i < MAX_CLIENTS ; i++) {

        //socket descriptor
        int sd = _client_socket[i];

        //if valid socket descriptor then add to read list
        if(sd > 0)
        	FD_SET(sd , &_readfds);

        //highest file descriptor number, need it for the select function
        if(sd > max_sd)
            max_sd = sd;
    }

    //wait for an activity on one of the sockets, timeout is NULL, so wait indefinitely
    int activity = select(max_sd + 1 , &_readfds , NULL , NULL , NULL);
    if ((activity < 0) && (errno != EINTR)) {
    	cout << NET_ERR("select activity(%d), error(%d)\n", activity, errno);
    }

    //If something happened on the master socket, then its an incoming connection
    if (FD_ISSET(_sockId, &_readfds)){

        int new_socket = accept(_sockId, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            cout << NET_ERR("accept error(%d)\n", new_socket);
            exit(EXIT_FAILURE);
        }

        //inform user of socket number - used in send and receive commands
        cout << NET_LOG("new connection, socket fd(%d), ip(%s), port(%d)\n",
        		new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

        //TODO

        //add new socket to array of sockets
        for (unsigned i = 0; i < MAX_CLIENTS; ++i) {
            //if position is empty
            if(_client_socket[i] == 0 )
            {
                _client_socket[i] = new_socket;
                cout << NET_LOG("Adding socket(%d) to list at (%d)\n" , new_socket, i);
                break;
            }
        }
    }

    //else its some IO operation on some other socket
    for (unsigned i = 0; i < MAX_CLIENTS; ++i)
    {
        int sd = _client_socket[i];

        if (FD_ISSET( sd , &_readfds))
        {
        	char buffer[1024];
        	int valread = read( sd , buffer, 1024);

            //Check if it was for closing , and also read the, incoming message
            if (valread == 0) {

                //Somebody disconnected , get his details and print
                getpeername(sd , (struct sockaddr*)&address, (socklen_t*)&addrlen);
                printf("Host disconnected , ip %s , port %d \n" ,
                      inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

                //Close the socket and mark as 0 in list for reuse
                close( sd );
                _client_socket[i] = 0;
            }

            //Echo back the message that came in
            else
            {
                //set the string terminating NULL byte on the end
                //of the data read
                buffer[valread] = '\0';
                send(sd , buffer , strlen(buffer) , 0 );
            }
        }
    }

	struct sockaddr_in dest;
	socklen_t socksize = sizeof(struct sockaddr_in);

	int consocket = accept(_sockId, (struct sockaddr *)&dest, &socksize);

	stream = StreamBaseSptr(new StreamTCP(
			inet_ntoa(dest.sin_addr), htons(dest.sin_port), consocket ));

	return 1;
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

int AcceptorUDP::process(StreamBaseSptr& stream, string& data){

	if(_sockId < 0) return -1;

	char tmp;
	struct sockaddr_in dest;
	socklen_t socksize = sizeof(struct sockaddr_in);

	/*
	 * To receive 1 byte from client
	 * When client connected, will sent 1 bytes, not be used
	 */
	recvfrom(_sockId, &tmp, sizeof(char), 0, (struct sockaddr *)&dest, &socksize);

	stream = StreamBaseSptr(new StreamUDP(inet_ntoa(dest.sin_addr), htons(dest.sin_port), _sockId));

	return 1;
}

