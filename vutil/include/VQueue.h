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

	VQueue():_Length(0){ }

	virtual ~VQueue(){ }

	void push(T element){
		_Content.push(element);
		++_Length ;
	}

	bool pop(T& val){
		val = _Content.front();
		_Content.pop();
		--_Length;
		return 1;
	}

	bool isEmpty(){
		return _Length == 0;
	}

	int size(){
		return _Length;
	}

protected:
	unsigned 	_Length;
	queue<T> 	_Content;
};

#endif /* VQUEUESAFE_H_ */
