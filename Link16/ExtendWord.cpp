#include <iostream>
#include <bitset>
#include "ExtendWord.h"
#include "tools.h"

using namespace std;

//�ñ����ַ���bit_str��д���е��������ֶΡ�Ҫ���ַ���ֻ����0��1��ɣ��ҳ���Ϊ75
void ExtendWord::rewrite(string& bit_str) {
	if (bit_str.length() != 75) {
		cout << "[rewrite]: bit_str���ȷǷ�" << endl;
		return;
	}
	for (int i = 0; i < 75; i++) {
		if (bit_str[i] != '0' && bit_str[i] != '1') {
			cout << "[rewrite]: bit_str���ݷǷ�" << endl;
			return;
		}
	}
	m_format = bitset<2>(bit_str.substr(0, 2));
	m_message = bitset<68>(bit_str.substr(2, 70));
	m_BIP = bitset<5>(bit_str.substr(70, 5));
}

void ExtendWord::clear() {
	m_format = 0b00;
	m_message = 0;
	m_BIP = 0;
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
	if (len < 68) {
		message = bitset<68>(bit_data);
		bit_data.clear();
	}
	else {
		string temp = bit_data.substr(0, 68);
		bit_data.erase(0, 68);
		message = bitset<68>(temp);
	}
	m_message = message;
}

void ExtendWord::show() {
	cout << "======" << "��չ����������" << "======" << endl;
	cout << "extend_word:" << endl;
	cout << "\tformat\t\t=\t" << m_format << endl;
	cout << "\tmessage\t\t=\t" << m_message << endl;
	cout << "\tBIP\t\t=\t" << m_BIP << endl;
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