#include <iostream>
#include <bitset>
#include "tools.h"

using namespace std;

//15Symbol->31Symbol
//用RS纠错编码处理消息字，使用schifra库
void InitialWord::RS31_15() {
    symbol* symbol_word = this->getS_iword();
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

    symbol* symbol_RS_word = this->getRS_iword();
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
void InitialWord::rewrite(string& bit_str) {
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
    memset(m_S_iword, 0, sizeof(symbol) * 15);
    memset(m_RS_iword, 0, sizeof(symbol) * 31);
}


void InitialWord::to_symbol() {
    string temp = { 0 };
    temp = m_format.to_string() + m_signal.to_string() + m_sub_signal.to_string()
        + m_length.to_string() + m_message.to_string() + m_BIP.to_string();

    int flag = 0;
    for (int i = 0; i < 15; i++) {
        m_S_iword[i] = symbol(temp.substr(flag, 5));
        flag += 5;
    }
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

string InitialWord::toString_STDP() {
    string res;
    for (int i = 0; i < 31; i++) {
        res += m_RS_iword[i].to_string();
    }
    return res;
}

bitset<5> InitialWord::getBIP() {
    return m_BIP;
}

void InitialWord::setBIP(bitset<5> BIP) {
    m_BIP = BIP;
}

symbol* InitialWord::getS_iword() {
    return m_S_iword;
}

symbol* InitialWord::getRS_iword() {
    return m_RS_iword;
}