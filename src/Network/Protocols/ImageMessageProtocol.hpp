#pragma once

#ifndef __IMAGEMESSAGEPROTOCOL_HPP_INCLUDED__
#define __IMAGEMESSAGEPROTOCOL_HPP_INCLUDED__

class ImageMessageProtocol
{
public:
	inline static constexpr std::size_t CHUNK_SIZE      = 4096;
	inline static constexpr std::size_t HEADER_LENGTH   = 8;
	inline static constexpr std::size_t MAX_DATA_LENGTH = 500000;

	using  span = gsl::span<      char, MAX_DATA_LENGTH>;
	using cspan = gsl::span<const char, MAX_DATA_LENGTH>;

public:
	ImageMessageProtocol() noexcept;

	[[nodiscard]] inline       auto   get_data()                              noexcept { return ( span(m_data)); }
	[[nodiscard]] inline const auto   get_data()                        const noexcept { return (cspan(m_data)); }
	[[nodiscard]] inline std::size_t  get_data_length()                 const noexcept { return (m_data_length); };
	[[nodiscard]] inline std::size_t  get_length()                      const noexcept { return (HEADER_LENGTH + m_data_length); }
	[[nodiscard]] inline std::size_t  get_chunk_num()                   const noexcept { return (m_chunk_num); }
	[[nodiscard]] char               *get_chunk(std::size_t chunk)      const;
	[[nodiscard]] std::size_t         get_chunk_size(std::size_t chunk) const;

	inline void set_data_length(std::size_t new_length) { m_data_length = std::min(new_length, MAX_DATA_LENGTH); m_chunk_num = static_cast<std::size_t>(std::ceil(m_data_length / CHUNK_SIZE)); }

	bool encode_header(std::size_t chunk) const;
	bool decode_header(std::size_t chunk) noexcept;

	inline void clear_data() { std::fill(std::begin(m_data), std::end(m_data), char{}); m_data_length = 0; }

private:
	std::size_t  m_chunk_num;   //-V122
	std::size_t  m_data_length; //-V122
	char         m_data[MAX_DATA_LENGTH];
	mutable char m_chunk[HEADER_LENGTH + CHUNK_SIZE];
};

using IMPROTO = ImageMessageProtocol;

#endif /* __IMAGEMESSAGEPROTOCOL_HPP_INCLUDED__ */