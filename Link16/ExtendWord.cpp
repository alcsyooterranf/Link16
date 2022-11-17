#include <iostream>
#include "datatype.h"
#include <bitset>
#include "tools.h"
#include "ExtendWord.h"

using namespace std;

void ExtendWord::clear() {
    m_format = 0b00;
    m_message = 0;
    m_BIP = 0;
}

symbol* ExtendWord::to_symbol() {
    symbol* symbol_words = new symbol[15];
    memset(symbol_words, 0, sizeof(symbol) * 15);
    string temp = { 0 };
    temp = m_format.to_string() + m_message.to_string() + m_BIP.to_string();

    int flag = 0;
    for (int i = 0; i < 15; i++) {
        symbol_words[i] = symbol(temp.substr(flag, 5));
        flag += 5;
    }
    return symbol_words;
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

bitset<5> ExtendWord::getBIP() {
    return m_BIP;
}

void ExtendWord::setBIP(bitset<5> BIP) {
    m_BIP = BIP;
}