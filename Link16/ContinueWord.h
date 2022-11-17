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