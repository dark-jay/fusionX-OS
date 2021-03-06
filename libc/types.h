
#ifndef __TYPES_H
#define __TYPES_H

	typedef char int8_t;
	typedef unsigned char uint8_t;

	typedef short int16_t;
	typedef unsigned short uint16_t;

	typedef int int32_t;
	typedef unsigned int uint32_t;

	typedef long long int int64_t;
	typedef unsigned long long int uint64_t;

	// asm macro
	#define asm 		__asm__
	#define asmv 		__asm__ __volatile__

	// std macro 
	#define NULL 0
	#define true 1
	#define false 0

#endif
