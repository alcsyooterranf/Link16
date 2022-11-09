#pragma once
#include <bitset>
#include "tools.h"

using namespace std;

//35bit报头
class Header35 {
private:
    bitset<3>	m_type;	    //时隙类型
    bitset<1>	m_PR;		//传输自由文本时，用于标识传输波形是双脉冲字符还是单脉冲字符
    bitset<15>	m_STN;	    //终端源航迹号，本时限消息的发送源编号
    bitset<16>	m_SDU;	    //保密数据单元，标识加密方式

public:
    Header35(bitset<15>	STN) : m_type(bitset<3>("001")), m_PR(bitset<1>(0)),
        m_SDU(bitset<16>("0000100010001001")) {
        m_STN = STN;
    }
    string toString();
    symbol* to_symbol();
};