#pragma once

#ifndef __COMMANDMESSAGEPROTOCOL_HPP_INCLUDED__
#define __COMMANDMESSAGEPROTOCOL_HPP_INCLUDED__

class CommandMessageProtocol
{
public:
	inline static constexpr size_t HEADER_LENGTH   = 4; //-V112
	inline static constexpr size_t COMMAND_LENGTH  = 2;
	inline static constexpr size_t SPACE_LENGTH    = 1;
	inline static constexpr size_t MAX_ARGS_LENGTH = 128;
	inline static constexpr size_t MAX_BODY_LENGTH = COMMAND_LENGTH + SPACE_LENGTH + MAX_ARGS_LENGTH;

	CommandMessageProtocol();

	inline       char *get_data()              { return (m_data); }
	inline const char *get_data()        const { return (m_data); }
	inline       char *get_body()              { return (m_data + HEADER_LENGTH); }
	inline const char *get_body()        const { return (m_data + HEADER_LENGTH); }
	inline       int   get_command()     const { return (std::atoi(m_data + HEADER_LENGTH)); }
	inline       char *get_args()              { return (m_data + HEADER_LENGTH + COMMAND_LENGTH + SPACE_LENGTH); };
	inline const char *get_args()        const { return (m_data + HEADER_LENGTH + COMMAND_LENGTH + SPACE_LENGTH); };
	inline size_t      get_length()      const { return (HEADER_LENGTH + m_body_length); }
	inline size_t      get_body_length() const { return (m_body_length); };

	inline void set_body_length(size_t new_length) { m_body_length = /* std:: */ min(new_length, MAX_BODY_LENGTH); }

	void encode_header();
	bool decode_header();

	inline void clear_data() { std::memset(m_data, char{}, HEADER_LENGTH + MAX_BODY_LENGTH); m_body_length = 0; }

private:
	size_t m_body_length; //-V122
	char   m_data[HEADER_LENGTH + MAX_BODY_LENGTH];
};

using CMPROTO = CommandMessageProtocol;

extern const CMPROTO CMPROTO_RESULT_SUCCESS; 
extern const CMPROTO CMPROTO_RESULT_FAILURE;

#endif /* __COMMANDMESSAGEPROTOCOL_HPP_INCLUDED__ */
