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

enum RS_Length
{
	code_16_7 = 16,
	data_16_7 = 7,
	fec_16_7 = 9,
	code_31_15 = 31,
	data_31_15 = 15,
	fec_31_15 = 16,
};