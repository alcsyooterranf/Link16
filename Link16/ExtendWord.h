#pragma once
#include <bitset>
#include "dataType.h"

using namespace std;

//75bit扩展字，必须按顺序发送
class ExtendWord {
private:
    bitset<2>	m_format;		//字格式：扩展字为10
    bitset<68>	m_message;	    //信息字
    bitset<5>	m_BIP;		    //奇偶校验，第一位空闲，后四位执行校验

public:
    ExtendWord() : m_format(0b10) {
    }

    void clear();
    symbol* to_symbol();
    void handler_extend_word(string& bit_data);
    void show();
    string toString_70B();
    string toString();
    bitset<5> getBIP();
    void setBIP(bitset<5> BIP);
};