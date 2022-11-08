#include <iostream>
#include <string>
#include <bitset>
#include "dataType.h"
#include "tools.h"

using namespace std;

void handler_initial_word(string& bit_data, void (*send_msg)(const string& msg)) {
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
        len = 57;
    }

    initial_word iword = { 0 };
    iword.format = bitset<2>(0b00);
    //iword.signal = bitset<5>();
    //iword.sub_signal = bitset<3>();
    //iword.length = bitset<3>();
    iword.message = message;

    cout << "======" << "初始字已填充完成" << "======" << endl;
    cout << "initial_word:" << endl;
    cout << "\tformat\t\t=\t" << iword.format << endl;
    cout << "\tsignal\t\t=\t" << iword.signal << endl;
    cout << "\tsub_signal\t=\t" << iword.sub_signal << endl;
    cout << "\tlength\t\t=\t" << iword.length << endl;
    cout << "\tmessage\t\t=\t" << iword.message << endl;
    cout << "\tBIP\t\t=\t" << iword.BIP << endl;
    //奇偶校验(70bit -> 75bit)
    BIP();
    //5bit->1Symbol
    symbol* symbol_word = word_to_symbol(iword);
    cout << "======" << "initial_word-字符转换完毕" << "======" << endl;
    int i = 0;
    while(i != 15) {
        cout << "symbol_word[" << i << "] = " << symbol_word[i].to_string() << endl;
        i++;
    }
    cout<<"开始执行RS纠错编码"<<endl;
    i = 0;
    symbol* symbol_RS_word = RS15_31(symbol_word);
    while (i != 31) {
        cout << "symbol_RS_word[" << i << "] = " << symbol_RS_word[i].to_string() << endl;
        i++;
    }
    weave();
    send_msg("初始字");
    delete(symbol_word);
    symbol_word = nullptr;
    delete(symbol_RS_word);
    symbol_RS_word = nullptr;
}

void handler_extend_word(string& bit_data, void (*send_msg)(const string& msg)) {
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

    extend_word eword = { 0 };
    eword.format = bitset<2>(0b10);
    eword.message = message;

    cout << "======" << "扩展字已填充完成" << "======" << endl;
    cout << "extend_word:" << endl;
    cout << "\tformat\t\t=\t" << eword.format << endl;
    cout << "\tmessage\t\t=\t" << eword.message << endl;
    //奇偶校验(70bit -> 75bit)
    BIP();
    //5bit->1Symbol
    symbol* symbol_word = word_to_symbol(eword);
    cout << "======" << "extend_word-字符转换完毕" << "======" << endl;
    int i = 0;
    while (i != 15) {
        cout << "symbol_word[" << i << "] = " << symbol_word[i].to_string() << endl;
        i++;
    }
    cout << "开始执行RS纠错编码" << endl;
    i = 0;
    symbol* symbol_RS_word = RS15_31(symbol_word);
    while (i != 31) {
        cout << "symbol_RS_word[" << i << "] = " << symbol_RS_word[i].to_string() << endl;
        i++;
    }
    weave();
    send_msg("扩展字");
    delete(symbol_word);
    symbol_word = nullptr;
    delete(symbol_RS_word);
    symbol_RS_word = nullptr;
}

void handler_continue_word(string& bit_data, void (*send_msg)(const string& msg)) {
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

    continue_word cword = { 0 };
    cword.format = bitset<2>(0b01);
    //cword.signal = bitset<5>();
    cword.message = message;

    cout << "======" << "继续字已填充完成" << "======" << endl;
    cout << "initial_word:" << endl;
    cout << "\tformat\t\t=\t" << cword.format << endl;
    cout << "\tsignal\t\t=\t" << cword.signal << endl;
    cout << "\tmessage\t\t=\t" << cword.message << endl;
    cout << "\tBIP\t\t=\t\t" << cword.BIP << endl;
    //奇偶校验(70bit -> 75bit)
    BIP();
    //5bit->1Symbol
    symbol* symbol_word = word_to_symbol(cword);
    cout << "======" << "extend_word-字符转换完毕" << "======" << endl;
    int i = 0;
    while (i != 15) {
        cout << "symbol_word[" << i << "] = " << symbol_word[i].to_string() << endl;
        i++;
    }
    cout << "开始执行RS纠错编码" << endl;
    i = 0;
    symbol* symbol_RS_word = RS15_31(symbol_word);
    while (i != 31) {
        cout << "symbol_RS_word[" << i << "] = " << symbol_RS_word[i].to_string() << endl;
        i++;
    }
    weave();
    send_msg("继续字");
    delete(symbol_word);
    symbol_word = nullptr;
    delete(symbol_RS_word);
    symbol_RS_word = nullptr;
}

void handler_header(header_35 header, void (*send_msg)(const string& msg)) {
    BIP();
    //5bit->1Symbol
    symbol* symbol_header = header_to_symbol(header);
    cout << "======" << "Jheader-字符转换完毕" << "======" << endl;
    int i = 0;
    while (i != 15) {
        cout << "Jheader[" << i << "] = " << symbol_header[i].to_string() << endl;
        i++;
    }
    cout << "开始执行RS纠错编码" << endl;
    i = 0;
    symbol* symbol_RS_header = RS15_31(symbol_header);
    while (i != 31) {
        cout << "symbol_RS_header[" << i << "] = " << symbol_RS_header[i].to_string() << endl;
        i++;
    }
    weave();
    send_msg("报头字");
    delete(symbol_header);
    symbol_header = nullptr;
    delete(symbol_RS_header);
    symbol_RS_header = nullptr;
}