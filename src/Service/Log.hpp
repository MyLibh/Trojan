#pragma once

#ifndef __LOG_HPP_INCLUDED__
#define __LOG_HPP_INCLUDED__

//! Macro analogue
#define LOG(severity) BOOST_LOG_TRIVIAL(severity) 

/*!
 * \brief Initializes the logger
 *
 * \param[in]  filename  Formated string for the name of log file
 *
 * \exception  ???
 */
void InitLog(const std::string_view filename);

#endif /* __LOG_HPP_INCLUDED__ */