#include "..\Service\pch.hpp"

#include "TCPConnection.hpp"
#include "Protocols\CommandMessageProtocol.hpp"
#include "..\Service\Debugger.hpp"

TCPConnection::TCPConnection(boost::asio::io_context &io_context) :
	m_io(io_context),
	m_socket(io_context),
	m_connected(false),
	m_read_msg(new CMPROTO),
	m_write_msgs()
{ }

TCPConnection::~TCPConnection()
{
	delete m_read_msg;
}

void TCPConnection::write(const CMPROTO *msg)
{
	boost::asio::post(m_io,
		[this, msg]()
		{
			bool write_in_progress = !m_write_msgs.empty();
			m_write_msgs.push_back(const_cast<CMPROTO*>(msg));
			if (!write_in_progress)
				write();
		});
}

void TCPConnection::close()
{
	boost::asio::post(m_io,
		[this]()
		{
			m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
			m_socket.close();

			m_connected = false;
		});
}

void TCPConnection::read_header()
{
	boost::asio::async_read(m_socket, boost::asio::buffer(m_read_msg->get_data(), CMPROTO::HEADER_LENGTH),
		[this](boost::system::error_code ec, size_t /* length */)
		{
			if (!ec && m_read_msg->decode_header())
				read_body();
			else
			{
				PrintBoostError(ec);

				close();
			}
		});
}

void TCPConnection::read_body()
{
	boost::asio::async_read(m_socket, boost::asio::buffer(m_read_msg->get_body(), m_read_msg->get_body_length()),
		[this](boost::system::error_code ec, size_t /* length */)
		{
			if (!ec)
			{
				std::cout << "========================RECEIVED MESSAGE========================" << std::endl;
				std::cout.write(m_read_msg->get_body(), m_read_msg->get_body_length());
				std::cout << "\n================================================================\n";

				m_read_msg->clear_data();

				read_header();
			}
			else
			{
				PrintBoostError(ec);

				close();
			}
		});
}

void TCPConnection::write()
{
	boost::asio::async_write(m_socket, boost::asio::buffer(m_write_msgs.front()->get_data(), m_write_msgs.front()->get_length()),
		[this](boost::system::error_code ec, size_t /* length */)
		{
			if (m_connected)
			{
				if (!ec)
				{
					m_write_msgs.pop_front();
					if (!m_write_msgs.empty())
						write();
				}
				else
				{
					PrintBoostError(ec);

					close();
				}
			}
		});
}
