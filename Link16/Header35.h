#pragma once
#include <bitset>
#include "tools.h"

using namespace std;

//35bit��ͷ
class Header35 {
private:
    bitset<3>	m_type;	    //ʱ϶����
    bitset<1>	m_PR;		//���������ı�ʱ�����ڱ�ʶ���䲨����˫�����ַ����ǵ������ַ�
    bitset<15>	m_STN;	    //�ն�Դ�����ţ���ʱ����Ϣ�ķ���Դ���
    bitset<16>	m_SDU;	    //�������ݵ�Ԫ����ʶ���ܷ�ʽ

public:
    Header35(bitset<15>	STN) : m_type(bitset<3>("001")), m_PR(bitset<1>(0)),
        m_SDU(bitset<16>("0000100010001001")) {
        m_STN = STN;
    }
    string toString();
    symbol* to_symbol();
};