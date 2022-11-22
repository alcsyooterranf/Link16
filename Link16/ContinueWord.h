#pragma once
#include <bitset>
#include "dataType.h"

using namespace std;

//75bit�����֣����Բ���˳����
class ContinueWord {
private:
    bitset<2>	m_format;		//�ָ�ʽ��������Ϊ01
    bitset<5>	m_signal;		//�����ֱ�ʶ��ÿ��Jϵ����Ϣ���������32��������
    bitset<63>	m_message;	    //��Ϣ��
    bitset<5>	m_BIP;		    //��żУ�飬��һλ���У�����λִ��У��

    symbol*     m_S_cword;      //symbolת�����ContinueWord
    symbol*     m_RS_cword;     //RS������ContinueWord

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