// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\..\Service\pch.hpp"

#include "CommandMessageProtocol.hpp"

namespace detail
{
	[[nodiscard]]
	std::shared_ptr<CMPROTO> make_success_msg()
	{
		static constexpr std::string_view success = "SUCCESS";

		std::shared_ptr<CMPROTO> msg{ std::make_shared<CMPROTO>() };
		msg->set_body_length(success.length());

		std::copy(std::cbegin(success), std::cend(success), std::begin(msg->get_body()));

		msg->encode_header();

		return msg;
	}

	[[nodiscard]]
	std::shared_ptr<CMPROTO> make_failure_msg()
	{
		static constexpr std::string_view failure = "FAILURE";

		std::shared_ptr<CMPROTO> msg{ std::make_shared<CMPROTO>() };
		msg->set_body_length(failure.length());

		std::copy(std::cbegin(failure), std::cend(failure), std::begin(msg->get_body()));

		msg->encode_header();

		return msg;
	}
}

#pragma warning(push)
#pragma warning(disable : 26426)
	// C26462: Global initializer calls a non-constexpr function.
const std::shared_ptr<CMPROTO> CMPROTO_RESULT_SUCCESS = detail::make_success_msg();
const std::shared_ptr<CMPROTO> CMPROTO_RESULT_FAILURE = detail::make_failure_msg();
#pragma warning(pop)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
inline constexpr CommandMessageProtocol::CommandMessageProtocol() noexcept :
	m_data       { },
	m_body_length{ }
{ }

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CommandMessageProtocol::encode_header() 
{
	char header[HEADER_LENGTH + 1]{ };
	sprintf_s(header, "%4zd", m_body_length);

	const gsl::span span(header);
	std::copy(std::cbegin(span), std::cbegin(span) + CMPROTO::HEADER_LENGTH, std::begin(m_data));
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CommandMessageProtocol::decode_header() noexcept
{
	const auto header{ std::string_view{ m_data.data() }.substr(0, CMPROTO::HEADER_LENGTH) };

	m_body_length = atoi(header.data());
	if (m_body_length > MAX_BODY_LENGTH)
	{
		m_body_length = 0ull;

		return false;
	}

	return true;
}


