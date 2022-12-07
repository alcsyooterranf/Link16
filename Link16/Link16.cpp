#include <iostream>
#include <bitset>
#include <algorithm>
#include "tools.h"

#define RECIEVING
#ifdef SENDING
int main()
{
	//数据准备
	std::cout << "请输入要转换的字符串：";
	string message;
	getline(std::cin, message);//读入一行字符串，遇到换行结束

	srand((unsigned)time(NULL));
	string bit_data = StrToBitStr(message);
	std::cout << "raw_data = " << message << std::endl;
	std::cout << "bit_data = " << bit_data << std::endl;

	//判断文件是否存在，若存在则删除
	if (!deleteFile()) {
		return 2;
	}

	bitset<15> STN = bitset<15>(generateBIN(15));
	HeaderWord headerWord = HeaderWord(STN);
	headerWord.show();

	size_t bit_length = bit_data.length();
	//封装和发送过程：使用标准格式(STD)进行封装---按照初始字->扩展字->继续字的顺序排列
	int flag = 3;
	InitialWord iword;
	ExtendWord eword;
	ContinueWord cword;
	while (1) {
		bit_length = bit_data.length();
		if (bit_length <= 0) {
			//执行210bit奇偶校验及后续步骤，并退出
			handlerSTDP(headerWord, iword, eword, cword);
			iword.clear();
			eword.clear();
			cword.clear();
			break;
		}
		if (flag == 0 && bit_length > 0) {
			//执行210bit奇偶校验及后续步骤，并进行新一轮的打包
			handlerSTDP(headerWord, iword, eword, cword);
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
			iword.handler_word(bit_data);
			iword.show();
			break;
		}
		case 2:
		{
			eword.clear();
			eword.handler_word(bit_data);
			eword.show();
			break;
		}
		case 1:
		{
			cword.clear();
			cword.handler_word(bit_data);
			cword.show();
			break;
		}
		default:
			break;
		}
		flag--;
	}
}
#endif // SENDING

#ifdef RECIEVING
#include "decodeTools.h"
#include "STDPMsg.h"

int main()
{
	//从文件中读入数据
	string RT_bit_data = read_msg();
	string bit_msg;

	//TODO:用STDPMsg类封装解包后的数据
	STDPMsg stdp_msg;

	while (RT_bit_data.length() != 0) {
		//截取一组消息
		std::cout << "当前消息长度为：" << RT_bit_data.length() << std::endl;
		string str_group = getGroup(RT_bit_data);
		stdp_msg.setRawMsg(str_group);

		//解交织
		string str_weave = decode_weave(str_group);

		//解RS编码、AES解密、BIP校验
		string bit_data = decode_RS_AES_BIP_handler(str_weave);
		if (bit_data.empty()) {
			std::cout << "[decode_RS_AES_BIP_handler]函数内部出错" << std::endl;
			return -1;
		}

		//去HeaderWord
		bit_data.erase(0, 35);
		//从InitialWord中取data
		bit_msg += getData(bit_data, 13, 57);
		//去InitialWord
		bit_data.erase(0, 75);
		//从ExtendWord中取data
		bit_msg += getData(bit_data, 2, 68);
		//去ExtendWord
		bit_data.erase(0, 75);
		//从ContinueWord中取data
		bit_msg += getData(bit_data, 7, 63);
	}
	stdp_msg.setBitMsg(bit_msg);
	std::cout << "消息数据长度为：" << bit_msg.length() << std::endl;
	std::cout << "接收到的消息为：" << bit_msg << std::endl;
	std::cout << "解码后的消息为：" << BitStrTostr(bit_msg) << std::endl;
}
#endif // RECIEVING

#ifdef DEBUG
int main() {
}
#endif // DEBUG