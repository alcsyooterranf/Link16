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
	m_format.reset();
	m_signal.reset();
	m_sub_signal.reset();
	m_length.reset();
	m_message.reset();
	m_BIP.reset();
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

void InitialWord::handler_word(string& bit_data, string& type) {
	size_t len = bit_data.length();
	vector<string> type_number = Tools::stringSplit(type, ' ');
	setSignal(bitset<5>(stoi(type_number[0])));
	setSubSignal(bitset<3>(stoi(type_number[1])));
	bitset<57> message;
	if (len < 51) {
		message = bitset<57>(bit_data);
		bitset<57> high = bitset<57>(len);
		high = high << 51;
		message = message | high;
		bit_data.clear();
	}
	else {
		string temp = bit_data.substr(0, 51);
		bit_data.erase(0, 51);
		message = bitset<57>(temp);
		bitset<57> high;
		high.set();
		high = high << 51;
		message = message | high;
	}

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

void InitialWord::setSignal(bitset<5> signal) {
	m_signal = signal;
}

void InitialWord::setSubSignal(bitset<3> sub_signal) {
	m_sub_signal = sub_signal;
}

bitset<5> InitialWord::getSignal() {
	return m_signal;
}

bitset<3> InitialWord::getSubSignal() {
	return m_sub_signal;
}

bitset<57> InitialWord::getMessage() {
	return m_message;
}

string InitialWord::getData() {
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
		return message.substr(57 - len);
	}
}