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

    symbol*     m_S_cword;      //symbol转换后的ContinueWord
    symbol*     m_RS_cword;     //RS编码后的ContinueWord

public:
    ContinueWord() : m_format(0b01) {
        m_S_cword = new symbol[15]();
        m_RS_cword = new symbol[31]();
    }

    ~ContinueWord()
    {
        delete[] m_S_cword;
        delete[] m_RS_cword;
    }

    void RS31_15();
    void rewrite(string& bit_str);
    void clear();
    void to_symbol();
    void handler_continue_word(string& bit_data);
    void show();
    string toString_70B();
    string toString();
    string toString_STDP();
    bitset<5> getBIP();
    void setBIP(bitset<5> BIP);
    symbol* getS_cword();
    symbol* getRS_cword();
};