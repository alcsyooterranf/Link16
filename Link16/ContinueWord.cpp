#include <iostream>
#include <bitset>
#include "ContinueWord.h"
#include "tools.h"

//用比特字符串bit_str重写字中的所有主字段。要求字符串只能由0或1组成，且长度为75
void ContinueWord::rewrite(string& bit_str) {
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
	m_signal = bitset<5>(bit_str.substr(2, 7));
	m_message = bitset<63>(bit_str.substr(7, 70));
	m_BIP = bitset<5>(bit_str.substr(70, 5));
}

void ContinueWord::clear() {
	m_format.reset();
	m_signal.reset();
	m_message.reset();
	m_BIP.reset();
	Word::clear();
}

void ContinueWord::to_symbol() {
	string temp = { 0 };
	temp = m_format.to_string() + m_signal.to_string() + m_message.to_string()
		+ m_BIP.to_string();

	int flag = 0;
	for (int i = 0; i < 15; i++) {
		m_S_word[i] = symbol(temp.substr(flag, 5));
		flag += 5;
	}
}

void ContinueWord::handler_word(string& bit_data) {
	size_t len = bit_data.length();
	bitset<63> message;
	if (len < 57) {
		message = bitset<63>(bit_data);
		bitset<63> high = bitset<63>(len);
		high = high << 57;
		message = message | high;
		bit_data.clear();
	}
	else {
		string temp = bit_data.substr(0, 57);
		bit_data.erase(0, 57);
		message = bitset<63>(temp);
		bitset<63> high;
		high.set();
		high = high << 57;
		message = message | high;
	}
	m_message = message;
}

void ContinueWord::show() {
	std::cout << "======" << "继续字已填充完成" << "======" << std::endl;
	std::cout << "continue_word:" << std::endl;
	std::cout << "\tformat\t\t=\t" << m_format << std::endl;
	std::cout << "\tsignal\t\t=\t" << m_signal << std::endl;
	std::cout << "\tmessage\t\t=\t" << m_message << std::endl;
	std::cout << "\tBIP\t\t=\t" << m_BIP << std::endl;
}

string ContinueWord::toString_70B() {
	return m_format.to_string() + m_signal.to_string() + m_message.to_string();
}

string ContinueWord::toString() {
	return m_format.to_string() + m_signal.to_string() + m_message.to_string() + m_BIP.to_string();
}

bitset<5> ContinueWord::getBIP() {
	return m_BIP;
}

void ContinueWord::setBIP(bitset<5> BIP) {
	m_BIP = BIP;
}

bitset<63> ContinueWord::getMessage() {
	return m_message;
}

string ContinueWord::getData() {
	string message = getMessage().to_string();
	bitset<6> high = bitset<6>(message.substr(0, 6));
	if (high.all()) {
		return message.substr(6);
	}
	else if (high.none()) {
		return "";
	}
	else {
		int len = static_cast<int>(high.to_ulong());
		return message.substr(63 - len);
	}
}