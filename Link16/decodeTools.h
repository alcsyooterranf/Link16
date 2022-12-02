#pragma once
#include <string>
#include "dataType.h"
#include "InitialWord.h"
#include "ExtendWord.h"
#include "ContinueWord.h"
#include "HeaderWord.h"
#include "tools.h"

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

string getGroup(string& bit_data);
void StrToSymbol(symbol* stdp, size_t length, string& message);
string decode_weave(string& raw_msg);
string decode_RS_code_16_7(symbol* head);
string decode_RS_code_31_15(symbol* head);
string decode_RS_AES_BIP_handler(string& message);
int decode_RS(string& message, string& str_data);
string AES_decrypt(string& char_data);