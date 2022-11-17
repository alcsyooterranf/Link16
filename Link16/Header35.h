#pragma once
#include <bitset>
#include "dataType.h"

using namespace std;

//35bit��ͷ
class Header35 {
private:
    bitset<3>	m_type;	    //ʱ϶����(����涨���)
    bitset<1>	m_PR;		//���������ı�ʱ�����ڱ�ʶ���䲨����˫�����ַ����ǵ������ַ�
    bitset<15>	m_STN;	    //�ն�Դ�����ţ���ʱ����Ϣ�ķ���Դ���
    bitset<16>	m_SDU;	    //�������ݵ�Ԫ����ʶ���ܷ�ʽ

public:
    Header35(bitset<15>	STN) : m_type(bitset<3>("100")), m_PR(bitset<1>(0)),
        m_SDU(bitset<16>("0000100010001001")) {
        m_STN = STN;
    }

    Header35(bitset<3> type, bitset<1> PR, bitset<15>	STN) : m_SDU(bitset<16>("0000100010001001")) {
        m_type = type;
        m_PR = PR;
        m_STN = STN;
    }
    string toString();
    string toString_15B();
    symbol* to_symbol();
    void setType(bitset<3> type);
    void setPR(bitset<1> PR);
    bitset<15> getSTN();
    void setSTN(bitset<15> STN);
    void setSDU(bitset<16> SDU);
};