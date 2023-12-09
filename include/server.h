#pragma once

#include <string>
#include <iostream>
#include <algorithm>

// Boost
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
using namespace boost::placeholders;
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>

namespace ip = boost::asio::ip;
using tcp = ip::tcp;
using context_ptr = boost::shared_ptr<boost::asio::io_context>;

constexpr int max_sz = 1024;

class Server : public boost::enable_shared_from_this<Server>, boost::noncopyable {
    Server(context_ptr cont);
public:
    using server_ptr = boost::shared_ptr<Server>;
    using error_code = boost::system::error_code;

    void do_read();
    void do_write(const std::string& msg);
    void on_read(const error_code& err, size_t bytes);
    void on_write(const error_code& err, size_t bytes);
    size_t read_complete(const error_code& err, size_t bytes);
    void start();
    void stop();

    static server_ptr new_(context_ptr cont);

    ip::tcp::socket& sock();

private:
    context_ptr m_context;
    tcp::socket m_sock;
    bool m_isStarted;
    char m_readBuf[max_sz];
    char m_writeBuf[max_sz];
};
