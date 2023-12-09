#pragma once

#include "server.h"

// Boost
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
using namespace boost::placeholders;

class HLS {
public:
    HLS(const ip::tcp::endpoint& ep);

    void handle_accept(Server::server_ptr client, const Server::error_code& err);

private:
    context_ptr m_context;
    ip::tcp::acceptor m_acceptor;
};
