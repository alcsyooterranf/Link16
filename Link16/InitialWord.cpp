#include <iostream>
#include <bitset>
#include "InitialWord.h"
#include "tools.h"

//用比特字符串bit_str重写字中的所有主字段。要求字符串只能由0或1组成，且长度为75
void InitialWord::rewrite(string& bit_str) {
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
	m_sub_signal = bitset<3>(bit_str.substr(7, 10));
	m_length = bitset<3>(bit_str.substr(10, 13));
	m_message = bitset<57>(bit_str.substr(13, 70));
	m_BIP = bitset<5>(bit_str.substr(70, 5));
}

void InitialWord::clear() {
	m_format = 0b00;
	m_signal = 0;
	m_sub_signal = 0;
	m_length = 0;
	m_message = 0;
	m_BIP = 0;
	Word::clear();
}


void InitialWord::to_symbol() {
	string temp = { 0 };
	temp = m_format.to_string() + m_signal.to_string() + m_sub_signal.to_string()
		+ m_length.to_string() + m_message.to_string() + m_BIP.to_string();

	int flag = 0;
	for (int i = 0; i < 15; i++) {
		m_S_word[i] = symbol(temp.substr(flag, 5));
		flag += 5;
	}
}

void InitialWord::handler_word(string& bit_data) {
	size_t len = bit_data.length();
	bitset<57> message;
	if (len < 57) {
		message = bitset<57>(bit_data);
		bit_data.clear();
	}
	else {
		string temp = bit_data.substr(0, 57);
		bit_data.erase(0, 57);
		message = bitset<57>(temp);
	}

	//m_signal = bitset<5>();
	//m_sub_signal = bitset<3>();
	//STDP封装标准，初始字后只跟两个字，一个扩展字和一个继续字
	m_length = bitset<3>(0b010);
	m_message = message;
}

void InitialWord::show() {
	std::cout << "======" << "初始字已填充完成" << "======" << std::endl;
	std::cout << "initial_word:" << std::endl;
	std::cout << "\tformat\t\t=\t" << m_format << std::endl;
	std::cout << "\tsignal\t\t=\t" << m_signal << std::endl;
	std::cout << "\tsub_signal\t=\t" << m_sub_signal << std::endl;
	std::cout << "\tlength\t\t=\t" << m_length << std::endl;
	std::cout << "\tmessage\t\t=\t" << m_message << std::endl;
	std::cout << "\tBIP\t\t=\t" << m_BIP << std::endl;
}

string InitialWord::toString_70B() {
	return m_format.to_string() + m_signal.to_string() + m_sub_signal.to_string() + m_length.to_string()
		+ m_message.to_string();
}

string InitialWord::toString() {
	return m_format.to_string() + m_signal.to_string() + m_sub_signal.to_string()
		+ m_length.to_string() + m_message.to_string() + m_BIP.to_string();
}

bitset<5> InitialWord::getBIP() {
	return m_BIP;
}

void InitialWord::setBIP(bitset<5> BIP) {
	m_BIP = BIP;
}