/*
 * ChatGeneral.cpp
 *
 *  Created on: Dec 23, 2016
 *      Author: htqvinh
 */

#include <general.h>
#include "StreamBase.h"


int send_message(const StreamBaseSptr& stream_ptr, ByteBuffer& buff){

	if(stream_ptr == nullptr) { return -1; }
	if(-1 == stream_ptr->connect()) { return -1; }

	/* sent data of packet */
	unsigned char* dataptr = buff.dataPtr();
	unsigned length = buff.length();
	if(-1 == stream_ptr->send(dataptr, length)){
		return -1;
	}

	return 0;
}

int send_and_close(StreamBaseSptr stream_ptr, ByteBuffer& buff){

	send_message(stream_ptr, buff);
	stream_ptr->close();
	return 0;
}

int send_and_keep(StreamBaseSptr stream_ptr, ByteBuffer& buff){

	return send_message(stream_ptr, buff);
}



