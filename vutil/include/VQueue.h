/*
 * VQueueSafe.h
 *
 *  Created on: Dec 27, 2016
 *      Author: htqvinh
 */

#ifndef VQUEUE_H_
#define VQUEUE_H_

#include <queue>
#include <mutex>
using namespace std;

template <class T>
class VQueue {

public:
	VQueue(){ }

	virtual ~VQueue(){ }

	void push(T element){
		lock_guard<std::mutex> lock(_mtx);
		_Content.push(element);
	}

	bool pop(T& val){
		lock_guard<std::mutex> lock(_mtx);
		if(size() == 0){
			return 0;
		}
		val = _Content.front();
		_Content.pop();
		return 1;
	}

	bool isEmpty(){
		return _Content.size() == 0;
	}

	int size(){
		return _Content.size();
	}

protected:
	queue<T> 	_Content;
	mutex 		_mtx;
};

#endif /* VQUEUESAFE_H_ */
