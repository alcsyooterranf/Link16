#pragma once
#include "Word.hpp"

//75bit初始字
class InitialWord : public Word<RS_Length::code_31_15, RS_Length::data_31_15> {
private:
	bitset<2>	m_format;		//字格式：初始字为00
	bitset<5>	m_signal;		//标识
	bitset<3>	m_sub_signal;	//子标识
	bitset<3>	m_length;		//消息长度，表示初始字后面的扩展字或继续字的总数，最多7个
	bitset<57>	m_message;	    //信息字
	bitset<5>	m_BIP;		    //奇偶校验，第一位空闲，后四位执行校验

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