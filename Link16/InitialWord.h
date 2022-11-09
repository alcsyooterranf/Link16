#pragma once
#include <bitset>
#include "tools.h"

using namespace std;

//Jϵ����Ϣ˳�򣺳�ʼ�� ---> ��չ�� ---> ������
//75bit��ʼ��
class InitialWord {
private:
    bitset<2>	m_format;		//�ָ�ʽ����ʼ��Ϊ00
    bitset<5>	m_signal;		//��ʶ
    bitset<3>	m_sub_signal;	//�ӱ�ʶ
    bitset<3>	m_length;		//��Ϣ���ȣ���ʾ��ʼ�ֺ������չ�ֻ�����ֵ����������7��
    bitset<57>	m_message;	    //��Ϣ��
    bitset<5>	m_BIP;		    //��żУ�飬��һλ���У�����λִ��У��

public:
    InitialWord() : m_format(0b00) {
    }

    void clear();
    symbol* to_symbol();
    void handler_initial_word(string& bit_data);
    void show();
    string toString_70bit();
    void setBIP(bitset<5> BIP);
};