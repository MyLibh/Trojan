#pragma once

#ifndef __COMMANDMESSAGEPROTOCOL_HPP_INCLUDED__
#define __COMMANDMESSAGEPROTOCOL_HPP_INCLUDED__

namespace gsl
{
	template<typename auto _Size>
	span(std::array<char, _Size>&)->span<char, _Size>;

	template<typename auto _Size>
	span(const std::array<char, _Size>&)->span<const char, _Size>;
}

class CommandMessageProtocol
{
public:
	inline static constexpr std::size_t HEADER_LENGTH   = 4; 
	inline static constexpr std::size_t COMMAND_LENGTH  = 2;
	inline static constexpr std::size_t SPACE_LENGTH    = 1;
	inline static constexpr std::size_t MAX_ARGS_LENGTH = 128;
	inline static constexpr std::size_t MAX_BODY_LENGTH = COMMAND_LENGTH + SPACE_LENGTH + MAX_ARGS_LENGTH;
	inline static constexpr std::size_t MAX_LENGTH      = HEADER_LENGTH + MAX_BODY_LENGTH;

	using buffer_t = std::array<char, MAX_LENGTH>;

public:
	inline constexpr CommandMessageProtocol() noexcept;
	 

	[[nodiscard]] inline       auto   get_data()              noexcept { return (gsl::span{ m_data }); }
	[[nodiscard]] inline const auto   get_data()        const noexcept { return (gsl::span{ m_data }); }
	[[nodiscard]] inline       auto   get_body()              noexcept { return (gsl::span{ m_data }.subspan<HEADER_LENGTH>()); }
	[[nodiscard]] inline const auto   get_body()        const noexcept { return (gsl::span{ m_data }.subspan<HEADER_LENGTH>()); }
	[[nodiscard]] inline       auto   get_command()     const noexcept { return (gsl::narrow_cast<std::size_t>(std::atoll(gsl::span{ m_data }.subspan<HEADER_LENGTH>().data()))); }
	[[nodiscard]] inline       auto   get_args()              noexcept { return (gsl::span{ m_data }.subspan<HEADER_LENGTH + COMMAND_LENGTH + SPACE_LENGTH>()); };
	[[nodiscard]] inline const auto   get_args()        const noexcept { return (gsl::span{ m_data }.subspan<HEADER_LENGTH + COMMAND_LENGTH + SPACE_LENGTH>()); };
	[[nodiscard]] inline std::size_t  get_length()      const noexcept { return (HEADER_LENGTH + m_body_length); }
	[[nodiscard]] inline std::size_t  get_body_length() const noexcept { return (m_body_length); };

	inline constexpr void set_body_length(std::size_t new_length) noexcept { m_body_length = std::min(new_length, MAX_BODY_LENGTH); }

	void encode_header();
	bool decode_header() noexcept;

	inline void clear_data() { std::fill(std::begin(m_data), std::end(m_data), char{ }); m_body_length = 0; }

private:
	buffer_t    m_data;
	std::size_t m_body_length; //-V122
};

using CMPROTO = CommandMessageProtocol;

/*!
 * \brief  Constructs message "SUCCESS"
 *
 * \return  Message
 *
 * \exception  ???
 */
[[nodiscard]]
std::unique_ptr<CMPROTO> make_success_msg();

/*!
 * \brief  Constructs message "FAILURE"
 *
 * \return  Message
 *
 * \exception  ???
 */
[[nodiscard]]
std::unique_ptr<CMPROTO> make_failure_msg();

#endif /* __COMMANDMESSAGEPROTOCOL_HPP_INCLUDED__ */
