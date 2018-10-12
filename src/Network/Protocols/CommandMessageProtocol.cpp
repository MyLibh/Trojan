#include "..\..\Service\pch.hpp"

#include "CommandMessageProtocol.hpp"

namespace detail
{
	CMPROTO make_success_msg()
	{
		static const char *line = "SUCCESS";
		static constexpr size_t length = 8;

		CMPROTO msg;
		msg.set_body_length(length);
		std::memcpy(msg.get_body(), line, msg.get_body_length());
		msg.encode_header();

		return msg;
	}

	CMPROTO make_failure_msg()
	{
		static const char *line = "FAILURE";
		static constexpr size_t length = 8;

		CMPROTO msg;
		msg.set_body_length(length);
		std::memcpy(msg.get_body(), line, msg.get_body_length());
		msg.encode_header();

		return msg;
	}

}

const CMPROTO CMPROTO_RESULT_SUCCESS = detail::make_success_msg();
const CMPROTO CMPROTO_RESULT_FAILURE = detail::make_failure_msg();

CommandMessageProtocol::CommandMessageProtocol() :
	m_body_length(0ull),
	m_data("")
{ }

void CommandMessageProtocol::encode_header()
{
	char header[HEADER_LENGTH + 1] = "";
	sprintf_s(header, "%4d", static_cast<int>(m_body_length));
	std::memcpy(m_data, header, HEADER_LENGTH);
}

bool CommandMessageProtocol::decode_header()
{
	char header[HEADER_LENGTH + 1] = "";
	strncat_s(header, m_data, HEADER_LENGTH);

	m_body_length = std::atoi(header);
	if (m_body_length > MAX_BODY_LENGTH)
	{
		m_body_length = 0;

		return false;
	}

	return true;
}

