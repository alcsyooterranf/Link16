#pragma once
#include <bitset>
#include "dataType.h"

using namespace std;

//75bit��չ�֣����밴˳����
class ExtendWord {
private:
    bitset<2>	m_format;		//�ָ�ʽ����չ��Ϊ10
    bitset<68>	m_message;	    //��Ϣ��
    bitset<5>	m_BIP;		    //��żУ�飬��һλ���У�����λִ��У��

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