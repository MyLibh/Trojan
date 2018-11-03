#pragma once

#ifndef __UDPPARTICIPIANT_HPP_INCLUDED__
#define __UDPPARTICIPIANT_HPP_INCLUDED__

class CommandMessageProtocol;
using CMPROTO = CommandMessageProtocol;

class ImageMessageProtocol;
using IMPROTO = ImageMessageProtocol;

class UDPParticipiant : private boost::noncopyable
{ 
public:
	inline static constexpr std::string_view OK_MESSAGE{ "OK" };

	UDPParticipiant(boost::asio::io_context &io_context, const boost::asio::ip::udp::endpoint &endpoint);

	void send(std::unique_ptr<CMPROTO> &&msg);
	void recv(std::unique_ptr<CMPROTO> &msg);

	void send(const std::shared_ptr<IMPROTO> &msg);
	void recv(const std::shared_ptr<IMPROTO> &msg);

protected:
	boost::asio::ip::udp::socket   m_socket;
	boost::asio::ip::udp::endpoint m_endpoint;
};

#endif /* __UDPPARTICIPIANT_HPP_INCLUDED__ */