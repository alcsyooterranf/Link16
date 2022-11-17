#include <iostream>
#include "datatype.h"
#include <bitset>
#include "tools.h"
#include "Header35.h"

using namespace std;

symbol* Header35::to_symbol() {
    symbol* symbol_header = new symbol[7];
    memset(symbol_header, 0, sizeof(symbol) * 7);
    string temp = { 0 };
    temp = m_type.to_string() + m_PR.to_string() + m_STN.to_string()
        + m_SDU.to_string();

    int flag = 0;
    for (int i = 0; i < 7; i++) {
        symbol_header[i] = symbol(temp.substr(flag, 5));
        flag += 5;
    }
    //cout << "======" << "Jheader-×Ö·û×ª»»Íê±Ï" << "======" << endl;
    //int i = 0;
    //while (i != 7) {
    //    cout << "Jheader[" << i << "] = " << symbol_header[i].to_string() << endl;
    //    i++;
    //}
    return symbol_header;
}

string Header35::toString() {
    return m_type.to_string() + m_PR.to_string() + m_STN.to_string() + m_SDU.to_string();
}

string Header35::toString_15B() {
    return m_STN.to_string();
}

bitset<15> Header35::getSTN() {
    return m_STN;
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