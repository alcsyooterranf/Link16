#include <iostream>
#include <bitset>
#include "tools.h"

using namespace std;

//15Symbol->31Symbol
//用RS纠错编码处理消息字，使用schifra库
void ExtendWord::RS31_15() {
    symbol* symbol_word = this->getS_eword();
    for (int i = 0; i < 15; i++) {
        std::cout << "编码前symbol_word[" << i << "] = " << symbol_word[i].to_string() << endl;
    }

    string message(15, 0x00);
    for (int i = 0; i < 15; i++) {
        message[i] = static_cast<char>(symbol_word[i].to_ulong());
    }

    //cout << "转换后的symbol(二进制表示): " << endl;
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
        std::cout << "RS编码成功" << endl;
    }
    else {
        std::cout << "RS编码失败" << endl;
    }
    for (int i = 0; i < 31; i++) {
        std::cout << "编码后symbol_RS_word[" << i << "] = " << symbol_RS_word[i].to_string() << endl;
    }
}

//用比特字符串bit_str重写字中的所有主字段。要求字符串只能由0或1组成，且长度为75
void ExtendWord::rewrite(string& bit_str) {
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
    cout << "======" << "扩展字已填充完成" << "======" << endl;
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