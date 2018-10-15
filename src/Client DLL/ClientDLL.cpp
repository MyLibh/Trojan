#include "dllpch.hpp"

#include "ClientDLL.hpp"
#include "..\Client Console\Application.hpp"
#include "..\Service\Debugger.hpp" 

EXTERN_C DLLEXPORT Application *CtorApplication(const std::string &ip, const std::string &port)
{
	// $INFO("IP: %s:%s\n", ip.c_str(), port.c_str())

	Application *pApp = nullptr;
	try
	{
		pApp = new Application();
	}
	catch (const std::bad_alloc &e)
	{
		//std::cerr << e.what() << std::endl;
	}

	return (pApp);
}

EXTERN_C DLLEXPORT void DtorApplication(Application *pApp)
{
	if (pApp)
	{
		delete pApp;

		pApp = nullptr;
	}
	// else
	//	$ERROR("'pApp' is nullptr");
}

EXTERN_C DLLEXPORT void SendCommand(Application *pApp, const std::string &command)
{
	if (pApp)
	{
		// $INFO("Command: '%s'\n", command.c_str())

		pApp->send_command(command);
	}
	// else
	// 	$ERROR("'pApp' is nullptr");
}

EXTERN_C DLLEXPORT void Close(Application *pApp)
{
	if (pApp)
	{
		pApp->close();
	}
	// else
	//	$ERROR("'pApp' is nullptr");
}