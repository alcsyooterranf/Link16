// Link16.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#pragma pack(1)
#include <iostream>
#include <bitset>
#include <string>
#include <algorithm>
#include "dataType.h"
#include "handler.h"
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
    bitset<15> tmp = generateSTN();
    header_35 Jheader = generate_J_header(tmp);

    //处理报头
    handler_header(Jheader, send_msg);

    int bit_length = bit_data.length();
    //封装和发送过程：使用标准格式(STD)进行封装---按照初始字->扩展字->继续字的顺序排列
    int flag = 3;
    while (1) {
        bit_length = bit_data.length();
        if (bit_length <= 0) {
            break;
        }
        //cout << "bit_data = " << bit_data << endl;
        //cout << "bit_length = " << bit_length << endl;
        if (flag == 0 && bit_length > 0) { //进行新一轮的发送
            flag = 3;
        }
        switch (flag)
        {
        case 3:
            handler_initial_word(bit_data, send_msg);
            break;
        case 2:
            handler_extend_word(bit_data, send_msg);
            break;
        case 1:
            handler_continue_word(bit_data, send_msg);
            break;
        default:
            break;
        }
        flag--;
    }
}