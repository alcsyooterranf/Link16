#include <iostream>
#include <string>
#include <bitset>
#include "dataType.h"
#include "tools.h"
#include "InitialWord.h"
#include "ExtendWord.h"
#include "ContinueWord.h"
#include "Header35.h"

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

void BIP(Header35& header35, InitialWord& iword, 
    ExtendWord& eword, ContinueWord& cword) {
    cout << "执行奇偶校验......" << endl;
    iword.setBIP(bitset<5>("01001"));
}

void weave(symbol* symbol_RS_header, symbol* symbol_RS_iword,
    symbol* symbol_RS_eword, symbol* symbol_RS_cword) {
    cout << "执行字符交织......" << endl;
}

//15Symbol->31Symbol
//用RS纠错编码处理消息字，默认在消息字后填充长度为16Symlbol的0数据单元
symbol* RS15_31(symbol* symbol_word) {
    cout << "======" << "开始执行RS纠错编码" << "======" << endl;
    int i = 0;
    symbol* symbol_RS_word = new symbol[31]();
    memset(symbol_RS_word, 0, sizeof(symbol) * 31);
    memcpy(symbol_RS_word, symbol_word, sizeof(symbol) * 15);
    while (i != 31) {
        cout << "symbol_RS_word[" << i << "] = " << symbol_RS_word[i].to_string() << endl;
        i++;
    }
    return symbol_RS_word;
}

//7Symbol->16Symbol
//用RS纠错编码处理消息头，默认在消息字后填充长度为9Symlbol的0数据单元
symbol* RS7_16(symbol* symbol_header) {
    cout << "======" << "开始执行RS纠错编码" << "======" << endl;
    int i = 0;
    symbol* symbol_RS_header = new symbol[16]();
    memset(symbol_RS_header, 0, sizeof(symbol) * 16);
    memcpy(symbol_RS_header, symbol_header, sizeof(symbol) * 7);
    while (i != 16) {
        cout << "symbol_RS_header[" << i << "] = " << symbol_RS_header[i].to_string() << endl;
        i++;
    }
    return symbol_RS_header;
}

void handlerSTDP(Header35& Jheader, InitialWord& iword,
    ExtendWord& eword, ContinueWord& cword) {
    //执行奇偶校验，70bit -> 75bit
    BIP(Jheader, iword, eword, cword);
    //TODO
    //消息加密

    //Symbol转换，然后进行RS编码
    symbol* symbol_header = Jheader.to_symbol();
    symbol* symbol_RS_header = RS7_16(symbol_header);

    symbol* symbol_iword = iword.to_symbol();
    symbol* symbol_RS_iword = RS15_31(symbol_iword);

    symbol* symbol_eword = eword.to_symbol();
    symbol* symbol_RS_eword = RS15_31(symbol_eword);

    symbol* symbol_cword = cword.to_symbol();
    symbol* symbol_RS_cword = RS15_31(symbol_cword);

    //交织
    weave(symbol_RS_header, symbol_RS_iword, symbol_RS_eword, symbol_RS_cword);

    //TODO
    //添加时间精同步符号和时间粗同步符号

    //TODO
    //循环码移键控（CCSK）

    //TODO
    //码字加密

    //发送
    send_msg("一个STDP消息");
    cout << "======发送的STDP消息内容如下：======\n"
        << Jheader.toString()
        << iword.toString()
        << eword.toString()
        << cword.toString() << endl;

    delete(symbol_header);
    symbol_header = nullptr;
    delete(symbol_RS_header);
    symbol_RS_header = nullptr;

    delete(symbol_iword);
    symbol_iword = nullptr;
    delete(symbol_RS_iword);
    symbol_RS_iword = nullptr;

    delete(symbol_eword);
    symbol_eword = nullptr;
    delete(symbol_RS_eword);
    symbol_RS_eword = nullptr;

    delete(symbol_cword);
    symbol_cword = nullptr;
    delete(symbol_RS_cword);
    symbol_RS_cword = nullptr;
}