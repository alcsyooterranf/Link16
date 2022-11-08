#pragma once
#include "tools.h"

void handler_initial_word(string& bit_data, void (*send_msg)(const string& msg));
void handler_extend_word(string& bit_data, void (*send_msg)(const string& msg));
void handler_continue_word(string& bit_data, void (*send_msg)(const string& msg));
void handler_header(header_35 header, void (*send_msg)(const string& msg));