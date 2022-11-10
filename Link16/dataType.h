#pragma once
#include <bitset>

using namespace std;

typedef short		int16_t;	//16位的整数
typedef int			int32_t;	//32位的整数
typedef long long	int64_t;	//64位的整数

typedef unsigned char		uint8_t;	//8位无符号整数
typedef unsigned short		uint16_t;	//16位无符号整数
typedef unsigned int		uint32_t;	//32位无符号整数
typedef unsigned long long	uint64_t;	//64位无符号整数

typedef bitset<5>	symbol;		//5bit = 1Symbol, 注意sizeof(symbol) = 4