#pragma once
#include "Word.hpp"

//75bit��չ�֣����밴˳����
class ExtendWord : public Word<RS_Length::code_31_15, RS_Length::data_31_15> {
private:
	bitset<2>	m_format;	    //�ָ�ʽ����չ��Ϊ10
	bitset<68>	m_message;	    //��Ϣ�֣�ǰ����bit����Ϣ���ȣ�ȫ��Ϊ1��ʾ������Ϣ������
	bitset<5>	m_BIP;		    //��żУ�飬��һλ���У�����λִ��У��

public:
	ExtendWord() : Word(), m_format(0b10) {}

	~ExtendWord() {}

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