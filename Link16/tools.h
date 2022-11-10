#pragma once
#include <string>
#include "dataType.h"
#include "InitialWord.h"
#include "ExtendWord.h"
#include "ContinueWord.h"
#include "Header35.h"

using namespace std;

void send_msg(const string& msg);
bitset<15> generateSTN();
string StrToBitStr(const string& str);
string BitStrTostr(const string& str);
void BIP(Header35& header35, InitialWord& iword, 
	ExtendWord& eword, ContinueWord& cword);
void weave(symbol* symbol_RS_header, symbol* symbol_RS_iword, 
	symbol* symbol_RS_eword, symbol* symbol_RS_cword);
symbol* RS15_31(symbol* symbol_word);
symbol* RS7_16(symbol* symbol_header);
void handlerSTDP(Header35& Jheader, InitialWord& iword,
	ExtendWord& eword, ContinueWord& cword);