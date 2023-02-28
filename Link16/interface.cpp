#include "interface.h"

//m,n�Ƿ��͵�ս����Ϣ����,inputs����Ϣ��Ҫ����
int encoder_Link16(int m, int n, string& inputs) {
	//����׼��
	string type = to_string(m) + " " + to_string(n);
	if (g_JType.count(type) == 0) {
		std::cout << "���͵���Ϣ���Ͳ�����" << std::endl;
		return -1;
	}
	std::cout << "���͵���Ϣ����Ϊ��" << g_JType[type] << std::endl;

	srand((unsigned)time(NULL));
	string bit_data = StrToBitStr(inputs);
	std::cout << "raw_data = " << inputs << std::endl;
	std::cout << "bit_data = " << bit_data << std::endl;

	//�ж��ļ��Ƿ���ڣ���������ɾ��
	if (!deleteFile()) {
		return -2;
	}

	bitset<15> STN = bitset<15>(generateBIN(15));
	HeaderWord headerWord = HeaderWord(STN);
	headerWord.show();

	size_t bit_length = bit_data.length();
	//��װ�ͷ��͹��̣�ʹ�ñ�׼��ʽ(STD)���з�װ---���ճ�ʼ��->��չ��->�����ֵ�˳������
	int flag = 3;
	InitialWord iword;
	ExtendWord eword;
	ContinueWord cword;
	while (1) {
		bit_length = bit_data.length();
		if (bit_length <= 0) {
			//ִ��210bit��żУ�鼰�������裬���˳�
			handlerSTDP(headerWord, iword, eword, cword);
			iword.clear();
			eword.clear();
			cword.clear();
			break;
		}
		if (flag == 0 && bit_length > 0) {
			//ִ��210bit��żУ�鼰�������裬��������һ�ֵĴ��
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

int decoder_Link16() {
	//���ļ��ж�������
	string RT_bit_data = read_msg();
	string bit_msg;

	//TODO:��STDPMsg���װ����������
	STDPMsg stdp_msg;

	while (RT_bit_data.length() != 0) {
		//��ȡһ����Ϣ
		std::cout << "��ǰ��Ϣ����Ϊ��" << RT_bit_data.length() << std::endl;
		string str_group = getGroup(RT_bit_data);
		stdp_msg.setRawMsg(str_group);

		//�⽻֯
		string str_weave = decode_weave(str_group);

		//��RS���롢AES���ܡ�BIPУ��
		string bit_data = decode_RS_AES_BIP_handler(str_weave);
		if (bit_data.empty()) {
			std::cout << "[decode_RS_AES_BIP_handler]�����ڲ�����" << std::endl;
			return -1;
		}

		//ȥHeaderWord
		bit_data.erase(0, 35);
		//��InitialWord��ȡdata
		bit_msg += getData(bit_data, 13, 57);
		//ȥInitialWord
		bit_data.erase(0, 75);
		//��ExtendWord��ȡdata
		bit_msg += getData(bit_data, 2, 68);
		//ȥExtendWord
		bit_data.erase(0, 75);
		//��ContinueWord��ȡdata
		bit_msg += getData(bit_data, 7, 63);
	}
	stdp_msg.setBitMsg(bit_msg);
	std::cout << "��Ϣ���ݳ���Ϊ��" << bit_msg.length() << std::endl;
	std::cout << "���յ�����ϢΪ��" << bit_msg << std::endl;
	std::cout << "��������ϢΪ��" << BitStrTostr(bit_msg) << std::endl;
}