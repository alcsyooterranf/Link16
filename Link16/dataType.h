#pragma once
#pragma pack(1)
#include <bitset>

using namespace std;

typedef short		int16_t;	//16λ������
typedef int			int32_t;	//32λ������
typedef long long	int64_t;	//64λ������

typedef unsigned char		uint8_t;	//8λ�޷�������
typedef unsigned short		uint16_t;	//16λ�޷�������
typedef unsigned int		uint32_t;	//32λ�޷�������
typedef unsigned long long	uint64_t;	//64λ�޷�������

typedef bitset<5>	symbol;		//5bit = 1Symbol

//35bit��ͷ
struct header_35 {
	bitset<3>	type;	//ʱ϶����
	bitset<1>	PR;		//���������ı�ʱ�����ڱ�ʶ���䲨����˫�����ַ����ǵ������ַ�
	bitset<15>	STN;	//�ն�Դ�����ţ���ʱ����Ϣ�ķ���Դ���
	bitset<16>	SDU;	//�������ݵ�Ԫ����ʶ���ܷ�ʽ
};

//Jϵ����Ϣ˳�򣺳�ʼ�� ---> ��չ�� ---> ������
//75bit��ʼ��
struct initial_word {
	bitset<2>	format;		//�ָ�ʽ����ʼ��Ϊ00
	bitset<5>	signal;		//��ʶ
	bitset<3>	sub_signal;	//�ӱ�ʶ
	bitset<3>	length;		//��Ϣ���ȣ���ʾ��ʼ�ֺ������չ�ֻ�����ֵ����������7��
	bitset<57>	message;	//��Ϣ��
	bitset<5>	BIP;		//��żУ�飬��һλ���У�����λִ��У��
};

//75bit��չ�֣����밴˳����
struct extend_word {
	bitset<2>	format;		//�ָ�ʽ����չ��Ϊ10
	bitset<68>	message;	//��Ϣ��
	bitset<5>	BIP;		//��żУ�飬��һλ���У�����λִ��У��
};

//75bit�����֣����Բ���˳����
struct continue_word {
	bitset<2>	format;		//�ָ�ʽ��������Ϊ01
	bitset<5>	signal;		//�����ֱ�ʶ��ÿ��Jϵ����Ϣ���������32��������
	bitset<63>	message;	//��Ϣ��
	bitset<5>	BIP;		//��żУ�飬��һλ���У�����λִ��У��
};