/*
 * VHandler.h
 *
 *  Created on: Dec 30, 2016
 *      Author: htqvinh
 */

#ifndef VHANDLER_H_
#define VHANDLER_H_

class VHandler {

public:
	VHandler(unsigned num_of_thread = 1);
	virtual ~VHandler();
	int isActive() { return _isActive; };
	void active(bool f = true);

protected:
	void run();
	virtual int init() = 0;
	virtual void process() = 0;

protected:
	bool 	 _isActive;
	unsigned _Number_of_Threads;
};

#endif /* VHANDLER_H_ */
