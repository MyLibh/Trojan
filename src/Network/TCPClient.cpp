#include "..\pch.hpp"

#include "TCPClient.hpp"

TCPClient::TCPClient(boost::asio::io_context &io_context, const boost::asio::ip::tcp::resolver::results_type &cr_endpoints) :
	m_io(io_context),
	m_socket(io_context),
	m_read_msg(),
	m_write_msgs()
{
	connect(cr_endpoints);
}

void TCPClient::write(const CMPROTO &cr_message)
{
	boost::asio::post(m_io, 
		[this, cr_message]()
		{
			bool write_in_progress = !m_write_msgs.empty();
			m_write_msgs.push_back(cr_message);
			if (!write_in_progress)
				write();
		});
}

void TCPClient::close()
{
	boost::asio::post(m_io,
		[this]()
		{
			m_socket.close();
		});
}

void TCPClient::connect(const boost::asio::ip::tcp::resolver::results_type & cr_endpoints)
{
	boost::asio::async_connect(m_socket, cr_endpoints,
		[this](boost::system::error_code ec, boost::asio::ip::tcp::endpoint /* endpoint */)
		{
			if (!ec)
				read_header();
		});
}

void TCPClient::read_header()
{
	boost::asio::async_read(m_socket, boost::asio::buffer(m_read_msg.get_data(), CMPROTO::HEADER_LENGTH),
		[this](boost::system::error_code ec, size_t /* length*/)
		{
			if (!ec && m_read_msg.decode_header())
				read_body();
			else
				m_socket.close();
		});
}

void TCPClient::read_body()
{
	boost::asio::async_read(m_socket, boost::asio::buffer(m_read_msg.get_data(), m_read_msg.get_body_length()),
		[this](boost::system::error_code ec, size_t /* length*/)
	{
		if (!ec)
		{
			std::cout << "========================RECEIVED MESSAGE========================" << std::endl;
			std::cout.write(m_read_msg.get_body(), m_read_msg.get_body_length());
			std::cout << "\n================================================================\n";

			read_header();
		}
		else
			m_socket.close();
	});
}

void TCPClient::write()
{
	boost::asio::async_write(m_socket, boost::asio::buffer(m_write_msgs.front().get_data(), m_write_msgs.front().get_length()),
		[this](boost::system::error_code ec, size_t /* length*/)
		{
			if (!ec)
			{
				m_write_msgs.pop_front();
				if (!m_write_msgs.empty())
					write();
			}
			else
				m_socket.close();
		});
}
