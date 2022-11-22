#include <iostream>
#include <bitset>
#include "tools.h"

using namespace std;

//15Symbol->31Symbol
//��RS������봦����Ϣ�֣�ʹ��schifra��
void ExtendWord::RS31_15() {
    symbol* symbol_word = this->getS_eword();
    for (int i = 0; i < 15; i++) {
        std::cout << "����ǰsymbol_word[" << i << "] = " << symbol_word[i].to_string() << endl;
    }

    string message(15, 0x00);
    for (int i = 0; i < 15; i++) {
        message[i] = static_cast<char>(symbol_word[i].to_ulong());
    }

    //cout << "ת�����symbol(�����Ʊ�ʾ): " << endl;
    //for (int i = 0; i < 15; i++) {
    //    for (int j = 7; j >= 0; j--) {
    //        cout << ((message[i] >> j) & 1);
    //    }
    //    cout << endl;
    //}

    symbol* symbol_RS_word = this->getRS_eword();
    memset(symbol_RS_word, 0, sizeof(symbol) * 31);
    memcpy(symbol_RS_word, symbol_word, sizeof(symbol) * 15);

    if (!RS(31, 15, message, symbol_RS_word)) {
        std::cout << "RS����ɹ�" << endl;
    }
    else {
        std::cout << "RS����ʧ��" << endl;
    }
    for (int i = 0; i < 31; i++) {
        std::cout << "�����symbol_RS_word[" << i << "] = " << symbol_RS_word[i].to_string() << endl;
    }
}

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
    memset(m_S_eword, 0, sizeof(symbol) * 15);
    memset(m_RS_eword, 0, sizeof(symbol) * 31);
}

void ExtendWord::to_symbol() {
    string temp = { 0 };
    temp = m_format.to_string() + m_message.to_string() + m_BIP.to_string();

    int flag = 0;
    for (int i = 0; i < 15; i++) {
        m_S_eword[i] = symbol(temp.substr(flag, 5));
        flag += 5;
    }
}

void ExtendWord::handler_extend_word(string& bit_data) {
    int len = bit_data.length();
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

string ExtendWord::toString_STDP() {
    string res;
    for (int i = 0; i < 31; i++) {
        res += m_RS_eword[i].to_string();
    }
    return res;
}

bitset<5> ExtendWord::getBIP() {
    return m_BIP;
}

void ExtendWord::setBIP(bitset<5> BIP) {
    m_BIP = BIP;
}

symbol* ExtendWord::getS_eword() {
    return m_S_eword;
}

symbol* ExtendWord::getRS_eword() {
    return m_RS_eword;
}