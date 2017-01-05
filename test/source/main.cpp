/*
 * main.cpp
 *
 *  Created on: Dec 29, 2016
 *      Author: vinhhtq
 */

#include <general.h>
#include <stdio.h>
#include <memory>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <queue>
#include <functional>
#include "StreamBase.h"
using namespace std;


mutex mtx;
queue<CPackage> vec;

void func_1(){
	mtx.lock();
	while(vec.size() > 0){
		CPackage p = vec.front();
		p._Method(p._Stream, p._Message);
		vec.pop();
	}
	mtx.unlock();
}

void create_thread(){
	thread t(func_1);
	t.detach();
}

int main(int argc, char** argv){

	create_thread();

	CMessage mess;
	mtx.lock();
	vec.push({ StreamBaseSptr(new StreamTCP("127.0.0.1", 5001)), mess, send_and_close});
	vec.push({ StreamBaseSptr(new StreamTCP("127.0.0.2", 5001)), mess, send_and_close});
	mtx.unlock();

	std::this_thread::sleep_for(chrono::seconds(10));

	return 0;
}

