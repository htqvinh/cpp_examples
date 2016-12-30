/*
 * defines.h
 *
 *  Created on: Dec 20, 2016
 *      Author: htqvinh
 */

extern VLog NetLog;
#define NET_LOG(s, ...) NetLog.out("LOG", __FILE__, __LINE__, s, __VA_ARGS__)
#define NET_ERR(s, ...) NetLog.out("ERR", __FILE__, __LINE__, s, __VA_ARGS__)
#define NET_WRN(s, ...) NetLog.out("WRN", __FILE__, __LINE__, s, __VA_ARGS__)
