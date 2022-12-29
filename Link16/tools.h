#pragma once
#include <string>
#include "Word.hpp"
#include "InitialWord.h"
#include "ExtendWord.h"
#include "ContinueWord.h"
#include "HeaderWord.h"
#include "CRC.h"
#include "AES.h"
#include "md5.h"
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

void save_msg(const string& msg);
bool deleteFile();
string generateBIN(int length);
vector<string> stringSplit(const string& str, char delim);
string StrToBitStr(const string& str);
string BitStrTostr(const string& str);
uint8_t* StrToCharArray(string& str_data, int char_length);
void BIP(HeaderWord& hword, InitialWord& iword,
	ExtendWord& eword, ContinueWord& cword);
void AES_Encrypt(HeaderWord& hword, InitialWord& iword,
	ExtendWord& eword, ContinueWord& cword);
void weave(HeaderWord& hword, InitialWord& iword,
	ExtendWord& eword, ContinueWord& cword);
void handlerSTDP(HeaderWord& hword, InitialWord& iword,
	ExtendWord& eword, ContinueWord& cword);
int RS(const size_t codeLength, const size_t dataLength, string& message, symbol* symbol_RS_word);