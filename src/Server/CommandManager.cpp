#include "..\Service\pch.hpp"

#include "CommandManager.hpp"
#include "..\Network\Protocols\CommandMessageProtocol.hpp"
#include "..\Service\Debugger.hpp"

CommandManager::CommandManager() :
	m_in_progress(0)
{ }

bool CommandManager::execute_command(const CMPROTO *msg)
{
	Commands cmd = static_cast<Commands>(msg->get_command()); // TODO: enum overrage set check
	if (cmd == Commands::UNDEFINED_COMMAND || cmd >= Commands::NUMBER_OF_COMMANDS)
	{
		$ERROR("Wrong command: %llu", static_cast<size_t>(cmd))

		return false;
	}

	auto iter = std::find_if(std::begin(COMMAND_PROPERTIES), std::end(COMMAND_PROPERTIES), [cmd](const auto &cmd_prop) { return (cmd == std::get<0>(cmd_prop.command)); });
	if (iter != std::end(COMMAND_PROPERTIES))
	{
		if (iter->exec_func.index() == 0) // CommandProperties::exec_func_t
			return std::get<0>(iter->exec_func)(parse_args(msg->get_args()));
		else // CommandProperties::threaded_exec_func_t
		{
			auto pos = static_cast<size_t>(get_bit(cmd));
			m_in_progress.set(pos, get_bit_new_value(cmd));
			
			// std::thread t(std::get<1>(iter->exec_func), std::ref(args), std::ref(m_in_progress), pos);
			// t.detach();
		}
	}

	return true;
}

std::vector<std::string> CommandManager::parse_args(const char *args)
{
	return { { args } };
}

CIP_BITS CommandManager::get_bit(Commands command)
{
	switch (command) // Don't check 'UNDEFINED_COMMAND' & 'NUMBER_OF_COMMANDS', becuase it is checked in 'execute_command'
	{
	case Commands::VIEWDESKTOP_START: 
	case Commands::VIEWDESKTOP_STOP:
		return CIP_BITS::DESKTOP_VIEW;

	case Commands::VIEWWEBCAM_START:
	case Commands::VIEWWEBCAM_STOP:
		return CIP_BITS::WEBCAM_VIEW;

	default:
		throw std::exception(__FUNCTION__);
	}
}

bool CommandManager::get_bit_new_value(Commands command)
{
	switch (command)
	{
	case Commands::VIEWDESKTOP_START:
	case Commands::VIEWWEBCAM_START:
		return true;

	case Commands::VIEWDESKTOP_STOP:
	case Commands::VIEWWEBCAM_STOP:
		return false;
		
	default:
		throw std::exception(__FUNCTION__);
	}
}
