#include <iostream>
#include <bitset>
#include "ExtendWord.h"
#include "tools.h"

//用比特字符串bit_str重写字中的所有主字段。要求字符串只能由0或1组成，且长度为75
void ExtendWord::rewrite(string& bit_str) {
	if (bit_str.length() != 75) {
		std::cout << "[rewrite]: bit_str长度非法" << std::endl;
		return;
	}
	for (int i = 0; i < 75; i++) {
		if (bit_str[i] != '0' && bit_str[i] != '1') {
			std::cout << "[rewrite]: bit_str内容非法" << std::endl;
			return;
		}
	}
	m_format = bitset<2>(bit_str.substr(0, 2));
	m_message = bitset<68>(bit_str.substr(2, 70));
	m_BIP = bitset<5>(bit_str.substr(70, 5));
}

void ExtendWord::clear() {
	m_format.reset();
	m_message.reset();
	m_BIP.reset();
	Word::clear();
}

void ExtendWord::to_symbol() {
	string temp = { 0 };
	temp = m_format.to_string() + m_message.to_string() + m_BIP.to_string();

	int flag = 0;
	for (int i = 0; i < 15; i++) {
		m_S_word[i] = symbol(temp.substr(flag, 5));
		flag += 5;
	}
}

void ExtendWord::handler_word(string& bit_data) {
	size_t len = bit_data.length();
	bitset<68> message;
	if (len < 62) {
		message = bitset<68>(bit_data);
		bitset<68> high = bitset<68>(len);
		high = high << 62;
		message = message | high;
		bit_data.clear();
	}
	else {
		string temp = bit_data.substr(0, 62);
		bit_data.erase(0, 62);
		message = bitset<68>(temp);
		bitset<68> high;
		high.set();
		high = high << 62;
		message = message | high;
	}
	m_message = message;
}

void ExtendWord::show() {
	std::cout << "======" << "扩展字已填充完成" << "======" << std::endl;
	std::cout << "extend_word:" << std::endl;
	std::cout << "\tformat\t\t=\t" << m_format << std::endl;
	std::cout << "\tmessage\t\t=\t" << m_message << std::endl;
	std::cout << "\tBIP\t\t=\t" << m_BIP << std::endl;
}

string ExtendWord::toString_70B() {
	return m_format.to_string() + m_message.to_string();
}

string ExtendWord::toString() {
	return m_format.to_string() + m_message.to_string() + m_BIP.to_string();
}

bitset<5> ExtendWord::getBIP() {
	return m_BIP;
}

void ExtendWord::setBIP(bitset<5> BIP) {
	m_BIP = BIP;
}