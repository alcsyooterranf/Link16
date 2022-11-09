#include <iostream>
#include <bitset>
#include <string>
#include <algorithm>
#include "dataType.h"
#include "tools.h"

using namespace std;

int main()
{
	//数据准备
	string message = "Hello, everyone! My name is Cai Siyuan, I come from China.";

    string bit_data = StrToBitStr(message);
    string raw_data = BitStrTostr(bit_data);
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
            break;
        }
        if (flag == 0 && bit_length > 0) {
            //执行210bit奇偶校验及后续步骤，并进行新一轮的打包
            handlerSTDP(Jheader, iword, eword, cword);
            flag = 3;
        }
        switch (flag)
        {
        case 3:
        {
            iword.clear();
            iword.handler_initial_word(bit_data);
            iword.show();
            string str_iword = iword.toString_70bit();
            cout << "iword_70bit = " << str_iword << endl;
            break;
        }
        case 2:
        {
            eword.clear();
            eword.handler_extend_word(bit_data);
            eword.show();
            string str_eword = eword.toString_70bit();
            cout << "eword_70bit = " << str_eword << endl;
            break;
        }
        case 1:
        {
            cword.clear();
            cword.handler_continue_word(bit_data);
            cword.show();
            string str_cword = cword.toString_70bit();
            cout << "cword_70bit = " << str_cword << endl;
            break;
        }
        default:
            break;
        }
        flag--;
    }
}