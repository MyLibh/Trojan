// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\..\Service\pch.hpp"

#include "CommandMessageProtocol.hpp"

namespace detail
{
	[[nodiscard]]
	CMPROTO make_success_msg() 
	{
		static constexpr std::string_view success = "SUCCESS";

		CMPROTO msg;
		msg.set_body_length(success.length());
		std::copy(std::cbegin(success), std::cend(success), std::begin(msg.get_body()));
		msg.encode_header();

		return msg;
	}

	[[nodiscard]]
	CMPROTO make_failure_msg() 
	{
		static constexpr std::string_view failure = "FAILURE";

		CMPROTO msg;
		msg.set_body_length(failure.length());
		std::copy(std::cbegin(failure), std::cend(failure), std::begin(msg.get_body()));
		msg.encode_header();

		return msg;
	}
}

#pragma warning(push)
#pragma warning(disable : 26426)
	// C26462: Global initializer calls a non-constexpr function.
const CMPROTO CMPROTO_RESULT_SUCCESS = detail::make_success_msg();
const CMPROTO CMPROTO_RESULT_FAILURE = detail::make_failure_msg();
#pragma warning(pop)

CommandMessageProtocol::CommandMessageProtocol() noexcept :
	m_body_length{ },
	m_data{ }
{ }

void CommandMessageProtocol::encode_header() 
{
	char header[HEADER_LENGTH + 1]{ };
	sprintf_s(header, "%4zd", m_body_length);
	std::copy(std::crbegin(header), std::crbegin(header) + CMPROTO::HEADER_LENGTH, m_data);
}

bool CommandMessageProtocol::decode_header() noexcept
{
	char header[HEADER_LENGTH + 1]{ };
	strncat_s(header, m_data, HEADER_LENGTH);

	m_body_length = atoi(&header[HEADER_LENGTH + 1]);
	if (m_body_length > MAX_BODY_LENGTH)
	{
		m_body_length = 0;

		return false;
	}

	return true;
}


