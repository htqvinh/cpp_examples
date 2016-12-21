/*
 * defines.h
 *
 *  Created on: Dec 20, 2016
 *      Author: htqvinh
 */

#ifndef INCLUDE_DEFINES_H_
#define INCLUDE_DEFINES_H_

extern VLog NetLog;
#define NET_ERR(s, ...) NetLog.err(s, __VA_ARGS__)

#endif /* INCLUDE_DEFINES_H_ */
