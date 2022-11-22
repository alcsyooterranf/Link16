#pragma once
#include <bitset>
#include "dataType.h"

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

    symbol*     m_S_iword;      //symbolת�����InitialWord
    symbol*     m_RS_iword;     //RS������InitialWord

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