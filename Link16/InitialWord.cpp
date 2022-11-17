#include <iostream>
#include "datatype.h"
#include <bitset>
#include "tools.h"
#include "InitialWord.h"

using namespace std;

void InitialWord::clear() {
    m_format = 0b00;
    m_signal = 0;
    m_sub_signal = 0;
    m_length = 0;
    m_message = 0;
    m_BIP = 0;
}

symbol* InitialWord::to_symbol() {
    symbol* symbol_words = new symbol[15];
    memset(symbol_words, 0, sizeof(symbol) * 15);
    string temp = { 0 };
    temp = m_format.to_string() + m_signal.to_string() + m_sub_signal.to_string()
        + m_length.to_string() + m_message.to_string() + m_BIP.to_string();

    int flag = 0;
    for (int i = 0; i < 15; i++) {
        symbol_words[i] = symbol(temp.substr(flag, 5));
        flag += 5;
    }
    return symbol_words;
}

void InitialWord::handler_initial_word(string& bit_data) {
    int len = bit_data.length();
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
    cout << "======" << "初始字已填充完成" << "======" << endl;
    cout << "initial_word:" << endl;
    cout << "\tformat\t\t=\t" << m_format << endl;
    cout << "\tsignal\t\t=\t" << m_signal << endl;
    cout << "\tsub_signal\t=\t" << m_sub_signal << endl;
    cout << "\tlength\t\t=\t" << m_length << endl;
    cout << "\tmessage\t\t=\t" << m_message << endl;
    cout << "\tBIP\t\t=\t" << m_BIP << endl;
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