// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\..\Service\pch.hpp"

#include "ImageMessageProtocol.hpp"

ImageMessageProtocol::ImageMessageProtocol() :
	m_chunk_num{ 0ull },
	m_body_length{ 0ull },
	m_data{ },
	m_chunk{ }
{ }

[[nodiscard]]
char *ImageMessageProtocol::get_chunk(size_t chunk)
{
	if (m_chunk_num < chunk)
		return nullptr;

	auto size{ (chunk == m_chunk_num ? m_body_length % CHUNK_SIZE : 0) };
	std::memcpy(m_chunk, m_data + HEADER_LENGTH + chunk * CHUNK_SIZE + size, (!size ? CHUNK_SIZE : size));

	return (m_chunk);
}

[[nodiscard]]
inline size_t ImageMessageProtocol::get_chunk_size(size_t chunk) const
{
	if (m_chunk_num < chunk)
		throw std::length_error("'chunk' is greater than 'm_chunk_num'\n");

	return (HEADER_LENGTH + (chunk == m_chunk_num ? m_body_length % CHUNK_SIZE : CHUNK_SIZE));
}

bool ImageMessageProtocol::encode_header(size_t chunk)
{
	if (m_chunk_num < chunk)
		return false;

	char header[HEADER_LENGTH + 1]{ };
	if(!chunk)
		sprintf_s(header, "%3d %4d", static_cast<int>(m_chunk_num), static_cast<int>(m_body_length % CHUNK_SIZE));
	else
		sprintf_s(header, "%3d %4d", static_cast<int>(chunk), static_cast<int>(get_chunk_size(chunk)));
	std::memcpy(m_chunk, header, HEADER_LENGTH);

	return true;
}

bool ImageMessageProtocol::decode_header(size_t chunk)
{
	char header[HEADER_LENGTH + 1]{ };
	strncat_s(header, m_chunk, HEADER_LENGTH);

	if (!chunk)
	{
		m_chunk_num = std::atoi(header);
		m_body_length = (m_chunk_num - 1) * CHUNK_SIZE + std::atoi(header + 4);
		if (m_body_length > MAX_BODY_LENGTH)
		{
			m_body_length = 0;

			return false;
		}
	}
	else if (m_chunk_num < std::atoi(header))
		return false;

	return true;
}

