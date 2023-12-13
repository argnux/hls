#pragma once

// Boost
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
using tcp = boost::asio::ip::tcp;

class HTTPServer {
public:
    HTTPServer(const tcp::endpoint& ep);

    int exec();

private:
    void read(tcp::socket& socket);
    void process_request(tcp::socket& socket);
    void write(tcp::socket& socket);

private:
    boost::asio::io_context context_;
    tcp::acceptor acceptor_;

    http::request<http::string_body> request_;
    http::response<http::string_body> response_;

    beast::flat_buffer buffer_;
    beast::error_code ec_;
};
