#pragma once

#ifndef __COMMANDMANGER_HPP_INCLUDED__
#define __COMMANDMANGER_HPP_INCLUDED__

#include "CommandProperties.hpp"

class CommandMessageProtocol;
using CMPROTO = CommandMessageProtocol;

class CommandManager
{
public:
	static bool execute_command(std::weak_ptr<CMPROTO> msg, boost::asio::io_context &io_context, const boost::asio::ip::udp::endpoint &endpoint);

private:
	static std::vector<std::string> parse_args(const char *args);
	static CIP_BITS                 get_bit(Commands command);
	static bool                     get_bit_new_value(Commands command);

private:
	static cip_t m_in_progress;
};

#endif /* __COMMANDMANGER_HPP_INCLUDED__ */