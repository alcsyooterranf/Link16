#include <iostream>
#include <bitset>
#include <algorithm>
#include "tools.h"

#define SENDING
#ifdef SENDING
int main()
{
	string msg = "hello, this is a test message.";
	int err_conde = encoder_Link16(0, 1, msg);
}
#endif // SENDING

#ifdef RECIEVING
#include "decodeTools.h"
#include "STDPMsg.h"

int main()
{
	int err_code = decoder_Link16();
}
#endif // RECIEVING

#ifdef DEBUG
int main() {
}
#endif // DEBUG