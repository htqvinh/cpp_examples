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

int process_packet_to(const CPackage &p){

	CMessage msg = p._Message;

	switch(msg._Type){
	case CMessage::M_LOGIN:
	{
		StreamBaseSptr stream = p._Stream;
		string usr_name = p._Message._Data;
		stream_map.insert({usr_name, stream});
		snd.push({stream, {CMessage::M_LOGIN, "success"}, send_and_keep});
		break;
	}
	case CMessage::M_CHATG:
	{
		cout << MAIN_LOG("Message is %s\n", p._Message._Data.c_str());

		string content = p._Message._Data;
		string delimiter = ": ";
		string sender = content.substr(0, content.find(delimiter));

		for (auto it=stream_map.begin(); it!=stream_map.end(); ++it){
			if((*it).first != sender){
				snd.push({(*it).second, {CMessage::M_CHATG, content}, send_and_keep});
			}
		}
		break;
	}
	default:
		break;
	}

	return 0;
}


