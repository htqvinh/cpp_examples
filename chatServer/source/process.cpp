/*
 * process.cpp
 *
 *  Created on: Jan 4, 2017
 *      Author: htqvinh
 */

#include <map>
#include "general.h"
#include "defines.h"
#include "Sender.h"

using namespace std;
extern Sender snd;
extern map<string, StreamBaseSptr > stream_map;

int process_packet_login (StreamBaseSptr sender, string data);
int process_packet_chat_group (StreamBaseSptr sender, string data);

int process_packet_to(const CPackage &p){

	CMessage msg = p._Message;

	std::function<int (StreamBaseSptr, string)> f;

	switch(msg._Type){
	case CMessage::M_LOGIN: { f = process_packet_login; break; }
	case CMessage::M_CHATG: { f = process_packet_chat_group; break; }
	default: { f = NULL; break; }
	}

	if(f != NULL){
		f (p._Stream, p._Message._Data);
	}

	return 0;
}

int process_packet_login (StreamBaseSptr sender, string data){

	cout << MAIN_LOG("Has a account %s\n, is logging", data.c_str());

	StreamBaseSptr stream = sender;
	string usr_name = data;
	stream_map.insert({usr_name, stream});
	snd.push({stream, {CMessage::M_LOGIN, "success"}, send_and_keep});

	return 0;
}

int process_packet_chat_group (StreamBaseSptr sender, string data){

	cout << MAIN_LOG("Message is %s\n", data.c_str());

	string content = data;

	for (auto it=stream_map.begin(); it!=stream_map.end(); ++it){
		StreamBaseSptr stream = (*it).second;
		if(stream != sender){
			snd.push({stream, {CMessage::M_CHATG, content}, send_and_keep});
		}
	}

	return 0;
}


