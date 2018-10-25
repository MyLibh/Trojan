#pragma once

#ifndef __LOG_HPP_INCLUDED__
#define __LOG_HPP_INCLUDED__

#define LOG(severity) BOOST_LOG_TRIVIAL(severity) 

void InitLog(const std::filesystem::path &filename);

#endif /* __LOG_HPP_INCLUDED__ */