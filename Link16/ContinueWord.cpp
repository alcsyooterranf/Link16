#include <iostream>
#include <bitset>
#include "ContinueWord.h"
#include "tools.h"

using namespace std;

//用比特字符串bit_str重写字中的所有主字段。要求字符串只能由0或1组成，且长度为75
void ContinueWord::rewrite(string& bit_str) {
	if (bit_str.length() != 75) {
		cout << "[rewrite]: bit_str长度非法" << endl;
		return;
	}
	for (int i = 0; i < 75; i++) {
		if (bit_str[i] != '0' && bit_str[i] != '1') {
			cout << "[rewrite]: bit_str内容非法" << endl;
			return;
		}
	}
	m_format = bitset<2>(bit_str.substr(0, 2));
	m_signal = bitset<5>(bit_str.substr(2, 7));
	m_message = bitset<63>(bit_str.substr(7, 70));
	m_BIP = bitset<5>(bit_str.substr(70, 5));
}

void ContinueWord::clear() {
	m_format = 0b00;
	m_signal = 0;
	m_message = 0;
	m_BIP = 0;
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
	if (len < 63) {
		message = bitset<63>(bit_data);
		bit_data.clear();
	}
	else {
		string temp = bit_data.substr(0, 63);
		bit_data.erase(0, 63);
		message = bitset<63>(temp);
	}
	m_message = message;
}

void ContinueWord::show() {
	cout << "======" << "继续字已填充完成" << "======" << endl;
	cout << "initial_word:" << endl;
	cout << "\tformat\t\t=\t" << m_format << endl;
	cout << "\tsignal\t\t=\t" << m_signal << endl;
	cout << "\tmessage\t\t=\t" << m_message << endl;
	cout << "\tBIP\t\t=\t" << m_BIP << endl;
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