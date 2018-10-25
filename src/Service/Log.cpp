// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "pch.hpp"

#include "Log.hpp"

void InitLog(const std::filesystem::path &filename)
{
	boost::log::add_common_attributes();

	boost::log::core::get()->add_global_attribute("Scope", boost::log::attributes::named_scope());

	auto fmtTimeStamp = boost::log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f");
	auto fmtThreadId = boost::log::expressions::attr<boost::log::attributes::current_thread_id::value_type>("ThreadID");
	auto fmtSeverity = boost::log::expressions::attr<boost::log::trivial::severity_level>("Severity");
	auto fmtScope = boost::log::expressions::format_named_scope("Scope",
		boost::log::keywords::format    = "%n(%f:%l)",
		boost::log::keywords::iteration = boost::log::expressions::reverse,
		boost::log::keywords::depth     = 2);

	boost::log::formatter logFmt = boost::log::expressions::format("[%1%]<%2%>[%3%](%4%):  %5%") % fmtTimeStamp % fmtThreadId % fmtSeverity % fmtScope % boost::log::expressions::smessage;

	auto consoleSink = boost::log::add_console_log(std::clog);
	consoleSink->set_formatter(logFmt);

	auto fsSink = boost::log::add_file_log(
		boost::log::keywords::file_name = "test_%Y-%m-%d_%H-%M-%S.%N.log",
		boost::log::keywords::rotation_size = 10 * 1024 * 1024,
		boost::log::keywords::min_free_space = 30 * 1024 * 1024,
		boost::log::keywords::open_mode = std::ios_base::app);

	fsSink->set_formatter(logFmt);
	fsSink->locked_backend()->auto_flush(true);

#ifdef NDEBUG
	boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
#endif
}
