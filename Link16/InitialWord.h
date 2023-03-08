#pragma once
#include "Word.hpp"

//75bit初始字
class InitialWord : public Word<RS_Length::code_31_15, RS_Length::data_31_15> {
private:
	bitset<2>	m_format;		//字格式：初始字为00
	bitset<5>	m_signal;		//标识，消息大类（Jn.m中的n标识）
	bitset<3>	m_sub_signal;	//子标识，消息子类（Jn.m中的m标识）
	bitset<3>	m_length;		//消息长度，表示初始字后面的扩展字或继续字的总数，最多7个
	bitset<57>	m_message;	    //信息字，前六个bit存消息长度（全部为1表示此字消息已满）
	bitset<5>	m_BIP;		    //奇偶校验，第一位空闲，后四位执行校验

public:
	InitialWord() : Word(), m_format(0b00) {}

	~InitialWord() {}

	void rewrite(string& bit_str);
	void clear();
	void to_symbol();
	void handler_word(string& bit_data, string& type);
	void show();
	string toString_70B();
	string toString();
	bitset<5> getBIP();
	void setBIP(bitset<5> BIP);
	void setSignal(bitset<5> signal);
	void setSubSignal(bitset<3> sub_signal);
	bitset<5> getSignal();
	bitset<3> getSubSignal();
	bitset<57> getMessage();
	string getData();
};