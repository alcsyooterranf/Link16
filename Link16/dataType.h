#pragma once
#pragma pack(1)
#include <bitset>

using namespace std;

typedef short		int16_t;	//16位的整数
typedef int			int32_t;	//32位的整数
typedef long long	int64_t;	//64位的整数

typedef unsigned char		uint8_t;	//8位无符号整数
typedef unsigned short		uint16_t;	//16位无符号整数
typedef unsigned int		uint32_t;	//32位无符号整数
typedef unsigned long long	uint64_t;	//64位无符号整数

typedef bitset<5>	symbol;		//5bit = 1Symbol

//35bit报头
struct header_35 {
	bitset<3>	type;	//时隙类型
	bitset<1>	PR;		//传输自由文本时，用于标识传输波形是双脉冲字符还是单脉冲字符
	bitset<15>	STN;	//终端源航迹号，本时限消息的发送源编号
	bitset<16>	SDU;	//保密数据单元，标识加密方式
};

//J系列消息顺序：初始字 ---> 扩展字 ---> 继续字
//75bit初始字
struct initial_word {
	bitset<2>	format;		//字格式：初始字为00
	bitset<5>	signal;		//标识
	bitset<3>	sub_signal;	//子标识
	bitset<3>	length;		//消息长度，表示初始字后面的扩展字或继续字的总数，最多7个
	bitset<57>	message;	//信息字
	bitset<5>	BIP;		//奇偶校验，第一位空闲，后四位执行校验
};

//75bit扩展字，必须按顺序发送
struct extend_word {
	bitset<2>	format;		//字格式：扩展字为10
	bitset<68>	message;	//信息字
	bitset<5>	BIP;		//奇偶校验，第一位空闲，后四位执行校验
};

//75bit继续字，可以不按顺序发送
struct continue_word {
	bitset<2>	format;		//字格式：继续字为01
	bitset<5>	signal;		//继续字标识，每条J系列消息最多允许定义32个继续字
	bitset<63>	message;	//信息字
	bitset<5>	BIP;		//奇偶校验，第一位空闲，后四位执行校验
};