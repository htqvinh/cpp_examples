/*
 * defines.h
 *
 *  Created on: Dec 20, 2016
 *      Author: htqvinh
 */

#ifndef INCLUDE_DEFINES_H_
#define INCLUDE_DEFINES_H_

extern VLog NetLog;
#define NET_LOG(s, ...) NetLog.out("LOG", __FILE__, __LINE__, s, __VA_ARGS__)
#define NET_ERR(s, ...) NetLog.out("ERR", __FILE__, __LINE__, s, __VA_ARGS__)
#define NET_WRN(s, ...) NetLog.out("WRN", __FILE__, __LINE__, s, __VA_ARGS__)

#endif /* INCLUDE_DEFINES_H_ */
