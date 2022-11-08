#pragma once

void send_msg(const string& msg);
bitset<15> generateSTN();
string StrToBitStr(const string& str);
string BitStrTostr(const string& str);
void BIP();
void weave();
header_35 generate_J_header(bitset<15> STN);

symbol* word_to_symbol(initial_word bit_word);
symbol* word_to_symbol(extend_word bit_word);
symbol* word_to_symbol(continue_word bit_word);
symbol* header_to_symbol(header_35 bit_word);
symbol* RS15_31(symbol* symbol_word);
symbol* RS7_16(symbol* symbol_header);