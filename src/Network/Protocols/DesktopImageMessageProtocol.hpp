#pragma once

#ifndef __DESKTOPIMAGEMESSAGEPROTOCOL_HPP_INCLUDED__
#define __DESKTOPIMAGEMESSAGEPROTOCOL_HPP_INCLUDED__

class DesktopImageMessageProtocol
{
public:
	static constexpr size_t CHUNK_SIZE    = 4096;
	static constexpr size_t HEADER_LENGTH = 8;
	static constexpr size_t MAX_BODY_LENGTH = 65555;

	DesktopImageMessageProtocol();

	inline       char *get_data()                         { return (m_data); }
	inline const char *get_data()                   const { return (m_data); }
	inline       char *get_body()                         { return (m_data + HEADER_LENGTH); }
	inline const char *get_body()                   const { return (m_data + HEADER_LENGTH); }
	inline size_t      get_chunk_num()              const { return (m_chunk_num); }
	inline size_t      get_length()                 const { return (HEADER_LENGTH + m_body_length); }
	inline size_t      get_body_length()            const { return (m_body_length); };

	inline const char *get_chunk(size_t chunk) const { return (get_chunk(chunk)); }
	             char *get_chunk(size_t chunk);

	size_t get_chunk_size(size_t chunk) const;

	inline void set_body_length(size_t new_length) { m_body_length = /* std:: */ min(new_length, MAX_BODY_LENGTH); m_chunk_num = static_cast<size_t>(std::ceil(m_body_length / CHUNK_SIZE)); }

	bool encode_header(size_t chunk);
	bool decode_header(size_t chunk);

private:
	size_t m_chunk_num;
	size_t m_body_length;
	char   m_data[MAX_BODY_LENGTH];
	char   m_chunk[HEADER_LENGTH +  CHUNK_SIZE];
};

#endif /* __DESKTOPIMAGEMESSAGEPROTOCOL_HPP_INCLUDED__ */