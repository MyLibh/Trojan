#pragma once

#ifndef __COMMANDMANGER_HPP_INCLUDED__
#define __COMMANDMANGER_HPP_INCLUDED__

#include "CommandProperties.hpp"

class CommandMessageProtocol;
using CMPROTO = CommandMessageProtocol;

class CommandManager
{
public:
	CommandManager();

	bool execute_command(const CMPROTO *msg);

private:
	std::vector<std::string> parse_args(const char *args);
	CIP_BITS                 get_bit(Commands command);
	bool                     get_bit_new_value(Commands command);

private:
	std::bitset<static_cast<size_t>(CIP_BITS::NUMBER_OF_BITS)> m_in_progress;
};

#endif /* __COMMANDMANGER_HPP_INCLUDED__ */