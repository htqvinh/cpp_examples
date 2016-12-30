/*
 * Receiver.h
 *
 *  Created on: Dec 27, 2016
 *      Author: htqvinh
 */

#ifndef INCLUDE_RECEIVER_H_
#define INCLUDE_RECEIVER_H_

class Receiver {
public:
	Receiver(unsigned port);
	virtual ~Receiver();

protected:
	void process();

protected:
	unsigned _Port;
};

#endif /* INCLUDE_RECEIVER_H_ */
