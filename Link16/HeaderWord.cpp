#include <iostream>
#include <bitset>
#include "HeaderWord.h"
#include "tools.h"

//用比特字符串bit_str重写报头中的所有主字段。要求字符串只能由0或1组成，且长度为35
void HeaderWord::rewrite(string& bit_str) {
	if (bit_str.length() != 35) {
		std::cout << "[rewrite]: bit_str长度非法" << std::endl;
		return;
	}
	for (int i = 0; i < 35; i++) {
		if (bit_str[i] != '0' && bit_str[i] != '1') {
			std::cout << "[rewrite]: bit_str内容非法" << std::endl;
			return;
		}
	}
	m_type = bitset<3>(bit_str.substr(0, 3));
	m_PR = bitset<1>(bit_str.substr(3, 1));
	m_STN = bitset<15>(bit_str.substr(4, 15));
	m_SDU = bitset<16>(bit_str.substr(19, 16));
}

void HeaderWord::to_symbol() {
	string temp = { 0 };
	temp = m_type.to_string() + m_PR.to_string() + m_STN.to_string()
		+ m_SDU.to_string();
	int flag = 0;
	for (int i = 0; i < 7; i++) {
		m_S_word[i] = symbol(temp.substr(flag, 5));
		flag += 5;
	}
}

void HeaderWord::show() {
	std::cout << "======" << "消息头已生成" << "======" << std::endl;
	std::cout << "JHeader:" << std::endl;
	std::cout << "\ttype\t\t=\t" << m_type << std::endl;
	std::cout << "\tPR\t\t=\t" << m_PR << std::endl;
	std::cout << "\tSTN\t\t=\t" << m_STN << std::endl;
	std::cout << "\tSDU\t\t=\t" << m_SDU << std::endl;
}

string HeaderWord::toString() {
	return m_type.to_string() + m_PR.to_string() + m_STN.to_string() + m_SDU.to_string();
}

string HeaderWord::toString_15B() {
	return m_STN.to_string();
}

bitset<15> HeaderWord::getSTN() {
	return m_STN;
}

bitset<16> HeaderWord::getSDU() {
	return m_SDU;
}

void HeaderWord::setType(bitset<3> type) {
	m_type = type;
}

void HeaderWord::setPR(bitset<1> PR) {
	m_PR = PR;
}

void HeaderWord::setSTN(bitset<15> STN) {
	m_STN = STN;
}

void HeaderWord::setSDU(bitset<16> SDU) {
	m_SDU = SDU;
}