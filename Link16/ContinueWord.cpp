#include <iostream>
#include "datatype.h"
#include <bitset>
#include "tools.h"
#include "ContinueWord.h"

using namespace std;

void ContinueWord::clear() {
    m_format = 0b00;
    m_signal = 0;
    m_message = 0;
    m_BIP = 0;
}

symbol* ContinueWord::to_symbol() {
    symbol* symbol_words = new symbol[15];
    string temp = { 0 };
    temp = m_format.to_string() + m_signal.to_string() + m_message.to_string()
        + m_BIP.to_string();

    int flag = 0;
    for (int i = 0; i < 15; i++) {
        symbol_words[i] = symbol(temp.substr(flag, 5));
        flag += 5;
    }
    return symbol_words;
}

void ContinueWord::handler_continue_word(string& bit_data) {
    int len = bit_data.length();
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

string ContinueWord::toString_70bit() {
    return m_format.to_string() + m_signal.to_string() + m_message.to_string();
}

string ContinueWord::toString() {
    return m_format.to_string() + m_signal.to_string() + m_message.to_string() + m_BIP.to_string();
}

void ContinueWord::setBIP(bitset<5> BIP) {
    m_BIP = BIP;
}