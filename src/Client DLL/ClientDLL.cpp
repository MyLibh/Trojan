// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "dllpch.hpp"

#include "ClientDLL.hpp"
#include "..\Client Console\Application.hpp"
#include "..\Service\Debugger.hpp" 

EXTERN_C DLLEXPORT Application *CtorApplication(const char *cpIP, const char *cpPort)
{
	$INFO("IP: %s:%s\n", cpIP, cpPort)

	Application *pApp = nullptr;
	try
	{
		pApp = new Application(cpIP, cpPort);
	}
	catch (const std::bad_alloc &e)
	{
		$ERROR("Exception: %s\n", e.what())
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
	else
		$ERROR("'pApp' is nullptr");
}

EXTERN_C DLLEXPORT void SendCommand(Application *pApp, const char *cpCommand)
{
	if (pApp)
	{
		$INFO("Command: '%s'\n", cpCommand)

		pApp->send_command(cpCommand);
	}
	else
	 	$ERROR("'pApp' is nullptr");
}

EXTERN_C DLLEXPORT void Close(Application *pApp)
{
	if (pApp)
	{
		pApp->close();
	}
	else
		$ERROR("'pApp' is nullptr");
}