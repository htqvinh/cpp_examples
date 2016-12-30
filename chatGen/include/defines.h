/*
 * defines.h
 *
 *  Created on: Dec 27, 2016
 *      Author: htqvinh
 */

extern VLog SenderLog;
#define SND_LOG(s, ...) SenderLog.out("LOG", __FILE__, __LINE__, s, __VA_ARGS__)
#define SND_ERR(s, ...) SenderLog.out("ERR", __FILE__, __LINE__, s, __VA_ARGS__)
#define SND_WRN(s, ...) SenderLog.out("WRN", __FILE__, __LINE__, s, __VA_ARGS__)
