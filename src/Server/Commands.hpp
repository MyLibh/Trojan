#pragma once

#ifndef __COMMANDS_HPP_INCLUDED__
#define __COMMANDS_HPP_INCLUDED__

enum class Command
{
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

	NUMBER_OF_COMMAND,
	UNDEFINEDCMD = -1
};

// boost::bimaps::bimap

template<typename T>
using command_props_t = std::tuple<std::pair<Command, std::string>, std::variant<std::function<int(std::optional<T>)>, std::thread>>;

#endif /* __COMMANDS_HPP_INCLUDED__ */