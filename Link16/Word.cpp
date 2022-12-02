//#include <iostream>
//#include <bitset>
//#include "tools.h"
//
////15Symbol->31Symbol
////用RS纠错编码处理消息字，使用schifra库
//template <RS_Length codeLength, RS_Length dataLength>
//void Word<codeLength, dataLength>::RS_handler() {
//	symbol* symbol_word = this->getS_word();
//	for (int i = 0; i < dataLength; i++) {
//		std::cout << "编码前symbol_word[" << i << "] = " << symbol_word[i].to_string() << endl;
//	}
//
//	string message(dataLength, 0x00);
//	for (int i = 0; i < dataLength; i++) {
//		message[i] = static_cast<char>(symbol_word[i].to_ulong());
//	}
//
//	//cout << "转换后的symbol(二进制表示): " << endl;
//	//for (int i = 0; i < dataLength; i++) {
//	//    for (int j = 7; j >= 0; j--) {
//	//        cout << ((message[i] >> j) & 1);
//	//    }
//	//    cout << endl;
//	//}
//
//	symbol* symbol_RS_word = this->getRS_word();
//	memset(symbol_RS_word, 0, sizeof(symbol) * codeLength);
//	memcpy(symbol_RS_word, symbol_word, sizeof(symbol) * dataLength);
//
//	if (!RS(codeLength, dataLength, message, symbol_RS_word)) {
//		std::cout << "RS编码成功" << endl;
//	}
//	else {
//		std::cout << "RS编码失败" << endl;
//	}
//	for (int i = 0; i < codeLength; i++) {
//		std::cout << "编码后symbol_RS_word[" << i << "] = " << symbol_RS_word[i].to_string() << endl;
//	}
//}
//
//template <RS_Length codeLength, RS_Length dataLength>
//void Word<codeLength, dataLength>::clear() {
//	memset(m_S_word, 0, sizeof(symbol) * dataLength);
//	memset(m_RS_word, 0, sizeof(symbol) * codeLength);
//}
//
//template <RS_Length codeLength, RS_Length dataLength>
//symbol* Word<codeLength, dataLength>::getS_word() {
//	return m_S_word;
//}
//
//template <RS_Length codeLength, RS_Length dataLength>
//symbol* Word<codeLength, dataLength>::getRS_word() {
//	return m_RS_word;
//}
//
//template <RS_Length codeLength, RS_Length dataLength>
//string Word<codeLength, dataLength>::toString_STDP() {
//	string res;
//	for (int i = 0; i < codeLength; i++) {
//		res += m_RS_word[i].to_string();
//	}
//	return res;
//}