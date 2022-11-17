#pragma once
#include <bitset>
#include "dataType.h"

using namespace std;

//75bit继续字，可以不按顺序发送
class ContinueWord {
private:
    bitset<2>	m_format;		//字格式：继续字为01
    bitset<5>	m_signal;		//继续字标识，每条J系列消息最多允许定义32个继续字
    bitset<63>	m_message;	    //信息字
    bitset<5>	m_BIP;		    //奇偶校验，第一位空闲，后四位执行校验

public:
    ContinueWord() : m_format(0b01) {
    }

    void clear();
    symbol* to_symbol();
    void handler_continue_word(string& bit_data);
    void show();
    string toString_70B();
    string toString();
    bitset<5> getBIP();
    void setBIP(bitset<5> BIP);
};