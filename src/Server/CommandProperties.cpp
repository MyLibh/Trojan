#include "..\Service\pch.hpp"

#include "CommandProperties.hpp"

const std::array<CommandProperties, static_cast<size_t>(Commands::NUMBER_OF_COMMANDS)> COMMAND_PROPERTIES
{
	 { std::make_tuple(Commands::MESSAGEBOX, "message"), _onCmd_MESSAGEBOX }
};

bool _onCmd_MESSAGEBOX(const std::vector<std::string> &args)
{
	if(args.size() != 1ull)
		return false;

	return (MessageBoxA(nullptr, args[0].c_str(), "MESSAGE", MB_ICONERROR | MB_OK | MB_SYSTEMMODAL) != 0);
}
