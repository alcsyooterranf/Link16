#pragma once
#include <string>
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

enum RS_Length
{
    code_16_7   = 16,
    data_16_7   = 7,
    fec_16_7    = 9,
    code_31_15  = 31,
    data_31_15  = 15,
    fec_31_15   = 16,
};

void send_msg(const string& msg);
string generateBIN(int length);
string StrToBitStr(const string& str);
string BitStrTostr(const string& str);
uint8_t* StrToCharArray(string& str_data, int char_length);
void BIP(Header35& header35, InitialWord& iword, 
	ExtendWord& eword, ContinueWord& cword);
void AES_Encrypt(Header35& header35, InitialWord& iword,
    ExtendWord& eword, ContinueWord& cword);
void weave(Header35& header35, InitialWord& iword,
    ExtendWord& eword, ContinueWord& cword);
void handlerSTDP(Header35& Jheader, InitialWord& iword,
	ExtendWord& eword, ContinueWord& cword);
int RS(const size_t codeLength, const size_t dataLength, string& message, symbol* symbol_RS_word);
