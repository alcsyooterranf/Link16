#include "STDPMsg.h"

void STDPMsg::setRawMsg(string& raw_msg) {
	m_raw_msg = raw_msg;
}

void STDPMsg::setBitMsg(string& bit_msg) {
	m_bit_msg = bit_msg;
}

void STDPMsg::clear() {
	m_raw_msg.clear();
	m_bit_msg.clear();
	m_headerword->clear();
	m_iword->clear();
	m_eword->clear();
	m_cword->clear();
}