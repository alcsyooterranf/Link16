#include "interface.h"

//m,n是发送的战术消息类型,inputs是消息主要内容
int32_t encoder_Link16(int32_t n, int32_t m, string& inputs) {
	//数据准备
	string type = to_string(n) + " " + to_string(m);
	if (g_JType.count(type) == 0) {
		std::cout << "发送的消息类型不存在" << std::endl;
		return -1;
	}
	std::cout << "发送的消息类型为：" << g_JType[type] << std::endl;

	srand((unsigned)time(NULL));
	string bit_data = Tools::StrToBitStr(inputs);
	std::cout << "raw_data = " << inputs << std::endl;
	std::cout << "bit_data = " << bit_data << std::endl;

	//判断文件是否存在，若存在则删除
	if (!Tools::deleteFile()) {
		return -2;
	}

	bitset<15> STN = bitset<15>(Tools::generateBIN(15));
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
			Tools::handlerSTDP(headerWord, iword, eword, cword);
			iword.clear();
			eword.clear();
			cword.clear();
			break;
		}
		if (flag == 0 && bit_length > 0) {
			//执行210bit奇偶校验及后续步骤，并进行新一轮的打包
			Tools::handlerSTDP(headerWord, iword, eword, cword);
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
			iword.handler_word(bit_data, type);
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

int32_t decoder_Link16(string& raw_data, int32_t& n, int32_t& m) {
	//从文件中读入数据
	string RT_bit_data = Tools::read_msg();
	string bit_msg;

	//TODO:用STDPMsg类封装解包后的数据
	STDPMsg stdp_msg;

	while (RT_bit_data.length() != 0) {
		//截取一组消息
		std::cout << "当前消息长度为：" << RT_bit_data.length() << std::endl;
		string str_group = Tools::getGroup(RT_bit_data);
		stdp_msg.setRawMsg(str_group);

		//解交织
		string str_weave = Tools::decode_weave(str_group);

		//解RS编码、AES解密、BIP校验
		string bit_data = Tools::decode_RS_AES_BIP_handler(str_weave);
		if (bit_data.empty()) {
			std::cout << "[decode_RS_AES_BIP_handler]函数内部出错" << std::endl;
			return -1;
		}

		//封装HeaderWord
		string headerword_str = bit_data.substr(0, 35);
		stdp_msg.setHeaderWord(headerword_str);
		//去HeaderWord
		bit_data.erase(0, 35);

		//封装InitialWord
		string iword_str = bit_data.substr(0, 75);
		stdp_msg.setInitialWord(iword_str);
		//从InitialWord取n, m
		bitset<5> signal = stdp_msg.getInitialWord()->getSignal();
		bitset<3> subSignal = stdp_msg.getInitialWord()->getSubSignal();
		n = static_cast<int32_t>(signal.to_ulong());
		m = static_cast<int32_t>(subSignal.to_ulong());
		//从InitialWord中取data
		bit_msg += stdp_msg.getInitialWord()->getData();
		//去InitialWord
		bit_data.erase(0, 75);

		//封装ExtendWord
		string eword_str = bit_data.substr(0, 75);
		stdp_msg.setExtendWord(eword_str);
		//从ExtendWord中取data
		bit_msg += stdp_msg.getExtendWord()->getData();
		//去ExtendWord
		bit_data.erase(0, 75);

		//封装ContinueWord
		string cword_str = bit_data.substr(0, 75);
		stdp_msg.setContinueWord(cword_str);
		//从ContinueWord中取data
		bit_msg += stdp_msg.getContinueWord()->getData();
	}
	stdp_msg.setBitMsg(bit_msg);
	raw_data = bit_msg;
}