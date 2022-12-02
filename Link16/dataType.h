#pragma once
#include <bitset>

using namespace std;

typedef short		int16_t;	//16λ������
typedef int			int32_t;	//32λ������
typedef long long	int64_t;	//64λ������

typedef unsigned char		uint8_t;	//8λ�޷�������
typedef unsigned short		uint16_t;	//16λ�޷�������
typedef unsigned int		uint32_t;	//32λ�޷�������
typedef unsigned long long	uint64_t;	//64λ�޷�������

typedef bitset<5>	symbol;		//5bit = 1Symbol, ע��sizeof(symbol) = 4

enum RS_Length
{
	code_16_7 = 16,
	data_16_7 = 7,
	fec_16_7 = 9,
	code_31_15 = 31,
	data_31_15 = 15,
	fec_31_15 = 16,
};