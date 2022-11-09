#include <iostream>
#include "datatype.h"
#include <bitset>
#include "tools.h"
#include "Header35.h"

using namespace std;

symbol* Header35::to_symbol() {
    symbol* symbol_header = new symbol[7];
    string temp = { 0 };
    temp = m_type.to_string() + m_PR.to_string() + m_STN.to_string()
        + m_SDU.to_string();

    for (int i = 0; i < 7; i++) {
        int flag = 0;
        symbol_header[i] = symbol(temp.substr(flag, 5));
        flag += 5;
    }
    cout << "======" << "Jheader-×Ö·û×ª»»Íê±Ï" << "======" << endl;
    int i = 0;
    while (i != 15) {
        cout << "Jheader[" << i << "] = " << symbol_header[i].to_string() << endl;
        i++;
    }
    return symbol_header;
}

string Header35::toString() {
    return m_type.to_string() + m_PR.to_string() + m_STN.to_string() + m_SDU.to_string();
}