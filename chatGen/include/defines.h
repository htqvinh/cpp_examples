/*
 * defines.h
 *
 *  Created on: Dec 27, 2016
 *      Author: htqvinh
 */

#include "VLog.h"

extern VLog SenderLog;
#define SND_LOG(s, ...) SenderLog.out("LOG", __FILE__, __LINE__, s, __VA_ARGS__)
#define SND_ERR(s, ...) SenderLog.out("ERR", __FILE__, __LINE__, s, __VA_ARGS__)
#define SND_WRN(s, ...) SenderLog.out("WRN", __FILE__, __LINE__, s, __VA_ARGS__)

extern VLog ReceiverLog;
#define REC_LOG(s, ...) ReceiverLog.out("LOG", __FILE__, __LINE__, s, __VA_ARGS__)
#define REC_ERR(s, ...) ReceiverLog.out("ERR", __FILE__, __LINE__, s, __VA_ARGS__)
#define REC_WRN(s, ...) ReceiverLog.out("WRN", __FILE__, __LINE__, s, __VA_ARGS__)

extern VLog ProcLog;
#define PROC_LOG(s, ...) ProcLog.out("LOG", __FILE__, __LINE__, s, __VA_ARGS__)
#define PROC_ERR(s, ...) ProcLog.out("ERR", __FILE__, __LINE__, s, __VA_ARGS__)
#define PROC_WRN(s, ...) ProcLog.out("WRN", __FILE__, __LINE__, s, __VA_ARGS__)
