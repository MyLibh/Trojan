// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\..\Service\pch.hpp"

#include "CommandMessageProtocol.hpp"

namespace detail
{
	[[nodiscard]]
	CMPROTO make_success_msg() noexcept
	{
		static constexpr std::string_view success = "SUCCESS";

		CMPROTO msg;
		msg.set_body_length(success.length());
		std::memcpy(msg.get_body().data(), success.data(), msg.get_body_length());
		msg.encode_header();

		return msg;
	}

	[[nodiscard]]
	CMPROTO make_failure_msg() noexcept
	{
		static constexpr std::string_view failure = "FAILURE";

		CMPROTO msg;
		msg.set_body_length(failure.length());
		std::memcpy(msg.get_body().data(), failure.data(), msg.get_body_length());
		msg.encode_header();

		return msg;
	}
}

#pragma warning(push)
#pragma warning(disable : 26426)

const CMPROTO CMPROTO_RESULT_SUCCESS = detail::make_success_msg();
const CMPROTO CMPROTO_RESULT_FAILURE = detail::make_failure_msg();

#pragma warning(pop)

CommandMessageProtocol::CommandMessageProtocol() noexcept :
	m_body_length{ },
	m_data{ }
{ }

void CommandMessageProtocol::encode_header() noexcept
{
	char header[HEADER_LENGTH + 1]{ };
	sprintf_s(header, "%4d", gsl::narrow<int>(m_body_length));
	std::memcpy(m_data, header, HEADER_LENGTH);
}

bool CommandMessageProtocol::decode_header() noexcept
{
	char header[HEADER_LENGTH + 1]{ };
	strncat_s(header, m_data, HEADER_LENGTH);

	m_body_length = std::atoi(header);
	if (m_body_length > MAX_BODY_LENGTH)
	{
		m_body_length = 0;

		return false;
	}

	return true;
}


