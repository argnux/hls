#include "server.h"

int main()
{
    tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 8080);
    HTTPServer server{ep};

    return server.exec();
}
