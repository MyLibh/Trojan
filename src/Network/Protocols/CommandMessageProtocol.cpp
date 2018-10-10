#include "..\..\Service\pch.hpp"

#include "CommandMessageProtocol.hpp"

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

