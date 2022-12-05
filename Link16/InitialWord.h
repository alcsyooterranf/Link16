#pragma once
#include "Word.hpp"

//75bit��ʼ��
class InitialWord : public Word<RS_Length::code_31_15, RS_Length::data_31_15> {
private:
	bitset<2>	m_format;		//�ָ�ʽ����ʼ��Ϊ00
	bitset<5>	m_signal;		//��ʶ
	bitset<3>	m_sub_signal;	//�ӱ�ʶ
	bitset<3>	m_length;		//��Ϣ���ȣ���ʾ��ʼ�ֺ������չ�ֻ�����ֵ����������7��
	bitset<57>	m_message;	    //��Ϣ��
	bitset<5>	m_BIP;		    //��żУ�飬��һλ���У�����λִ��У��

public:
	InitialWord() : Word(), m_format(0b00) {}

	~InitialWord() {}

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