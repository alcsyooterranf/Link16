#include <iostream>
#include <string>
#include <bitset>
#include "tools.h"

using namespace std;

const unsigned int BLOCK_BYTES_LENGTH = 16 * sizeof(unsigned char);

void send_msg(const string& msg) {
	std::cout << msg << "已发送成功" << endl;
}

//随机二进制数生成器
string generateBIN(int length) {
	string res;
	for (int i = 0; i < length; i++) {
		res += to_string(rand() % 2);
	}
	return res;
}

string StrToBitStr(const string& str) {
	size_t len = str.length();
	string res;

	for (int i = 0; i < len; i++) {
		bitset<8> bits = bitset<8>(str[i]);
		bitset<1> tmp;
		//二进制翻转
		for (int j = 0; j < 4; j++)
		{
			tmp[0] = bits[j];
			bits[j] = bits[7 - j];
			bits[7 - j] = tmp[0];
		}
		res += bits.to_string();
	}

	//添加一个翻转操作
	reverse(begin(res), end(res));
	return res;
}

string BitStrTostr(const string& str) {
	size_t len = str.length();
	string res;
	for (int i = 0; i < len; i = i + 8) {
		string tmp;
		for (int j = 0; j < 8; j++) {
			tmp += str[i + j];
		}
		bitset<8> ch = bitset<8>(tmp);
		res += (char)ch.to_ulong();
	}
	//添加一个翻转操作
	reverse(begin(res), end(res));
	return res;
}

//输入字符串str_data长度必须为8的整数倍
//功能：将二进制字符串“0000000100000010”按8bit一组合并转化{ "1", "2" }的字符数组
uint8_t* StrToCharArray(string& str_data, int char_length) {
	size_t len = str_data.length();
	if (len % 8 != 0) {
		cout << "CRC输入字符串长度有误，需8bit整数倍";
		return nullptr;
	}
	//CRC(237, 225)，225bit要用29Bytes装填
	uint8_t* data = new uint8_t[char_length]();
	for (int i = 0; i < char_length; i++) {
		bitset<8> tmp = bitset<8>(str_data.substr(i * 8, 8));
		/*std::cout << tmp.to_string() << endl;*/
		data[i] = static_cast<uint8_t>(tmp.to_ulong());
	}
	return data;
}

//使用CRC循环冗余校验(使用CRCpp库)
void BIP(HeaderWord& hword, InitialWord& iword,
	ExtendWord& eword, ContinueWord& cword) {
	string str_data = hword.toString_15B() + iword.toString_70B() + eword.toString_70B() + cword.toString_70B();
	//CRC(237, 225)，225bit要用29Bytes装填
	str_data += "0000000";
	uint8_t* data = StrToCharArray(str_data, 29);
	if (data == nullptr) {
		return;
	}
	////print
	//std::cout << "data = ";
	//for (int i = 0; i < 29; i++) {
	//    std::cout << "data[" << i << "]" << data[i] << endl;
	//}
	std::uint16_t crc = CRC::CalculateBits(data, 225, CRC::CRC_12_CDMA2000());
	bitset<16> bit_crc = bitset<16>(crc);
	//std::cout << "bit_crc = " << bit_crc.to_string() << endl;
	iword.setBIP(bitset<5>("0" + bit_crc.to_string().substr(4, 4)));
	eword.setBIP(bitset<5>("0" + bit_crc.to_string().substr(8, 4)));
	cword.setBIP(bitset<5>("0" + bit_crc.to_string().substr(12, 4)));
	delete data;
	data = nullptr;
}

//TODO: 使用AES加密数据(记得更改回MD5)
void AES_Encrypt(HeaderWord& hword, InitialWord& iword,
	ExtendWord& eword, ContinueWord& cword) {
	string message = hword.toString() + iword.toString()
		+ eword.toString() + cword.toString();
	//总长度 = 75 + 75 + 75 + 35 = 260bit。由于AES算法的输入限制，只加密前256bit数据。

	//print
	std::cout << "AES加密之前的STDP消息 = " << message << std::endl;

	string str_data = message.substr(0, 256);
	uint8_t* plain = StrToCharArray(str_data, 32);
	AES aes(AESKeyLength::AES_128);
	string key = hword.getSDU().to_string().substr(0, 8);
	//MD5 md5(key);
	//const uint8_t* key_16 = md5.getDigest();
	const uint8_t key_16[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
	uint8_t* out = aes.EncryptECB(plain, BLOCK_BYTES_LENGTH, key_16);
	string tmp;
	for (int i = 0; i < 32; i++) {
		tmp += out[i];
	}
	string bit_str = StrToBitStr(tmp) + message.substr(256, 4);

	//print
	std::cout << "AES加密之后的STDP消息 = " << bit_str << std::endl;

	//将AES加密后的数据重新写入报头
	string bit_header = bit_str.substr(0, 35);
	hword.rewrite(bit_header);

	//将AES加密后的数据重新写入字
	string bit_iword = bit_str.substr(35, 75);
	iword.rewrite(bit_iword);
	string bit_eword = bit_str.substr(110, 75);
	eword.rewrite(bit_eword);
	string bit_cword = bit_str.substr(185, 75);
	cword.rewrite(bit_cword);
}

//将长度为109Symbol的消息按照先行后列的顺序写入12 x 9的矩阵（最后一个Symbol不参与交织）,然后按照先列后行的顺序打印输出
void weave(HeaderWord& hword, InitialWord& iword,
	ExtendWord& eword, ContinueWord& cword) {
	symbol* bit_data = new symbol[108];
	symbol* RS_Header = hword.getRS_word();
	symbol* RS_iword = iword.getRS_word();
	symbol* RS_eword = eword.getRS_word();
	symbol* RS_cword = cword.getRS_word();

	for (int i = 0; i < 108; i++) {
		if (i < 16) {
			bit_data[i] = RS_Header[i];
		}
		else if (i >= 16 && i < 47) {
			bit_data[i] = RS_iword[i - 16];
		}
		else if (i >= 47 && i < 78) {
			bit_data[i] = RS_eword[i - 47];
		}
		else {
			bit_data[i] = RS_cword[i - 78];
		}
	}

	symbol** matrix = new symbol * [12];
	for (int i = 0; i < 12; i++) {
		matrix[i] = new symbol[9];
		for (int j = 0; j < 9; j++) {
			matrix[i][j] = bit_data[i * 9 + j];
		}
	}

	//发送
	string res;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 12; j++) {
			res += matrix[j][i].to_string();
		}
	}
	res += RS_cword[30].to_string();
	std::cout << "======交织后的STDP消息内容如下：======\n";
	cout << res << endl;

	//释放资源
	delete[] bit_data;
	bit_data = nullptr;

	for (int i = 0; i < 12; i++) {
		delete[] matrix[i];
		matrix[i] = nullptr;
	}
	delete[] matrix;
	matrix = nullptr;
}

int RS(const size_t codeLength, const size_t dataLength, string& message, symbol* symbol_msg) {
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
	typedef schifra::reed_solomon::encoder<code_length, fec_length> encoder_t;
	typedef schifra::reed_solomon::decoder<code_length, fec_length> decoder_t;

	const encoder_t encoder(field, generator_polynomial);
	const decoder_t decoder(field, generator_polynomial_index);

	/* Instantiate RS Block For Codec */
	schifra::reed_solomon::block<code_length, fec_length> block;
	schifra::reed_solomon::block<code_length, fec_length> original_block;

	/* Pad message with nulls up until the code-word length */
	message.resize(code_length, 0x00);

	/* Populate RS Blocks with 5-bit data symbols */
	for (std::size_t i = 0; i < data_length; ++i)
	{
		/*block[i] = static_cast<int>(i & mask);*/
		original_block[i] = static_cast<int>(message[i] & mask);
	}

	/* Transform message into Reed-Solomon encoded codeword */
	//将Symbol处理后的message中的数据逐个放入block块中进行编码，然后将编码后的数据存入block.data中(前面放原始数据，后面放FEC码)
	if (!encoder.encode(message, block))
	{
		std::cout << "Error - Critical encoding failure! "
			<< "Msg: " << block.error_as_string() << std::endl;
		return 1;
	}

	//格式化str_fec
	string str_fec(RS_Length::fec_31_15, 0x00);
	block.fec_to_string(str_fec);

	////print(用char封装的二进制数)
	//string str_data(RS_Length::data_31_15, 0x00);
	//block.data_to_string(str_data);
	//string str_code = str_data + str_fec;
	//std::cout << "统一31_15RS编码后 = " << std::endl;
	//for (int i = 0; i < RS_Length::code_31_15; i++) {
	//	for (int j = 7; j >= 0; j--) {
	//		std::cout << ((str_code[i] >> j) & 1);
	//	}
	//}
	//std::cout << std::endl;

	if (codeLength == RS_Length::code_31_15 && dataLength == RS_Length::data_31_15) {
		//Assemble(Word)
		for (int i = RS_Length::data_31_15; i < RS_Length::code_31_15; i++) {
			bitset<8> temp = bitset<8>(str_fec[i - RS_Length::data_31_15]);
			symbol_msg[i] = symbol(temp.to_string().substr(3, 5));
		}
	}

	else if (codeLength == RS_Length::code_16_7 && dataLength == RS_Length::data_16_7) {
		//Assemble(Header)，丢掉fec中前7Symbol的纠错位
		for (int i = RS_Length::data_16_7; i < RS_Length::code_16_7; i++) {
			bitset<8> temp = bitset<8>(str_fec[i]);
			symbol_msg[i] = symbol(temp.to_string().substr(3, 5));
		}
	}
	else {
		return 1;
	}

	/* Add errors at every 3th location starting at position zero */
	schifra::corrupt_message_all_errors_wth_mask(block, 0, mask, 3);

	if (!decoder.decode(block))
	{
		std::cout << "Error - Critical decoding failure! "
			<< "Msg: " << block.error_as_string() << std::endl;
		return 1;
	}
	else if (!schifra::are_blocks_equivelent(block, original_block, data_length))
	{
		std::cout << "Error - Error correction failed!" << std::endl;
		return 1;
	}
	return 0;
}

void handlerSTDP(HeaderWord& hword, InitialWord& iword,
	ExtendWord& eword, ContinueWord& cword) {
	//执行奇偶校验，70bit -> 75bit
	std::cout << "======" << "开始执行奇偶校验" << "======" << endl;
	BIP(hword, iword, eword, cword);

	//消息加密
	std::cout << "======" << "开始AES加密" << "======" << endl;
	AES_Encrypt(hword, iword, eword, cword);

	//Symbol转换，然后进行RS编码
	hword.to_symbol();
	std::cout << "======" << "开始执行RS纠错编码 7Symbol --> 16Symbol" << "======" << endl;
	hword.RS_handler();

	iword.to_symbol();
	std::cout << "======" << "开始执行RS纠错编码 15Symbol --> 31Symbol" << "======" << endl;
	iword.RS_handler();

	eword.to_symbol();
	std::cout << "======" << "开始执行RS纠错编码 15Symbol --> 31Symbol" << "======" << endl;
	eword.RS_handler();

	cword.to_symbol();
	std::cout << "======" << "开始执行RS纠错编码 15Symbol --> 31Symbol" << "======" << endl;
	cword.RS_handler();

	//std::cout << "======交织前的STDP消息内容如下：======\n"
	//	<< hword.toString_STDP()
	//	<< iword.toString_STDP()
	//	<< eword.toString_STDP()
	//	<< cword.toString_STDP() << endl;

	//交织并发送
	std::cout << "======" << "开始执行字符交织" << "======" << endl;
	weave(hword, iword, eword, cword);

	//发送提示信息
	send_msg("一个STDP消息");
}