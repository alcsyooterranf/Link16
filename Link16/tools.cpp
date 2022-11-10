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
    cout << msg << "�ѷ��ͳɹ�" << endl;
}

//��α���������15bit��STN
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
        //�����Ʒ�ת
        for (int j = 0; j < 4; j++)
        {
            tmp[0] = bits[j];
            bits[j] = bits[7 - j];
            bits[7 - j] = tmp[0];
        }
        res += bits.to_string();
    }

    //���һ����ת����
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
    //���һ����ת����
    reverse(begin(res), end(res));
    return res;
}

void BIP(Header35& header35, InitialWord& iword, 
    ExtendWord& eword, ContinueWord& cword) {
    cout << "ִ����żУ��......" << endl;
    iword.setBIP(bitset<5>("01001"));
}

void weave(symbol* symbol_RS_header, symbol* symbol_RS_iword,
    symbol* symbol_RS_eword, symbol* symbol_RS_cword) {
    cout << "ִ���ַ���֯......" << endl;
}

//15Symbol->31Symbol
//��RS������봦����Ϣ�֣�Ĭ������Ϣ�ֺ���䳤��Ϊ16Symlbol��0���ݵ�Ԫ
symbol* RS15_31(symbol* symbol_word) {
    cout << "======" << "��ʼִ��RS�������" << "======" << endl;
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
//��RS������봦����Ϣͷ��Ĭ������Ϣ�ֺ���䳤��Ϊ9Symlbol��0���ݵ�Ԫ
symbol* RS7_16(symbol* symbol_header) {
    cout << "======" << "��ʼִ��RS�������" << "======" << endl;
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
    //ִ����żУ�飬70bit -> 75bit
    BIP(Jheader, iword, eword, cword);
    //TODO
    //��Ϣ����

    //Symbolת����Ȼ�����RS����
    symbol* symbol_header = Jheader.to_symbol();
    symbol* symbol_RS_header = RS7_16(symbol_header);

    symbol* symbol_iword = iword.to_symbol();
    symbol* symbol_RS_iword = RS15_31(symbol_iword);

    symbol* symbol_eword = eword.to_symbol();
    symbol* symbol_RS_eword = RS15_31(symbol_eword);

    symbol* symbol_cword = cword.to_symbol();
    symbol* symbol_RS_cword = RS15_31(symbol_cword);

    //��֯
    weave(symbol_RS_header, symbol_RS_iword, symbol_RS_eword, symbol_RS_cword);

    //TODO
    //���ʱ�侫ͬ�����ź�ʱ���ͬ������

    //TODO
    //ѭ�����Ƽ��أ�CCSK��

    //TODO
    //���ּ���

    //����
    send_msg("һ��STDP��Ϣ");
    cout << "======���͵�STDP��Ϣ�������£�======\n"
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