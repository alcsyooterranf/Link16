//#include <iostream>
//#include <sstream>
//#include <string>
//#include <bitset>
//#include <fstream>
//#include <io.h>
//#include "tools.h"
//
//void save_msg(const string& msg) {
//	std::cout << "һ��STDP��Ϣ�ѷ��ͳɹ�" << std::endl;
//	ofstream fout;
//	fout.open(FILENAME, ios::app);
//	if (fout.is_open() == false) {
//		std::cout << "���ļ�" << FILENAME << "ʧ��" << std::endl;
//		return;
//	}
//
//	//д��Ҫ���͵�����
//	fout << msg;
//	fout.close();
//	return;
//}
//
////�ж��ļ��Ƿ���ڣ���������ɾ��
//bool deleteFile() {
//	if (_access(FILENAME, 0) == 0) {
//		if (!remove(FILENAME)) {
//			std::cout << "�ļ�ɾ���ɹ�" << std::endl;
//			return true;
//		}
//		else {
//			std::cout << "�ļ�ɾ��ʧ��" << std::endl;
//			return false;
//		}
//	}
//	return true;
//}
//
////�����������������
//string generateBIN(int length) {
//	string res;
//	for (int i = 0; i < length; i++) {
//		res += to_string(rand() % 2);
//	}
//	return res;
//}
//
//vector<string> stringSplit(const string& str, char delim) {
//	std::stringstream ss(str);
//	string item;
//	vector<std::string> elems;
//	while (getline(ss, item, delim)) {
//		if (!item.empty()) {
//			elems.push_back(item);
//		}
//	}
//	return elems;
//}
//
//string StrToBitStr(const string& str) {
//	size_t len = str.length();
//	string res;
//	for (int i = 0; i < len; i++) {
//		bitset<8> bits = bitset<8>(str[i]);
//		res += bits.to_string();
//	}
//	return res;
//}
//
//string BitStrTostr(const string& str) {
//	size_t len = str.length();
//	string res;
//	for (int i = 0; i < len; i = i + 8) {
//		string tmp;
//		for (int j = 0; j < 8; j++) {
//			tmp += str[i + j];
//		}
//		bitset<8> ch = bitset<8>(tmp);
//		res += (char)ch.to_ulong();
//	}
//	return res;
//}
//
////�����ַ���str_data���ȱ���Ϊ8��������
////���ܣ����������ַ�����0000000100000010����8bitһ��ϲ�ת��{ "1", "2" }���ַ�����
//uint8_t* StrToCharArray(string& str_data, int char_length) {
//	size_t len = str_data.length();
//	if (len % 8 != 0) {
//		std::cout << "�����ַ�������������8bit������";
//		return nullptr;
//	}
//	uint8_t* data = new uint8_t[char_length]();
//	for (int i = 0; i < char_length; i++) {
//		bitset<8> tmp = bitset<8>(str_data.substr(i * 8, 8));
//		data[i] = static_cast<uint8_t>(tmp.to_ulong());
//	}
//	return data;
//}
//
////ʹ��CRCѭ������У��(ʹ��CRCpp��)
//void BIP(HeaderWord& hword, InitialWord& iword,
//	ExtendWord& eword, ContinueWord& cword) {
//	string str_data = hword.toString_15B() + iword.toString_70B() + eword.toString_70B() + cword.toString_70B();
//	//CRC(237, 225)��225bitҪ��29Bytesװ��
//	str_data += "0000000";
//	uint8_t* data = StrToCharArray(str_data, 29);
//	if (data == nullptr) {
//		return;
//	}
//	std::uint16_t crc = CRC::CalculateBits(data, 225, CRC::CRC_12_CDMA2000());
//	bitset<16> bit_crc = bitset<16>(crc);
//	iword.setBIP(bitset<5>("0" + bit_crc.to_string().substr(4, 4)));
//	eword.setBIP(bitset<5>("0" + bit_crc.to_string().substr(8, 4)));
//	cword.setBIP(bitset<5>("0" + bit_crc.to_string().substr(12, 4)));
//
//	delete[] data;
//	data = nullptr;
//}
//
//void AES_Encrypt(HeaderWord& hword, InitialWord& iword,
//	ExtendWord& eword, ContinueWord& cword) {
//	string message = hword.toString() + iword.toString()
//		+ eword.toString() + cword.toString();
//	//�ܳ��� = 75 + 75 + 75 + 35 = 260bit������AES�㷨���������ƣ�ֻ����ǰ256bit���ݡ�
//
//	string str_data = message.substr(0, 256);
//	uint8_t* plain = StrToCharArray(str_data, 32);
//
//	AES aes(AESKeyLength::AES_256);
//	const uint8_t key_16[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
//						 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
//						 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
//						 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
//	uint8_t* out = aes.EncryptECB(plain, BLOCK_BYTES_LENGTH * 2, key_16);
//
//	delete[] plain;
//	plain = nullptr;
//
//	string tmp;
//	for (int i = 0; i < 32; i++) {
//		tmp += out[i];
//	}
//
//	string bit_str = StrToBitStr(tmp) + message.substr(256, 4);
//
//	delete[] out;
//	out = nullptr;
//
//	//��AES���ܺ����������д�뱨ͷ
//	string bit_header = bit_str.substr(0, 35);
//	hword.rewrite(bit_header);
//
//	//��AES���ܺ����������д����
//	string bit_iword = bit_str.substr(35, 75);
//	iword.rewrite(bit_iword);
//	string bit_eword = bit_str.substr(110, 75);
//	eword.rewrite(bit_eword);
//	string bit_cword = bit_str.substr(185, 75);
//	cword.rewrite(bit_cword);
//}
//
////������Ϊ109Symbol����Ϣ�������к��е�˳��д��12 x 9�ľ������һ��Symbol�����뽻֯��,Ȼ�������к��е�˳���ӡ���
//void weave(HeaderWord& hword, InitialWord& iword,
//	ExtendWord& eword, ContinueWord& cword) {
//	symbol* bit_data = new symbol[108];
//	symbol* RS_Header = hword.getRS_word();
//	symbol* RS_iword = iword.getRS_word();
//	symbol* RS_eword = eword.getRS_word();
//	symbol* RS_cword = cword.getRS_word();
//
//	for (int i = 0; i < 108; i++) {
//		if (i < 16) {
//			bit_data[i] = RS_Header[i];
//		}
//		else if (i >= 16 && i < 47) {
//			bit_data[i] = RS_iword[i - 16];
//		}
//		else if (i >= 47 && i < 78) {
//			bit_data[i] = RS_eword[i - 47];
//		}
//		else {
//			bit_data[i] = RS_cword[i - 78];
//		}
//	}
//
//	symbol** matrix = new symbol * [12];
//	for (int i = 0; i < 12; i++) {
//		matrix[i] = new symbol[9];
//		for (int j = 0; j < 9; j++) {
//			matrix[i][j] = bit_data[i * 9 + j];
//		}
//	}
//
//	//����
//	string res;
//	for (int i = 0; i < 9; i++) {
//		for (int j = 0; j < 12; j++) {
//			res += matrix[j][i].to_string();
//		}
//	}
//	res += RS_cword[30].to_string();
//	std::cout << "======��֯���STDP��Ϣ�������£�======\n";
//	std::cout << res << std::endl;
//	save_msg(res);
//
//	//�ͷ���Դ
//	delete[] bit_data;
//	bit_data = nullptr;
//
//	for (int i = 0; i < 12; i++) {
//		delete[] matrix[i];
//		matrix[i] = nullptr;
//	}
//	delete[] matrix;
//	matrix = nullptr;
//}
//
//int RS(const size_t codeLength, const size_t dataLength, string& message, symbol* symbol_msg) {
//	/* Finite Field Parameters */
//	const std::size_t field_descriptor = 5;
//	const std::size_t generator_polynomial_index = 0;
//	const std::size_t generator_polynomial_root_count = 16;
//
//	/* Reed Solomon Code Parameters */
//	const std::size_t code_length = RS_Length::code_31_15; //(2^5 - 1)
//	const std::size_t data_length = RS_Length::data_31_15;
//	const std::size_t fec_length = RS_Length::fec_31_15;
//
//	/* 5-bit Symbol Parameter */
//	const int mask = 0x0000001F;
//
//	/* Instantiate Finite Field and Generator Polynomials */
//	const schifra::galois::field field(field_descriptor,
//		schifra::galois::primitive_polynomial_size02,
//		schifra::galois::primitive_polynomial02);
//
//	schifra::galois::field_polynomial generator_polynomial(field);
//
//	if (
//		!schifra::make_sequential_root_generator_polynomial(field,
//			generator_polynomial_index,
//			generator_polynomial_root_count,
//			generator_polynomial)
//		)
//	{
//		std::cout << "Error - Failed to create sequential root generator!" << std::endl;
//		return 1;
//	}
//
//	/* Instantiate Encoder and Decoder (Codec) */
//	typedef schifra::reed_solomon::encoder<code_length, fec_length> encoder_t;
//
//	const encoder_t encoder(field, generator_polynomial);
//
//	/* Instantiate RS Block For Codec */
//	schifra::reed_solomon::block<code_length, fec_length> block;
//
//	/* Pad message with nulls up until the code-word length */
//	message.resize(code_length, 0x00);
//
//	/* Transform message into Reed-Solomon encoded codeword */
//	//��Symbol������message�е������������block���н��б��룬Ȼ�󽫱��������ݴ���block.data��(ǰ���ԭʼ���ݣ������FEC��)
//	if (!encoder.encode(message, block))
//	{
//		std::cout << "Error - Critical encoding failure! "
//			<< "Msg: " << block.error_as_string() << std::endl;
//		return 1;
//	}
//
//	//��ʽ��str_fec
//	string str_fec(RS_Length::fec_31_15, 0x00);
//	block.fec_to_string(str_fec);
//
//	if (codeLength == RS_Length::code_31_15 && dataLength == RS_Length::data_31_15) {
//		//Assemble(Word)
//		for (int i = RS_Length::data_31_15; i < RS_Length::code_31_15; i++) {
//			bitset<8> temp = bitset<8>(str_fec[i - RS_Length::data_31_15]);
//			symbol_msg[i] = symbol(temp.to_string().substr(3, 5));
//		}
//	}
//
//	else if (codeLength == RS_Length::code_16_7 && dataLength == RS_Length::data_16_7) {
//		//Assemble(Header)������fec��ǰ7Symbol�ľ���λ
//		for (int i = RS_Length::data_16_7; i < RS_Length::code_16_7; i++) {
//			bitset<8> temp = bitset<8>(str_fec[i]);
//			symbol_msg[i] = symbol(temp.to_string().substr(3, 5));
//		}
//	}
//	else {
//		return 1;
//	}
//	return 0;
//}
//
//void handlerSTDP(HeaderWord& hword, InitialWord& iword,
//	ExtendWord& eword, ContinueWord& cword) {
//	//ִ����żУ�飬70bit -> 75bit
//	std::cout << "======" << "��ʼִ����żУ��" << "======" << std::endl;
//	BIP(hword, iword, eword, cword);
//
//	//��Ϣ����
//	std::cout << "======" << "��ʼAES����" << "======" << std::endl;
//	AES_Encrypt(hword, iword, eword, cword);
//
//	//Symbolת����Ȼ�����RS����
//	hword.to_symbol();
//	std::cout << "======" << "HeaderWordִ��RS������� 7Symbol --> 16Symbol" << "======" << std::endl;
//	hword.RS_handler();
//
//	iword.to_symbol();
//	std::cout << "======" << "InitialWordִ��RS������� 15Symbol --> 31Symbol" << "======" << std::endl;
//	iword.RS_handler();
//
//	eword.to_symbol();
//	std::cout << "======" << "ExtendWordִ��RS������� 15Symbol --> 31Symbol" << "======" << std::endl;
//	eword.RS_handler();
//
//	cword.to_symbol();
//	std::cout << "======" << "ContinueWordִ��RS������� 15Symbol --> 31Symbol" << "======" << std::endl;
//	cword.RS_handler();
//
//	//��֯������
//	std::cout << "======" << "��ʼִ���ַ���֯" << "======" << std::endl;
//	weave(hword, iword, eword, cword);
//}