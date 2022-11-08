#include <iostream>
#include <string>
#include <bitset>
#include "dataType.h"

using namespace std;

void send_msg(const string& msg) {
    cout << msg << "已发送成功" << endl;
}

//用伪随机数生成15bit的STN
bitset<15> generateSTN() {
    srand(time(0));
    string res;
    for (int i = 0; i < 15; i++) {
        res += to_string(rand() % 2);
    }
    bitset<15> STN = bitset<15>(res);
    return STN;
}

string StrToBitStr(const string& str) {
    int len = str.length();
    string res;

    for (int i = 0; i < len; i++) {
        bitset<8> bits = bitset<8>(str[i]);
        bitset<1> tmp;
        //二进制翻转
        for (int j = 0; j < 4; j++)
        {
            tmp[0] = bits[j];
            bits[j] = bits[7 - j];
            bits[7 - j] = tmp[0];
        }
        res += bits.to_string();
    }

    //添加一个翻转操作
    reverse(begin(res), end(res));
    return res;
}

string BitStrTostr(const string& str) {
    int len = str.length();
    string res;
    for (int i = 0; i < len; i = i + 8) {
        string tmp;
        for (int j = 0; j < 8; j++) {
            tmp += str[i + j];
        }
        bitset<8> ch = bitset<8>(tmp);
        res += (char)ch.to_ulong();
    }
    //添加一个翻转操作
    reverse(begin(res), end(res));
    return res;
}

void BIP() {
    cout << "执行奇偶校验......" << endl;
}

void weave() {
    cout << "执行字符交织......" << endl;
}

//生成J系列消息的35bit报头
header_35 generate_J_header(bitset<15> STN) {
    header_35 Jheader = { 0 };
    Jheader.type = bitset<3>("001");
    Jheader.PR = bitset<1>(0);
    Jheader.STN = STN;
    Jheader.SDU = bitset<16>("0000100010001001");    //一种加密方式
    return Jheader;
}

symbol* word_to_symbol(initial_word bit_word) {
    symbol* symbol_words = new symbol[15];
    string temp = { 0 };
    temp = bit_word.format.to_string() + bit_word.signal.to_string() + bit_word.sub_signal.to_string()
        + bit_word.length.to_string() + bit_word.message.to_string() + bit_word.BIP.to_string();

    int flag = 0;
    for (int i = 0; i < 15; i++) {
        symbol_words[i] = symbol(temp.substr(flag, 5));
        flag += 5;
    }
    return symbol_words;
}

symbol* word_to_symbol(extend_word bit_word) {
    symbol* symbol_words = new symbol[15];
    string temp = { 0 };
    temp = bit_word.format.to_string() + bit_word.message.to_string() + bit_word.BIP.to_string();

    int flag = 0;
    for (int i = 0; i < 15; i++) {
        symbol_words[i] = symbol(temp.substr(flag, 5));
        flag += 5;
    }
    return symbol_words;
}

symbol* word_to_symbol(continue_word bit_word) {
    symbol* symbol_words = new symbol[15];
    string temp = { 0 };
    temp = bit_word.format.to_string() + bit_word.signal.to_string() + bit_word.message.to_string() 
        + bit_word.BIP.to_string();

    int flag = 0;
    for (int i = 0; i < 15; i++) {
        symbol_words[i] = symbol(temp.substr(flag, 5));
        flag += 5;
    }
    return symbol_words;
}

symbol* header_to_symbol(header_35 bit_word) {
    symbol* symbol_header = new symbol[7];
    string temp = { 0 };
    temp = bit_word.type.to_string() + bit_word.PR.to_string() + bit_word.STN.to_string()
        + bit_word.SDU.to_string();

    for (int i = 0; i < 7; i++) {
        int flag = 0;
        symbol_header[i] = symbol(temp.substr(flag, 5));
        flag += 5;
    }
    return symbol_header;
}

//15Symbol->31Symbol
//用RS纠错编码处理消息字，默认在消息字后填充长度为16Symlbol的0数据单元
symbol* RS15_31(symbol* symbol_word) {
    symbol* symbol_RS_word = new symbol[31]();
    memcpy(symbol_RS_word, symbol_word, sizeof(symbol) * 15);
    return symbol_RS_word;
}

//7Symbol->16Symbol
//用RS纠错编码处理消息头，默认在消息字后填充长度为9Symlbol的0数据单元
symbol* RS7_16(symbol* symbol_header) {
    symbol* symbol_RS_header = new symbol[16]();
    memcpy(symbol_RS_header, symbol_header, sizeof(symbol) * 7);
    return symbol_RS_header;
}