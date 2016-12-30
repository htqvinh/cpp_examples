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
	virtual void process() = 0;
	int isActive() { return _isActive; };
	void active(bool f = true);

protected:
	bool 	 _isActive;
	unsigned _Number_of_Threads;
};

#endif /* VHANDLER_H_ */
