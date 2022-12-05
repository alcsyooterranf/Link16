#include <iostream>
#include <bitset>
#include <algorithm>
#include "tools.h"

#define SENDING
#ifdef SENDING
int main()
{
	//数据准备
	string message = "Hello, everyone! My name is Cai Siyuan, I come from China.";
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
#endif

#ifdef RECIEVING
#include "decodeTools.h"
#include "STDPMsg.h"

int main()
{
	//正确数据
	string message = "Hello, everyone! My name is Cai Siyuan, I come from China.";
	string real_data = StrToBitStr(message);
	std::cout << "real_data = " << real_data << std::endl;

	////数据准备(对照组)
	////明文（不变）
	//string first_AES_Encrypt_plain = "";
	//string second_AES_Encrypt_plain = "";
	//string third_AES_Encrypt_plain = "";

	////密文（不变）
	//string first_AES_Encrypt_out = "";
	//string second_AES_Encrypt_out = "";
	//string third_AES_Encrypt_out = "";

	////RS编码后
	//string first_bit_after_RS = "";
	//string second_bit_after_RS = "";
	//string third_bit_after_RS = "";

	//从文件中读入数据
	string RT_bit_data = read_msg();

	string bit_message;
	STDPMsg stdp_msg;

	while (RT_bit_data.length() != 0) {
		//截取一组消息
		std::cout << "当前消息长度为：" << RT_bit_data.length() << std::endl;
		string str_group = getGroup(RT_bit_data);
		stdp_msg.setRawMsg(str_group);

		//解交织
		string str_weave = decode_weave(str_group);
		std::cout << "解交织后字符串 = " << str_weave << std::endl;

		//解RS编码、AES解密、BIP校验
		string str_data = decode_RS_AES_BIP_handler(str_weave);
		if (str_data.empty()) {
			return 2;
		}

		//去HeaderWord
		str_data.erase(0, 35);
		//从InitialWord中取data
		bit_message += str_data.substr(13, 57);
		//去InitialWord
		str_data.erase(0, 75);
		//从ExtendWord中取data
		bit_message += str_data.substr(2, 68);
		//去ExtendWord
		str_data.erase(0, 75);
		//从ContinueWord中取data
		bit_message += str_data.substr(7, 63);
	}
	std::cout << "消息数据长度为：" << bit_message.length() << std::endl;
	std::cout << "接收到的消息为：" << bit_message << std::endl;
	std::cout << "应该收到消息为：" << real_data << std::endl;
	//清除空数据
	bit_message = bit_message.substr(0, 429) + bit_message.substr(466, 35);
	std::cout << "bit_message   = " << bit_message << std::endl;
	string last = BitStrTostr(bit_message);
	std::cout << "最终解码后的消息为：" << last << std::endl;
}
#endif //

#ifdef DEBUG
int main() {
}
#endif // DEBUG