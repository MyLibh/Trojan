// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\..\Service\pch.hpp"

#include "ImageMessageProtocol.hpp"

ImageMessageProtocol::ImageMessageProtocol() noexcept :
	m_chunk_num{ 0ull },
	m_data_length{ 0ull },
	m_data{ },
	m_chunk{ }
{ }

[[nodiscard]]
char *ImageMessageProtocol::get_chunk(std::size_t chunk) const 
{
	if (m_chunk_num < chunk)
		return nullptr;

	const auto size{ (chunk == m_chunk_num ? m_data_length % CHUNK_SIZE : 0ull) };
	
	std::copy_n(std::begin(get_data().subspan(chunk * CHUNK_SIZE + size)), (size == 0ull) ? CHUNK_SIZE : size, m_chunk);
	return (m_chunk);
}

[[nodiscard]]
inline std::size_t ImageMessageProtocol::get_chunk_size(std::size_t chunk) const
{
	if (m_chunk_num < chunk)
		throw std::length_error("'chunk' is greater than 'm_chunk_num'\n");

	return (HEADER_LENGTH + (chunk == m_chunk_num ? m_data_length % CHUNK_SIZE : CHUNK_SIZE));
}

bool ImageMessageProtocol::encode_header(std::size_t chunk) const
{
	if (m_chunk_num < chunk)
		return false;

	char header[HEADER_LENGTH + 1]{ };
	if(chunk == 0)
		sprintf_s(header, "%3zd %4zd", m_chunk_num, m_data_length % CHUNK_SIZE); // NumberOfChunks + ' ' + LastChunkSize
	else
		sprintf_s(header, "%3zd %4zd", chunk, get_chunk_size(chunk)); // ChunkNumber + ' ' + ChunkSize

	std::copy_n(header, IMPROTO::HEADER_LENGTH, m_chunk);

	return true;
}

bool ImageMessageProtocol::decode_header(std::size_t chunk) noexcept
{
	char header[HEADER_LENGTH + 1]{ };
	strncat_s(header, m_chunk, HEADER_LENGTH);

	if (chunk == 0)
	{
		m_chunk_num = std::atoi(header);
		m_data_length = (m_chunk_num - 1) * CHUNK_SIZE + std::atoi(gsl::span<char>(header, HEADER_LENGTH + 1).subspan(4).data()); // 4: NumberOfChunks/ChunkNumber + ' '.(to get LastChunkSize/ChunkSize) [see ImageMessageProtocol::encode_header] //-V112
		if (m_data_length > MAX_DATA_LENGTH)
		{
			m_data_length = 0;

			return false;
		}
	}
	else if (m_chunk_num < std::atoi(header))
		return false;

	return true;
}

