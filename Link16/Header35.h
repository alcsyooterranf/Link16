#pragma once
#include <bitset>
#include "dataType.h"

using namespace std;

//35bit报头
class Header35 {
private:
    bitset<3>	m_type;	    //时隙类型(具体规定查表)
    bitset<1>	m_PR;		//传输自由文本时，用于标识传输波形是双脉冲字符还是单脉冲字符
    bitset<15>	m_STN;	    //终端源航迹号，本时限消息的发送源编号
    bitset<16>	m_SDU;	    //保密数据单元，标识加密方式

public:
    Header35(bitset<15>	STN) : m_type(bitset<3>("100")), m_PR(bitset<1>(0)),
        m_SDU(bitset<16>("0000100010001001")) {
        m_STN = STN;
    }

    Header35(bitset<3> type, bitset<1> PR, bitset<15>	STN) : m_SDU(bitset<16>("0000100010001001")) {
        m_type = type;
        m_PR = PR;
        m_STN = STN;
    }
    string toString();
    string toString_15B();
    symbol* to_symbol();
    void setType(bitset<3> type);
    void setPR(bitset<1> PR);
    bitset<15> getSTN();
    void setSTN(bitset<15> STN);
    void setSDU(bitset<16> SDU);
};