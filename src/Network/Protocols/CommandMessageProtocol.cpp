// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\..\Service\pch.hpp"

#include "CommandMessageProtocol.hpp"
#include "..\..\Service\Log.hpp"

/*************************************************************************************************************************************************************************************************************/
inline constexpr CommandMessageProtocol::CommandMessageProtocol() noexcept :
	m_data       { },
	m_body_length{ }
{ }

/*************************************************************************************************************************************************************************************************************/
void CommandMessageProtocol::encode_header() 
{
	static auto header_fmt{ boost::format("%4llu") };

	std::string header{ boost::str(header_fmt % m_body_length) };
	std::copy(std::cbegin(header), std::cend(header), std::begin(m_data));
}

/*************************************************************************************************************************************************************************************************************/
bool CommandMessageProtocol::decode_header() noexcept
{
	const auto header{ std::string_view{ m_data.data() }.substr(0, CMPROTO::HEADER_LENGTH) };

	m_body_length = std::atoi(header.data());
	if (m_body_length > MAX_BODY_LENGTH)
	{
		LOG(trace) << "m_body_length > MAX_BODY_LENGTH(" << m_body_length << ')';

		m_body_length = 0ull;

		return false;
	}

	return true;
}

/*************************************************************************************************************************************************************************************************************/
[[nodiscard]]
std::unique_ptr<CMPROTO> make_success_msg()
{
	static constexpr std::string_view success = "SUCCESS";

	std::unique_ptr<CMPROTO> msg{ std::make_unique<CMPROTO>() };
	msg->set_body_length(success.length());

	std::copy(std::cbegin(success), std::cend(success), std::begin(msg->get_body()));

	msg->encode_header();

	return msg;
}

/*************************************************************************************************************************************************************************************************************/
[[nodiscard]]
std::unique_ptr<CMPROTO> make_failure_msg()
{
	static constexpr std::string_view failure = "FAILURE";

	std::unique_ptr<CMPROTO> msg{ std::make_unique<CMPROTO>() };
	msg->set_body_length(failure.length());

	std::copy(std::cbegin(failure), std::cend(failure), std::begin(msg->get_body()));

	msg->encode_header();

	return msg;
}
