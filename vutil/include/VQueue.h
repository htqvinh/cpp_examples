/*
 * VQueueSafe.h
 *
 *  Created on: Dec 27, 2016
 *      Author: htqvinh
 */

#ifndef VQUEUESAFE_H_
#define VQUEUESAFE_H_

#include <queue>
#include <mutex>
using namespace std;

template <class T>
class VQueue {

public:
	VQueue(){ }

	virtual ~VQueue(){ }

	bool isEmpty(){
		return _Content.empty();
	}

	void push(const T& element){
		_Content.push(element);
	}

	T pop(){
		T tmp = _Content.front();
		_Content.pop();
		return tmp;
	}

	int size(){
		return _Content.size();
	}

	void lock(){
		_mtx.lock();
	}

	void unlock(){
		_mtx.unlock();
	}

protected:
	queue<T> 	_Content;
	mutex 		_mtx;
};

#endif /* VQUEUESAFE_H_ */
