#include <iostream>
#include <bitset>
#include <string>
#include <algorithm>
#include "tools.h"
#include "decodeTools.h"

using namespace std;

#define TRANSMIT
#ifdef TRANSMIT
int main()
{
    //数据准备
    string message = "Hello, everyone! My name is Cai Siyuan, I come from China.";

    string bit_data = StrToBitStr(message);
    string raw_data = BitStrTostr(bit_data);
    cout << "bit_data = " << bit_data << endl;
    cout << "raw_data = " << raw_data << endl;

    //生成35bit报头
    bitset<15> STN = generateSTN();
    Header35 Jheader = Header35(STN);
    cout << "header_str = " << Jheader.toString() << endl;

    int bit_length = bit_data.length();
    //封装和发送过程：使用标准格式(STD)进行封装---按照初始字->扩展字->继续字的顺序排列
    int flag = 3;
    InitialWord iword;
    ExtendWord eword;
    ContinueWord cword;
    while (1) {
        bit_length = bit_data.length();
        if (bit_length <= 0) {
            //执行210bit奇偶校验及后续步骤，并退出
            handlerSTDP(Jheader, iword, eword, cword);
            iword.clear();
            eword.clear();
            cword.clear();
            break;
        }
        if (flag == 0 && bit_length > 0) {
            //执行210bit奇偶校验及后续步骤，并进行新一轮的打包
            handlerSTDP(Jheader, iword, eword, cword);
            iword.clear();
            eword.clear();
            cword.clear();
            flag = 3;
        }
        switch (flag)
        {
        case 3:
        {
            iword.clear();
            iword.handler_initial_word(bit_data);
            iword.show();
            //cout << "iword_70bit = " << iword.toString_70bit() << endl;
            break;
        }
        case 2:
        {
            eword.clear();
            eword.handler_extend_word(bit_data);
            eword.show();
            //cout << "eword_70bit = " << eword.toString_70bit() << endl;
            break;
        }
        case 1:
        {
            cword.clear();
            cword.handler_continue_word(bit_data);
            cword.show();
            //cout << "cword_70bit = " << cword.toString_70bit() << endl;
            break;
        }
        default:
            break;
        }
        flag--;
    }
}
#else //RECIEVE
int main()
{
    //正确数据
    string real_data = "001011100110000101101110011010010110100001000011001000000110110101101111011100100110011000100000011\
0010101101101011011110110001100100000010010010010000000101100011011100110000101110101011110010110100101010011001000\
0001101001011000010100001100100000011100110110100100100000011001010110110101100001011011100010000001111001010011010\
0100000001000010110010101101110011011110111100101110010011001010111011001100101001000000010110001101111011011000110\
11000110010101001000";

    //数据准备
    string bit_data = "10001010001011000010000100010001001000000000001000101110011000010110111001101001011010000100001100100000001001001101101011011110111001001100110001000000110010101101101011011110110000000000000001100100000010010010010000000101100011011100110000101110101011100000\
10001010001011000010000100010001001000000000001010010110100101010011001000000110100101100001010000110010001001000000111001101101001001000000110010101101101011000010110111000100000000000000000011110010100110100100000001000010110010101101110011011110111100100000\
10001010001011000010000100010001001000000000001001110010011001010111011001100101001000000010110001101111001001000000000000000000000000000000000000000110110001101100011001010100100000000000000000000000000000000000000000000000000000000000000000000000000000000000";

    string bit_message;

    ////问题
    //char test_ch[ecclen];
    //for (int i = 0; i < ecclen; i++) {
    //    test_ch[i] = 'u';
    //}
    ////正解
    //string test_str(ecclen, '0');
    //for (int i = 0; i < ecclen; i++) {
    //    test_str[i] = test_ch[i];
    //}
    //cout << "test_str = " << test_str << endl;
    //cout << "test_str_length = " << test_str.length() << endl;


    while (bit_data.length() != 0) {
        //截取一组消息
        cout << "当前消息长度为：" << bit_data.length() << endl;
        string str_group = getGroup(bit_data);
        cout << bit_data << endl;

        //去消息头
        str_group.erase(0, 35);
        //从InitialWord中取信息
        bit_message += str_group.substr(13, 57);
        //去InitialWord
        str_group.erase(0, 75);
        //从ExtendWord中取信息
        bit_message += str_group.substr(2, 68);
        //去ExtendWord
        str_group.erase(0, 75);
        //从ContinueWord中取信息
        bit_message += str_group.substr(7, 63);
    }
    cout << "消息数据长度为：" << bit_message.length() << endl;
    string res = bit_message.substr(0, 433) + bit_message.substr(470, 31);
    cout << "真实消息为：" << real_data << endl;
    cout << "消息数据为：" << res << endl;
    string last = BitStrTostr(res);
    cout << "最终转换后的消息为：" << last << endl;
}
#endif // TRANSMIT