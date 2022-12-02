#pragma once
#include "dataType.h"
#include <iostream>

template <RS_Length codeLength, RS_Length dataLength>
class Word {
public:
	symbol* m_S_word;      //symbol转换后的Word
	symbol* m_RS_word;     //RS编码后的Word

	Word() {
		m_S_word = new symbol[dataLength]();
		m_RS_word = new symbol[codeLength]();
	}

	virtual ~Word()
	{
		delete[] m_S_word;
		m_S_word = nullptr;
		delete[] m_RS_word;
		m_RS_word = nullptr;
	}

	//用RS纠错编码处理消息字，使用schifra库
	void RS_handler() {
		symbol* symbol_word = this->getS_word();
		std::cout << "编码前symbol_word = " << std::endl;
		for (int i = 0; i < dataLength; i++) {
			std::cout << symbol_word[i].to_string();
		}
		std::cout << std::endl;

		string message(dataLength, 0x00);
		for (int i = 0; i < dataLength; i++) {
			message[i] = static_cast<char>(symbol_word[i].to_ulong());
		}

		std::cout << "RS编码前转换后的symbol(二进制表示): " << std::endl;
		for (int i = 0; i < dataLength; i++) {
			for (int j = 7; j >= 0; j--) {
				std::cout << ((message[i] >> j) & 1);
			}
		}
		std::cout << std::endl;

		symbol* symbol_RS_word = this->getRS_word();
		memset(symbol_RS_word, 0, sizeof(symbol) * codeLength);
		memcpy(symbol_RS_word, symbol_word, sizeof(symbol) * dataLength);

		if (!RS(codeLength, dataLength, message, symbol_RS_word)) {
			std::cout << "RS编码成功" << std::endl;
		}
		else {
			std::cout << "RS编码失败" << std::endl;
		}
		std::cout << "编码后symbol_RS_word = " << std::endl;
		for (int i = 0; i < codeLength; i++) {
			std::cout << symbol_RS_word[i].to_string();
		}
		std::cout << std::endl;
	}

	virtual void clear() {
		memset(m_S_word, 0, sizeof(symbol) * dataLength);
		memset(m_RS_word, 0, sizeof(symbol) * codeLength);
	}

	string toString_STDP() {
		string res;
		for (int i = 0; i < codeLength; i++) {
			res += m_RS_word[i].to_string();
		}
		return res;
	}

	symbol* getS_word() {
		return m_S_word;
	}

	symbol* getRS_word() {
		return m_RS_word;
	}
	virtual void rewrite(string& bit_str) = 0;
	virtual void to_symbol() = 0;
	virtual string toString() = 0;
};