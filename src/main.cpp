#include <iostream>
#include "hls.h"

int main()
{
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8080);
    HLS hls(ep);
    return 0;
}
