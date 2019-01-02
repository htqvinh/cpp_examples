/*
 * Receiver.cpp
 *
 *  Created on: Dec 27, 2016
 *      Author: htqvinh
 */

#include "Receiver.h"

Receiver::Receiver(
		AcceptorBaseSptr acceptor, unsigned port,
		unsigned num_of_threads)
:
		_Acceptor(acceptor), _Port(port),
		VHandler(num_of_threads){ }

Receiver::~Receiver() { }

int Receiver::init(){
	if(nullptr == _Acceptor)
		return -1;
	if(-1 == _Acceptor->init(_Port))
		return -1;
	return 0;
}

void Receiver::process(){

	std::function<int(const StreamBaseSptr&)> addNewConnection(
		[this](const StreamBaseSptr& stream) -> int {

			_StreamMap.insert_(stream->Info(), stream);

		}
	);

	std::function<int(const StreamInfo&)> disconectConnection(
		[this](const StreamInfo& info) -> int {

			_StreamMap.delete_(info);

		}
	);

	std::function<int(const StreamInfo&, ByteBuffer&)> getNewData(
		[this](const StreamInfo& info, ByteBuffer& data) -> int {

			StreamBaseSptr stream;
			if(_StreamMap.find_(info, stream)){

				//Maybe, one or many packages is coming to at once
				//Check & divide byte buffer to CPackages, then pushing queue to process

				BYTE* dptr = data.dataPtr();
				unsigned total_len = data.length();

				do{

					if(total_len < NUMBER_BYTES_OF_MSG_TYPE){ break; }
					CPackage::Type type = CPackage::_MIN;
					memcpy(&type, dptr, NUMBER_BYTES_OF_MSG_TYPE);
					total_len -= NUMBER_BYTES_OF_MSG_TYPE;

					if(total_len < NUMBER_BYTES_OF_MSG_LEN){ break; }
					unsigned contentL = 0;
					memcpy(&contentL, dptr + NUMBER_BYTES_OF_MSG_TYPE, NUMBER_BYTES_OF_MSG_LEN);
					total_len -= NUMBER_BYTES_OF_MSG_LEN;

					if(total_len < contentL) { break; }
					unsigned packageL =
							NUMBER_BYTES_OF_MSG_TYPE +
							NUMBER_BYTES_OF_MSG_LEN +
							contentL;

					ByteBuffer d;
					d.append(dptr, packageL);
					pushToQueue({stream, d});
					total_len -= contentL;

					dptr += packageL;

				}while(total_len > 0);
			}

		}
	);

	_Acceptor->process(addNewConnection, disconectConnection, getNewData);
}

void Receiver::pushToQueue(const CPackage& p){
    std::unique_lock<std::mutex> lk(_mtx);
    _Pool.push(p);
	_cv.notify_one();
}


void Receiver::waitToPopFromQueue(CPackage& p){

    std::unique_lock<std::mutex> lk(_mtx);
    _cv.wait(lk, [this]() -> bool {
		if(_Pool.isEmpty()){
			cout << "Receiver is waiting for package coming...\n";
			return false;
		}
		return true;
	});

	_Pool.pop(p);

}

