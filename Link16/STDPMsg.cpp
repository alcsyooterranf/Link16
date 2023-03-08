#include "STDPMsg.h"

HeaderWord* STDPMsg::getHeaderWord() {
	return m_headerword;
}

InitialWord* STDPMsg::getInitialWord() {
	return m_iword;
}

ExtendWord* STDPMsg::getExtendWord() {
	return m_eword;
}

ContinueWord* STDPMsg::getContinueWord() {
	return m_cword;
}

void STDPMsg::setRawMsg(string& raw_msg) {
	m_raw_msg = raw_msg;
}

void STDPMsg::setBitMsg(string& bit_msg) {
	m_bit_msg = bit_msg;
}

void STDPMsg::setHeaderWord(string& bit_data) {
	m_headerword->rewrite(bit_data);
}

void STDPMsg::setInitialWord(string& bit_data) {
	m_iword->rewrite(bit_data);
}

void STDPMsg::setExtendWord(string& bit_data) {
	m_eword->rewrite(bit_data);
}

void STDPMsg::setContinueWord(string& bit_data) {
	m_cword->rewrite(bit_data);
}

void STDPMsg::clear() {
	m_raw_msg.clear();
	m_bit_msg.clear();
	m_headerword->clear();
	m_iword->clear();
	m_eword->clear();
	m_cword->clear();
}