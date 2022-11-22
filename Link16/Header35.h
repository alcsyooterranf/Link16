#pragma once
#include <bitset>
#include "dataType.h"

using namespace std;

//35bit��ͷ
class Header35 {
private:
    bitset<3>	m_type;	        //ʱ϶����(����涨���)
    bitset<1>	m_PR;		    //���������ı�ʱ�����ڱ�ʶ���䲨����˫�����ַ����ǵ������ַ�
    bitset<15>	m_STN;	        //�ն�Դ�����ţ���ʱ����Ϣ�ķ���Դ���
    bitset<16>	m_SDU;	        //�������ݵ�Ԫ����ʶ���ܷ�ʽ(Ŀǰ��ʱԼ����ǰ8λ��ʾ���ܷ�ʽ����8λ��λ11001010)
                                //AES:00001010  DES:00001011    RSA:00001111

    symbol*     m_S_Header;     //symbolת�����Header
    symbol*     m_RS_Header;    //RS������Header

public:
    Header35(bitset<15>	STN) : m_type(bitset<3>("100")), m_PR(bitset<1>(0)),
        m_SDU(bitset<16>("0000101011001010")) {
        m_STN = STN;
        m_S_Header = new symbol[7]();
        m_RS_Header = new symbol[16]();
    }

    Header35(bitset<3> type, bitset<1> PR, bitset<15>	STN) : m_SDU(bitset<16>("0000101011001010")) {
        m_type = type;
        m_PR = PR;
        m_STN = STN;
        m_S_Header = new symbol[7];
        m_RS_Header = new symbol[16];
    }

    ~Header35()
    {
        delete[] m_S_Header;
        delete[] m_RS_Header;
    }

    void RS16_7();
    void rewrite(string& bit_str);
    void show();
    string toString();
    string toString_15B();
    string toString_STDP();
    void to_symbol();
    void setType(bitset<3> type);
    void setPR(bitset<1> PR);
    bitset<15> getSTN();
    bitset<16> getSDU();
    void setSTN(bitset<15> STN);
    void setSDU(bitset<16> SDU);
    symbol* getS_Header();
    symbol* getRS_Header();
};