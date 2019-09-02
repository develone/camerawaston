/*********************************************************************
 * base.h
 *********************************************************************/

#ifndef _BASE_H_
#define _BASE_H_

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef schar
#define schar signed char
#endif

#ifndef uint
	#ifndef ULTIBO
	#define uint unsigned int
	#endif
#endif

#ifndef ushort
	#ifndef ULTIBO
	#define ushort unsigned short
	#endif
#endif

#ifndef ulong
	#ifndef ULTIBO
	#define ulong unsigned long
	#endif
#endif

#ifndef max
#define max(a,b)	((a) > (b) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)	((a) < (b) ? (a) : (b))
#endif
#define max3(a,b,c)	((a) > (b) ? max((a),(c)) : max((b),(c)))
#define min3(a,b,c)	((a) < (b) ? min((a),(c)) : min((b),(c)))

#endif

