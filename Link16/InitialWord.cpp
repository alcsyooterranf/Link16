#include <iostream>
#include <bitset>
#include "tools.h"

using namespace std;

//15Symbol->31Symbol
//��RS������봦����Ϣ�֣�ʹ��schifra��
void InitialWord::RS31_15() {
    symbol* symbol_word = this->getS_iword();
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

    symbol* symbol_RS_word = this->getRS_iword();
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
void InitialWord::rewrite(string& bit_str) {
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
    //STDP��װ��׼����ʼ�ֺ�ֻ�������֣�һ����չ�ֺ�һ��������
    m_length = bitset<3>(0b010);
    m_message = message;
}

void InitialWord::show() {
    cout << "======" << "��ʼ����������" << "======" << endl;
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