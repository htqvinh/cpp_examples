/*
 * defines.h
 *
 *  Created on: Dec 20, 2016
 *      Author: htqvinh
 */

extern VLog MainLog;
#define MAIN_LOG(s, ...) MainLog.out("LOG", __FILE__, __LINE__, s, __VA_ARGS__)
#define MAIN_ERR(s, ...) MainLog.out("ERR", __FILE__, __LINE__, s, __VA_ARGS__)
#define MAIN_WRN(s, ...) MainLog.out("WRN", __FILE__, __LINE__, s, __VA_ARGS__)
