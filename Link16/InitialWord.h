#pragma once
#include <bitset>
#include "dataType.h"

using namespace std;

//J系列消息顺序：初始字 ---> 扩展字 ---> 继续字
//75bit初始字
class InitialWord {
private:
    bitset<2>	m_format;		//字格式：初始字为00
    bitset<5>	m_signal;		//标识
    bitset<3>	m_sub_signal;	//子标识
    bitset<3>	m_length;		//消息长度，表示初始字后面的扩展字或继续字的总数，最多7个
    bitset<57>	m_message;	    //信息字
    bitset<5>	m_BIP;		    //奇偶校验，第一位空闲，后四位执行校验

    symbol*     m_S_iword;      //symbol转换后的InitialWord
    symbol*     m_RS_iword;     //RS编码后的InitialWord

public:
    InitialWord() : m_format(0b00) {
        m_S_iword = new symbol[15]();
        m_RS_iword = new symbol[31]();
    }

    ~InitialWord()
    {
        delete[] m_S_iword;
        delete[] m_RS_iword;
    }

    void RS31_15();
    void rewrite(string& bit_str);
    void clear();
    void to_symbol();
    void handler_initial_word(string& bit_data);
    void show();
    string toString_70B();
    string toString();
    string toString_STDP();
    bitset<5> getBIP();
    void setBIP(bitset<5> BIP);
    symbol* getS_iword();
    symbol* getRS_iword();
};