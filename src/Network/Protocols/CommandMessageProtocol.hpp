#pragma once

#ifndef __COMMANDMESSAGEPROTOCOL_HPP_INCLUDED__
#define __COMMANDMESSAGEPROTOCOL_HPP_INCLUDED__

class CommandMessageProtocol
{
public:
	inline static constexpr std::size_t HEADER_LENGTH   = 4; //-V112
	inline static constexpr std::size_t COMMAND_LENGTH  = 2;
	inline static constexpr std::size_t SPACE_LENGTH    = 1;
	inline static constexpr std::size_t MAX_ARGS_LENGTH = 128;
	inline static constexpr std::size_t MAX_BODY_LENGTH = COMMAND_LENGTH + SPACE_LENGTH + MAX_ARGS_LENGTH;
	inline static constexpr std::size_t MAX_LENGTH      = HEADER_LENGTH + MAX_BODY_LENGTH;

	using  span = gsl::span<      char, MAX_LENGTH>;
	using cspan = gsl::span<const char, MAX_LENGTH>;

public:
	CommandMessageProtocol() noexcept;
	 
	[[nodiscard]] inline       auto  get_data()              noexcept { return ( span(m_data)); }
	[[nodiscard]] inline const auto  get_data()        const noexcept { return (cspan(m_data)); }
	[[nodiscard]] inline       auto  get_body()              noexcept { return ( span(m_data).subspan(HEADER_LENGTH)); }
	[[nodiscard]] inline const auto  get_body()        const noexcept { return (cspan(m_data).subspan(HEADER_LENGTH)); }
	[[nodiscard]] inline       int   get_command()     const noexcept { return (std::atoi(cspan(m_data).subspan(HEADER_LENGTH).data())); }
	[[nodiscard]] inline       auto  get_args()              noexcept { return ( span(m_data).subspan(HEADER_LENGTH + COMMAND_LENGTH + SPACE_LENGTH)); };
	[[nodiscard]] inline const auto  get_args()        const noexcept { return (cspan(m_data).subspan(HEADER_LENGTH + COMMAND_LENGTH + SPACE_LENGTH)); };
	[[nodiscard]] inline std::size_t get_length()      const noexcept { return (HEADER_LENGTH + m_body_length); }
	[[nodiscard]] inline std::size_t get_body_length() const noexcept { return (m_body_length); };

	inline void set_body_length(std::size_t new_length) noexcept { m_body_length = std::min(new_length, MAX_BODY_LENGTH); }

	void encode_header();
	bool decode_header() noexcept;

	inline void clear_data() { std::fill(std::begin(m_data), std::end(m_data), char{}); m_body_length = 0; }

private:
	std::size_t m_body_length;  //-V122
	char        m_data[MAX_LENGTH];
};

using CMPROTO = CommandMessageProtocol;

extern const std::shared_ptr<CMPROTO> CMPROTO_RESULT_SUCCESS; 
extern const std::shared_ptr<CMPROTO> CMPROTO_RESULT_FAILURE;

#endif /* __COMMANDMESSAGEPROTOCOL_HPP_INCLUDED__ */
