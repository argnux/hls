#include "hls.h"

HLS::HLS(const ip::tcp::endpoint& ep)
    : m_context(new boost::asio::io_context), m_acceptor(m_context->get_executor(), ep)
{
    Server::server_ptr new_client = Server::new_(m_context);
    m_acceptor.async_accept(new_client->sock(), boost::bind(&HLS::handle_accept, this, new_client, _1));
    m_context->run();
}

void HLS::handle_accept(Server::server_ptr client, const Server::error_code& err)
{
    client->start();
    Server::server_ptr new_client = Server::new_(m_context);
    m_acceptor.async_accept(new_client->sock(), boost::bind(&HLS::handle_accept, this, new_client, _1));
}
