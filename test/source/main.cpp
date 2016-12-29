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
using namespace std;

class A{
public:
	A(){}
	~A(){}
};

typedef shared_ptr<A> Aptr;

struct S{
	Aptr 					_ptr;
	const char* 			_str;
	function<int(Aptr)> 		_fun;
};
mutex mtx;
//vector<shared_ptr<A>> vec;
//queue<Aptr> vec;
queue<S> vec;

class A1 : public A{
public:
	A1(){}
	~A1(){}
};

class A2 : public A{
public:
	A2(){}
	~A2(){}
};

int func_1(){
	while(1){
		mtx.lock();
		if(vec.size() > 0){
			S p = vec.front();
			p._fun(p._ptr);
			vec.pop();
		}
		mtx.unlock();
		this_thread::sleep_for(chrono::seconds(2));
	}
	return 0;
}

int echo(Aptr p){
	printf("func_2: %x\n", &(p));
	return 0;
}

void create_thread(){
	thread t(func_1);
	t.detach();
}

int main(int argc, char** argv){


	mtx.lock();
	vec.push({ Aptr(new A1()), "A1", echo});
	vec.push({ Aptr(new A2()), "A2", echo});
	mtx.unlock();

	create_thread();

	std::this_thread::sleep_for(chrono::seconds(10));

	return 0;
}

