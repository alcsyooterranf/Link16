#include <iostream>
#include <bitset>
#include <algorithm>
#include "interface.h"

#define SENDING
#ifdef SENDING
int main()
{
	string msg = "！！！This is a warning message.";
	int err_conde = encoder_Link16(15, 0, msg);
}
#endif // SENDING

#ifdef RECIEVING
#include "STDPMsg.h"

int main()
{
	string raw_msg;
	int n, m;
	int err_code = decoder_Link16(raw_msg, n, m);
	std::cout << "消息数据长度为：" << raw_msg.length() << std::endl;
	std::cout << "接收到的消息为：" << raw_msg << std::endl;
	std::cout << "解码后的消息为：" << Tools::BitStrTostr(raw_msg) << std::endl;
	std::cout << "消息为类型为：" << "J" << n << "." << m << std::endl;
}
#endif // RECIEVING

#ifdef DEBUG
int main() {
}
#endif // DEBUG