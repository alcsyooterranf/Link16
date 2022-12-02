#pragma once
#include "dataType.h"
#include <iostream>

template <RS_Length codeLength, RS_Length dataLength>
class Word {
public:
	symbol* m_S_word;      //symbolת�����Word
	symbol* m_RS_word;     //RS������Word

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

	//��RS������봦����Ϣ�֣�ʹ��schifra��
	void RS_handler() {
		symbol* symbol_word = this->getS_word();
		std::cout << "����ǰsymbol_word = " << std::endl;
		for (int i = 0; i < dataLength; i++) {
			std::cout << symbol_word[i].to_string();
		}
		std::cout << std::endl;

		string message(dataLength, 0x00);
		for (int i = 0; i < dataLength; i++) {
			message[i] = static_cast<char>(symbol_word[i].to_ulong());
		}

		std::cout << "RS����ǰת�����symbol(�����Ʊ�ʾ): " << std::endl;
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
			std::cout << "RS����ɹ�" << std::endl;
		}
		else {
			std::cout << "RS����ʧ��" << std::endl;
		}
		std::cout << "�����symbol_RS_word = " << std::endl;
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