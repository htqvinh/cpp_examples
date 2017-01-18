/*
 * main.cpp
 *
 *  Created on: Dec 29, 2016
 *      Author: vinhhtq
 */

#include <stdio.h>
#include <memory>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include "general.h"
#include "StreamBase.h"
using namespace std;


mutex mtx;
queue<CPackage> vec;

void func_1(){
	mtx.lock();
	while(vec.size() > 0){
		CPackage p = vec.front();
		p._Send_Method(p._Stream, p._Message);
		vec.pop();
	}
	mtx.unlock();
}

void create_thread(){
	thread t(func_1);
	t.detach();
}

void print_vector(vector<int> &v){
	for(vector<int>::iterator it = v.begin(); it != v.end(); ++it){
		cout << *it << ", ";
	}
	cout << endl;
}

int main(int argc, char** argv){

//	create_thread();
//
//	CMessage mess;
//	mtx.lock();
//	vec.push({ StreamBaseSptr(new StreamTCP("127.0.0.1", 5001)), mess, send_and_close});
//	vec.push({ StreamBaseSptr(new StreamTCP("127.0.0.2", 5001)), mess, send_and_close});
//	mtx.unlock();
//
//	std::this_thread::sleep_for(chrono::seconds(10));


	vector<int> v = {0, 1, 2, 3, 4, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 5, 6, 7, 8, 9, 10, 1, 2, 3};

	sort(v.begin(), v.end());
	unique(v.begin(), v.end());
	print_vector(v);

	for(; v.size() > 4; ){
		v.erase(v.begin() + 4);
		print_vector(v);
	}

	return 0;
}

