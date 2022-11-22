#pragma once
#include <bitset>
#include "dataType.h"

using namespace std;

//75bit��չ�֣����밴˳����
class ExtendWord {
private:
    bitset<2>	m_format;	    //�ָ�ʽ����չ��Ϊ10
    bitset<68>	m_message;	    //��Ϣ��
    bitset<5>	m_BIP;		    //��żУ�飬��һλ���У�����λִ��У��

    symbol*     m_S_eword;      //symbolת�����ExtendWord
    symbol*     m_RS_eword;     //RS������ExtendWord

public:
    ExtendWord() : m_format(0b10) {
        m_S_eword = new symbol[15]();
        m_RS_eword = new symbol[31]();
    }

    ~ExtendWord()
    {
        delete[] m_S_eword;
        delete[] m_RS_eword;
    }

    void RS31_15();
    void rewrite(string& bit_str);
    void clear();
    void to_symbol();
    void handler_extend_word(string& bit_data);
    void show();
    string toString_70B();
    string toString();
    string toString_STDP();
    bitset<5> getBIP();
    void setBIP(bitset<5> BIP);
    symbol* getS_eword();
    symbol* getRS_eword();
};