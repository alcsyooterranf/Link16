#include <iostream>
#include <string>
#include <bitset>
#include "dataType.h"
#include "decodeTools.h"
#include "InitialWord.h"
#include "ExtendWord.h"
#include "ContinueWord.h"
#include "Header35.h"

using namespace std;

string getGroup(string& bit_data) {
	string str_header35 = bit_data.substr(0, 35);
	string type = str_header35.substr(0, 3);
	string group;
	if (type == "100") { //固定或可变STDP消息
		group = bit_data.substr(0, 260);
		bit_data.erase(0, 260);
	}
	//TODO：匹配其他消息

	return group;
}