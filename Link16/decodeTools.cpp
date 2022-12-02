#include <iostream>
#include <bitset>
#include "decodeTools.h"

using namespace std;

const unsigned int BLOCK_BYTES_LENGTH = 16 * sizeof(unsigned char);

string getGroup(string& bit_data) {
	string group = bit_data.substr(0, 545);
	bit_data.erase(0, 545);
	return group;
}

//将一个stdp字符串消息用symbol数据格式封装
void StrToSymbol(symbol* stdp, size_t length, string& message) {
	for (int i = 0; i < length; i++) {
		stdp[i] = bitset<5>(message.substr(i * 5, 5));
	}
}

//raw_msg长度必须为545
string decode_weave(string& raw_msg) {
	symbol* bit_data = new symbol[108];
	StrToSymbol(bit_data, 108, raw_msg);
	//for (int i = 0; i < 108; i++) {
	//	bit_data[i] = bitset<5>(raw_msg.substr(i * 5, 5));
	//}

	symbol** matrix = new symbol * [9];
	for (int i = 0; i < 9; i++) {
		matrix[i] = new symbol[12];
		for (int j = 0; j < 12; j++) {
			matrix[i][j] = bit_data[i * 12 + j];
		}
	}

	string res;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 9; j++) {
			res += matrix[j][i].to_string();
		}
	}
	res += raw_msg.substr(540, 5);

	//释放资源
	delete[] bit_data;
	bit_data = nullptr;

	for (int i = 0; i < 9; i++) {
		delete[] matrix[i];
		matrix[i] = nullptr;
	}
	delete[] matrix;
	matrix = nullptr;
	return res;
}

//解码HeaderWord
string decode_RS_code_16_7(symbol* head) {
	string str_hword(code_31_15, 0x00);
	for (int i = 0; i < data_16_7; i++) {
		str_hword[i] = static_cast<char>(head[i].to_ulong());
	}
	for (int i = data_31_15 + 7; i < code_31_15; i++) {
		str_hword[i] = static_cast<char>(head[i - data_31_15].to_ulong());
	}
	////print
	//std::cout << "RS编码前转换后的symbol(二进制表示): " << std::endl;
	//for (int i = 0; i < code_31_15; i++) {
	//	for (int j = 7; j >= 0; j--) {
	//		std::cout << ((str_hword[i] >> j) & 1);
	//	}
	//}
	//std::cout << std::endl;
	string hword_data(data_31_15, 0x00);
	if (!decode_RS(str_hword, hword_data)) {
		std::cout << "RS解码成功" << std::endl;
	}
	else {
		std::cout << "RS解码失败" << std::endl;
	}
	hword_data.erase(data_16_7, 8);
	return hword_data;
}

//解码Word
string decode_RS_code_31_15(symbol* head) {
	string str_word(code_31_15, 0x00);
	for (int i = 0; i < code_31_15; i++) {
		str_word[i] = static_cast<char>(head[i].to_ulong());
	}
	////print
	//std::cout << "RS编码前转换后的symbol(二进制表示): " << std::endl;
	//for (int i = 0; i < code_31_15; i++) {
	//	for (int j = 7; j >= 0; j--) {
	//		std::cout << ((str_iword[i] >> j) & 1);
	//	}
	//}
	//std::cout << std::endl;
	string word_data(data_31_15, 0x00);
	if (!decode_RS(str_word, word_data)) {
		std::cout << "RS解码成功" << std::endl;
	}
	else {
		std::cout << "RS解码失败" << std::endl;
	}
	return word_data;
}

//message长度必须为545
string decode_RS_AES_BIP_handler(string& message) {
	if (message.length() != 545) {
		std::cout << "错误的STDP消息格式" << std::endl;
		return "";
	}
	symbol* stdp = new symbol[109];
	StrToSymbol(stdp, 109, message);
	string char_data;

	//解码HeaderWord
	symbol* hword = stdp;
	char_data += decode_RS_code_16_7(hword);

	//解码InitialWord
	symbol* iword = hword + code_16_7;
	char_data += decode_RS_code_31_15(iword);

	//解码ExtendWord
	symbol* eword = iword + code_31_15;
	char_data += decode_RS_code_31_15(eword);

	//解码ContinueWord
	symbol* cword = eword + code_31_15;
	char_data += decode_RS_code_31_15(cword);

	//释放资源
	delete[] stdp;
	stdp = nullptr;

	//print
	std::cout << "before_DES_Decrypt = " << std::endl;
	for (int i = 0; i < 52; i++) {
		for (int j = 7; j >= 0; j--) {
			std::cout << ((char_data[i] >> j) & 1);
		}
	}
	std::cout << std::endl;

	//AES解密
	string bit_str = AES_decrypt(char_data);

	return bit_str;
}

string AES_decrypt(string& char_data) {
	string str_data;
	for (auto i : char_data)
	{
		bitset<5> bs(i);
		str_data += bs.to_string();
	}

	std::cout << "str_data.length() = " << str_data.length() << std::endl;
	std::cout << "AES解密函数入参：str_data = " << str_data << std::endl;

	string ciper_data = str_data.substr(0, 256);
	uint8_t* cipher = StrToCharArray(ciper_data, 32);
	AES aes(AESKeyLength::AES_128);
	const uint8_t key_16[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
	uint8_t* out = aes.DecryptECB(cipher, BLOCK_BYTES_LENGTH, key_16);
	string tmp;
	for (int i = 0; i < 32; i++) {
		tmp += out[i];
	}
	string bit_str = StrToBitStr(tmp) + str_data.substr(256, 4);
	std::cout << "AES解密之后字符串 = " << bit_str << std::endl;
	return bit_str;
}

//message必须压缩为char
int decode_RS(string& message, string& str_data) {
	/* Finite Field Parameters */
	const std::size_t field_descriptor = 5;
	const std::size_t generator_polynomial_index = 0;
	const std::size_t generator_polynomial_root_count = 16;

	/* Reed Solomon Code Parameters */
	const std::size_t code_length = RS_Length::code_31_15; //(2^5 - 1)
	const std::size_t data_length = RS_Length::data_31_15;
	const std::size_t fec_length = RS_Length::fec_31_15;

	/* 5-bit Symbol Parameter */
	const int mask = 0x0000001F;

	/* Instantiate Finite Field and Generator Polynomials */
	const schifra::galois::field field(field_descriptor,
		schifra::galois::primitive_polynomial_size02,
		schifra::galois::primitive_polynomial02);

	schifra::galois::field_polynomial generator_polynomial(field);

	if (
		!schifra::make_sequential_root_generator_polynomial(field,
			generator_polynomial_index,
			generator_polynomial_root_count,
			generator_polynomial)
		)
	{
		std::cout << "Error - Failed to create sequential root generator!" << std::endl;
		return 1;
	}

	/* Instantiate Encoder and Decoder (Codec) */
	typedef schifra::reed_solomon::decoder<code_length, fec_length> decoder_t;

	const decoder_t decoder(field, generator_polynomial_index);

	string data = message.substr(0, 15);
	string fec = message.substr(15, 16);
	/* Instantiate RS Block For Codec */
	schifra::reed_solomon::block<code_length, fec_length> block(data, fec);

	///* Pad message with nulls up until the code-word length */
	//message.resize(code_length, 0x00);

	///* Populate RS Blocks with 5-bit data symbols */
	//for (std::size_t i = 0; i < code_length; ++i)
	//{
	//	/*block[i] = static_cast<int>(i & mask);*/
	//	block[i] = static_cast<int>(message[i] & mask);
	//}

	////格式化str_fec
	//string str_fec(RS_Length::fec_31_15, 0x00);
	//block.fec_to_string(str_fec);

	//string temp(RS_Length::data_31_15, 0x00);
	//block.data_to_string(temp);
	//cout << "block.data = ";
	////print
	//for (int i = 0; i < RS_Length::data_31_15; i++) {
	//	for (int j = 7; j >= 0; j--) {
	//		std::cout << ((temp[i] >> j) & 1);
	//	}
	//}
	//std::cout << std::endl;

	if (!decoder.decode(block))
	{
		std::cout << "Error - Critical decoding failure! "
			<< "Msg: " << block.error_as_string() << std::endl;
		return 1;
	}
	block.data_to_string(str_data);
	return 0;
}