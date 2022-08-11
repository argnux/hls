#include "server.h"

Server::Server(context_ptr cont)
    : m_context(cont), m_sock(m_context->get_executor()), m_isStarted(false)
{
}

void Server::start()
{
    m_isStarted = true;
    do_read();
}

Server::server_ptr Server::new_(context_ptr cont)
{
    server_ptr ptr{new Server(cont)};
    return ptr;
}

ip::tcp::socket& Server::sock()
{
    return m_sock;
}

void Server::stop()
{
    if (!m_isStarted)
        return;
    
    m_isStarted = false;
    m_sock.close();
}

void Server::on_read(const error_code& err, size_t bytes)
{
    if (!err) {
        std::string msg(m_readBuf, bytes);
        std::cout << "Message is '" << msg << "'" << std::endl; // FIXME remove logs
        do_write(msg);
    }
    stop();
}

void Server::on_write(const error_code& err, size_t bytes)
{
    do_read();
}

void Server::do_read()
{
    boost::asio::async_read(m_sock, boost::asio::buffer(m_readBuf),
                            boost::bind(&Server::read_complete, shared_from_this(), _1, _2),
                            boost::bind(&Server::on_read, shared_from_this(), _1, _2));
}

void Server::do_write(const std::string& msg)
{
    if (!m_isStarted)
        return;
    std::copy(msg.begin(), msg.end(), m_writeBuf);
    m_sock.async_write_some(boost::asio::buffer(m_writeBuf, msg.size()), boost::bind(&Server::on_write, shared_from_this(), _1, _2));
}

size_t Server::read_complete(const error_code& err, size_t bytes)
{
    if (err)
        return 0;

	bool found = std::find(m_readBuf, m_readBuf + bytes, '\n') < m_readBuf + bytes;
	return found ? 0 : 1;
}
