#include <iostream>
#include <string>
#include <bitset>
#include "dataType.h"
#include "tools.h"
#include "InitialWord.h"
#include "ExtendWord.h"
#include "ContinueWord.h"
#include "Header35.h"
#include "CRC.h"

#include <cstddef>

#define NO_GFLUT
#include "schifra_galois_field.hpp"
#undef NO_GFLUT
#include "schifra_galois_field_polynomial.hpp"
#include "schifra_sequential_root_generator_polynomial_creator.hpp"
#include "schifra_reed_solomon_encoder.hpp"
#include "schifra_reed_solomon_decoder.hpp"
#include "schifra_reed_solomon_block.hpp"
#include "schifra_error_processes.hpp"
#include "schifra_reed_solomon_bitio.hpp"

using namespace std;

void send_msg(const string& msg) {
    std::cout << msg << "�ѷ��ͳɹ�" << endl;
}

//��α���������15bit��STN
bitset<15> generateSTN() {
    srand(time(0));
    string res;
    for (int i = 0; i < 15; i++) {
        res += to_string(rand() % 2);
    }
    bitset<15> STN = bitset<15>(res);
    return STN;
}

string StrToBitStr(const string& str) {
    int len = str.length();
    string res;

    for (int i = 0; i < len; i++) {
        bitset<8> bits = bitset<8>(str[i]);
        bitset<1> tmp;
        //�����Ʒ�ת
        for (int j = 0; j < 4; j++)
        {
            tmp[0] = bits[j];
            bits[j] = bits[7 - j];
            bits[7 - j] = tmp[0];
        }
        res += bits.to_string();
    }

    //���һ����ת����
    reverse(begin(res), end(res));
    return res;
}

string BitStrTostr(const string& str) {
    int len = str.length();
    string res;
    for (int i = 0; i < len; i = i + 8) {
        string tmp;
        for (int j = 0; j < 8; j++) {
            tmp += str[i + j];
        }
        bitset<8> ch = bitset<8>(tmp);
        res += (char)ch.to_ulong();
    }
    //���һ����ת����
    reverse(begin(res), end(res));
    return res;
}

uint8_t* StrToCharArray(string& str_data) {
    //CRC(237, 225)��225bitҪ��29Bytesװ��
    uint8_t* data = new uint8_t[29];
    memset(data, 0x00, sizeof(data));
    str_data += "0000000";
    for (int i = 0; i < 29; i++) {
        bitset<8> tmp = bitset<8>(str_data.substr(i * 8, 8));
        /*std::cout << tmp.to_string() << endl;*/
        data[i] = static_cast<uint8_t>(tmp.to_ulong());
    }
    return data;
}

//ʹ��CRCѭ������У��(ʹ��CRCpp��)
void BIP(Header35& header35, InitialWord& iword, 
    ExtendWord& eword, ContinueWord& cword) {
    std::cout << "ִ����żУ��......" << endl;
    string str_data = header35.toString_15B() + iword.toString_70B() + eword.toString_70B() + cword.toString_70B();
    uint8_t* data = StrToCharArray(str_data);
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
    //std::cout << "iword_BIP = " << iword.getBIP() << endl;
    //std::cout << "eword_BIP = " << eword.getBIP() << endl;
    //std::cout << "cword_BIP = " << cword.getBIP() << endl;
    delete data;
}

void weave(symbol* symbol_RS_header, symbol* symbol_RS_iword,
    symbol* symbol_RS_eword, symbol* symbol_RS_cword) {
    std::cout << "ִ���ַ���֯......" << endl;
}

//15Symbol->31Symbol
//��RS������봦����Ϣ�֣�ʹ��schifra��
symbol* RS31_15(symbol* symbol_word) {
    std::cout << "======" << "��ʼִ��RS������� 15Symbol(60B) --> 31Symbol(124B)" << "======" << endl;
    for (int i = 0; i < 15; i++) {
        std::cout << "����ǰsymbol_word[" << i << "] = " << symbol_word[i].to_string() << endl;
    }

    string message(15, 0x00);
    for (int i = 0; i < 15; i++) {
        message[i] = static_cast<char>(symbol_word[i].to_ulong());
    }
    
    //cout << "ת�����symbol(�����Ʊ�ʾ): " << endl;
    //for (int i = 0; i < 15; i++) {
    //    for (int j = 7; j >= 0; j--) {
    //        cout << ((message[i] >> j) & 1);
    //    }
    //    cout << endl;
    //}

    symbol* symbol_RS_word = new symbol[31]();
    memset(symbol_RS_word, 0, sizeof(symbol) * 31);
    memcpy(symbol_RS_word, symbol_word, sizeof(symbol) * 15);

    if (!RS(31, 15, message, symbol_RS_word)) {
        std::cout << "RS����ɹ�" << endl;
    }
    else {
        std::cout << "RS����ʧ��" << endl;
    }
    for (int i = 0; i < 31; i++) {
        std::cout << "�����symbol_RS_word[" << i << "] = " << symbol_RS_word[i].to_string() << endl;
    }
    return symbol_RS_word;
}

//7Symbol->16Symbol
//��RS������봦����Ϣͷ��ʹ��schifra��
symbol* RS16_7(symbol* symbol_header) {
    std::cout << "======" << "��ʼִ��RS������� 7Symbol(28B) --> 15Symbol(60B)" << "======" << endl;
    for (int i = 0; i < 7; i++) {
        std::cout << "����ǰsymbol_header[" << i << "] = " << symbol_header[i].to_string() << endl;
    }

    string message(15, 0x00);
    for (int i = 0; i < 7; i++) {
        message[i] = static_cast<char>(symbol_header[i].to_ulong());
    }

    symbol* symbol_RS_header = new symbol[16]();
    memset(symbol_RS_header, 0, sizeof(symbol) * 16);
    memcpy(symbol_RS_header, symbol_header, sizeof(symbol) * 7);

    if (!RS(16, 7, message, symbol_RS_header)) {
        std::cout << "RS����ɹ�" << endl;
    }
    else {
        std::cout << "RS����ʧ��" << endl;
    }

    //��symbol_RS_header_temp�е�fec����
    for (int i = 0; i < 16; i++) {
        std::cout << "�����symbol_RS_header[" << i << "] = " << symbol_RS_header[i].to_string() << endl;
    }
    return symbol_RS_header;
}

int RS(const size_t codeLength, const size_t dataLength, string& message, symbol* symbol_msg) {
    /* Finite Field Parameters */
    const std::size_t field_descriptor                  = 5;
    const std::size_t generator_polynomial_index        = 0;
    const std::size_t generator_polynomial_root_count   = 16;

    /* Reed Solomon Code Parameters */
    const std::size_t code_length   = RS_Length::code_31_15; //(2^5 - 1)
    const std::size_t data_length   = RS_Length::data_31_15;
    const std::size_t fec_length    = RS_Length::fec_31_15;

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
    //��Symbol������message�е������������block���н��б��룬Ȼ�󽫱��������ݴ���block.data��(ǰ���ԭʼ���ݣ������FEC��)
    if (!encoder.encode(message, block))
    {
        std::cout << "Error - Critical encoding failure! "
            << "Msg: " << block.error_as_string() << std::endl;
        return 1;
    }

    //��ʽ��str_fec
    string str_fec(RS_Length::fec_31_15, 0x00);
    block.fec_to_string(str_fec);

    ////print
    //for (int i = 0; i < RS_Length::fec_31_15; i++) {
    //    for (int j = 7; j >= 0; j--) {
    //        std::cout << ((str_fec[i] >> j) & 1);
    //    }
    //    std::cout << std::endl;
    //}

    if (codeLength == RS_Length::code_31_15 && dataLength == RS_Length::data_31_15) {
        //Assemble(Word)
        for (int i = RS_Length::data_31_15; i < RS_Length::code_31_15; i++) {
            bitset<8> temp = bitset<8>(str_fec[i - RS_Length::data_31_15]);
            symbol_msg[i] = symbol(temp.to_string().substr(3, 5));
        }
    }

    else if (codeLength == RS_Length::code_16_7 && dataLength == RS_Length::data_16_7) {
        //Assemble(Header)������fec��ǰ7Symbol�ľ���λ
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

    //std::cout << "Encoder Parameters [" << schifra::reed_solomon::encoder<code_length, fec_length>::trait::code_length << ","
    //    << schifra::reed_solomon::encoder<code_length, fec_length>::trait::data_length << ","
    //    << schifra::reed_solomon::encoder<code_length, fec_length>::trait::fec_length << "]" << std::endl;

    //std::cout << "Decoder Parameters [" << schifra::reed_solomon::decoder<code_length, fec_length>::trait::code_length << ","
    //    << schifra::reed_solomon::decoder<code_length, fec_length>::trait::data_length << ","
    //    << schifra::reed_solomon::decoder<code_length, fec_length>::trait::fec_length << "]" << std::endl;
    return 0;
}

void handlerSTDP(Header35& Jheader, InitialWord& iword,
    ExtendWord& eword, ContinueWord& cword) {
    //ִ����żУ�飬70bit -> 75bit
    BIP(Jheader, iword, eword, cword);

    //Symbolת����Ȼ�����RS����
    symbol* symbol_header = Jheader.to_symbol();
    symbol* symbol_RS_header = RS16_7(symbol_header);

    symbol* symbol_iword = iword.to_symbol();
    symbol* symbol_RS_iword = RS31_15(symbol_iword);

    symbol* symbol_eword = eword.to_symbol();
    symbol* symbol_RS_eword = RS31_15(symbol_eword);

    symbol* symbol_cword = cword.to_symbol();
    symbol* symbol_RS_cword = RS31_15(symbol_cword);

    //TODO
    //��Ϣ����
    
    //��֯
    weave(symbol_RS_header, symbol_RS_iword, symbol_RS_eword, symbol_RS_cword);

    //TODO
    //���ʱ�侫ͬ�����ź�ʱ���ͬ������

    //����
    send_msg("һ��STDP��Ϣ");
    std::cout << "======���͵�STDP��Ϣ�������£�======\n"
        << Jheader.toString()
        << iword.toString()
        << eword.toString()
        << cword.toString() << endl;

    delete(symbol_header);
    symbol_header = nullptr;
    delete(symbol_RS_header);
    symbol_RS_header = nullptr;

    delete(symbol_iword);
    symbol_iword = nullptr;
    delete(symbol_RS_iword);
    symbol_RS_iword = nullptr;

    delete(symbol_eword);
    symbol_eword = nullptr;
    delete(symbol_RS_eword);
    symbol_RS_eword = nullptr;

    delete(symbol_cword);
    symbol_cword = nullptr;
    delete(symbol_RS_cword);
    symbol_RS_cword = nullptr;
}