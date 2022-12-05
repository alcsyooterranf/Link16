#pragma once
#include "Word.hpp"

//75bit�����֣����Բ���˳����
class ContinueWord : public Word<RS_Length::code_31_15, RS_Length::data_31_15> {
private:
	bitset<2>	m_format;		//�ָ�ʽ��������Ϊ01
	bitset<5>	m_signal;		//�����ֱ�ʶ��ÿ��Jϵ����Ϣ���������32��������
	bitset<63>	m_message;	    //��Ϣ��
	bitset<5>	m_BIP;		    //��żУ�飬��һλ���У�����λִ��У��

public:
	ContinueWord() : Word(), m_format(0b01) {}

	~ContinueWord() {}

	void rewrite(string& bit_str);
	void clear();
	void to_symbol();
	void handler_word(string& bit_data);
	void show();
	string toString_70B();
	string toString();
	bitset<5> getBIP();
	void setBIP(bitset<5> BIP);
};