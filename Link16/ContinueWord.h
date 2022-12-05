#pragma once
#include "Word.hpp"

//75bit继续字，可以不按顺序发送
class ContinueWord : public Word<RS_Length::code_31_15, RS_Length::data_31_15> {
private:
	bitset<2>	m_format;		//字格式：继续字为01
	bitset<5>	m_signal;		//继续字标识，每条J系列消息最多允许定义32个继续字
	bitset<63>	m_message;	    //信息字
	bitset<5>	m_BIP;		    //奇偶校验，第一位空闲，后四位执行校验

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