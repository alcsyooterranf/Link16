#pragma once
#include "tools.h"
#include "global.h"

#include "decodeTools.h"
#include "STDPMsg.h"

int32_t encoder_Link16(int32_t n, int32_t m, string& inputs);
int32_t decoder_Link16(string& raw_data, int32_t& n, int32_t& m);