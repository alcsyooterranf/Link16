#pragma once
#include "Word.hpp"

//75bit扩展字，必须按顺序发送
class ExtendWord : public Word<RS_Length::code_31_15, RS_Length::data_31_15> {
private:
	bitset<2>	m_format;	    //字格式：扩展字为10
	bitset<68>	m_message;	    //信息字，前六个bit存消息长度（全部为1表示此字消息已满）
	bitset<5>	m_BIP;		    //奇偶校验，第一位空闲，后四位执行校验

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