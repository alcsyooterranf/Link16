#include <iostream>
#include <bitset>
#include "tools.h"
#include "Header35.h"

using namespace std;

//7Symbol->16Symbol
//用RS纠错编码处理消息头，使用schifra库
void Header35::RS16_7() {
    symbol* symbol_header = this->getS_Header();
    for (int i = 0; i < 7; i++) {
        std::cout << "编码前symbol_header[" << i << "] = " << symbol_header[i].to_string() << endl;
    }

    string message(15, 0x00);
    for (int i = 0; i < 7; i++) {
        message[i] = static_cast<char>(symbol_header[i].to_ulong());
    }

    symbol* symbol_RS_header = this->getRS_Header();
    memset(symbol_RS_header, 0, sizeof(symbol) * 16);
    memcpy(symbol_RS_header, symbol_header, sizeof(symbol) * 7);

    if (!RS(16, 7, message, symbol_RS_header)) {
        std::cout << "RS编码成功" << endl;
    }
    else {
        std::cout << "RS编码失败" << endl;
    }

    //将symbol_RS_header_temp中的fec放入
    for (int i = 0; i < 16; i++) {
        std::cout << "编码后symbol_RS_header[" << i << "] = " << symbol_RS_header[i].to_string() << endl;
    }
}

//用比特字符串bit_str重写报头中的所有主字段。要求字符串只能由0或1组成，且长度为35
void Header35::rewrite(string& bit_str){
    if (bit_str.length() != 35) {
        cout << "[rewrite]: bit_str长度非法" << endl;
        return;
    }
    for (int i = 0; i < 35; i++) {
        if (bit_str[i] != '0' && bit_str[i] != '1') {
            cout << "[rewrite]: bit_str内容非法" << endl;
            return;
        }
    }
    m_type = bitset<3>(bit_str.substr(0, 3));
    m_PR = bitset<1>(bit_str.substr(3, 1));
    m_STN = bitset<15>(bit_str.substr(4, 15));
    m_SDU = bitset<16>(bit_str.substr(19, 16));
}

void Header35::to_symbol() {
    string temp = { 0 };
    temp = m_type.to_string() + m_PR.to_string() + m_STN.to_string()
        + m_SDU.to_string();

    int flag = 0;
    for (int i = 0; i < 7; i++) {
        m_S_Header[i] = symbol(temp.substr(flag, 5));
        flag += 5;
    }
}

void Header35::show() {
    cout << "======" << "消息头已生成" << "======" << endl;
    cout << "JHeader:" << endl;
    cout << "\ttype\t\t=\t" << m_type << endl;
    cout << "\tPR\t\t=\t" << m_PR << endl;
    cout << "\tSTN\t\t=\t" << m_STN << endl;
    cout << "\tSDU\t\t=\t" << m_SDU << endl;
}

string Header35::toString() {
    return m_type.to_string() + m_PR.to_string() + m_STN.to_string() + m_SDU.to_string();
}

string Header35::toString_15B() {
    return m_STN.to_string();
}

string Header35::toString_STDP() {
    string res;
    for (int i = 0; i < 16; i++) {
        res += m_RS_Header[i].to_string();
    }
    return res;
}

bitset<15> Header35::getSTN() {
    return m_STN;
}

bitset<16> Header35::getSDU() {
    return m_SDU;
}

void Header35::setType(bitset<3> type) {
    m_type = type;
}

void Header35::setPR(bitset<1> PR) {
    m_PR = PR;
}

void Header35::setSTN(bitset<15> STN) {
    m_STN = STN;
}

void Header35::setSDU(bitset<16> SDU) {
    m_SDU = SDU;
}

symbol* Header35::getS_Header() {
    return m_S_Header;
}

symbol* Header35::getRS_Header() {
    return m_RS_Header;
}