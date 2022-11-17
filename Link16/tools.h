#pragma once
#include <string>
#include "dataType.h"
#include "InitialWord.h"
#include "ExtendWord.h"
#include "ContinueWord.h"
#include "Header35.h"

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
bitset<15> generateSTN();
string StrToBitStr(const string& str);
string BitStrTostr(const string& str);
uint8_t* StrToCharArray(string& str_data);
void BIP(Header35& header35, InitialWord& iword, 
	ExtendWord& eword, ContinueWord& cword);
void weave(symbol* symbol_RS_header, symbol* symbol_RS_iword, 
	symbol* symbol_RS_eword, symbol* symbol_RS_cword);
symbol* RS31_15(symbol* symbol_word);
symbol* RS16_7(symbol* symbol_header);
void handlerSTDP(Header35& Jheader, InitialWord& iword,
	ExtendWord& eword, ContinueWord& cword);
int RS(const size_t codeLength, const size_t dataLength, string& message, symbol* symbol_RS_word);
