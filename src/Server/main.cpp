// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\Service\pch.hpp" 

#include "Server.hpp"
#include "..\Service\Log.hpp"
#include "..\Service\Constants.hpp"

/*************************************************************************************************************************************************************************************************************/
int __cdecl main(int argc, char **argv)
{
	InitLog(SERVER_LOG_FMT_FILENAME);

	LOG(info) << "Server started";
	try
	{
		std::shared_ptr<Server> app;

		if (argc < 2)
		{
			LOG(warning) << "Usage: server [port]";

			app = Server::create(DEFAULT_PORT);
		}
		else
		{
			const gsl::span<char*> span(argv, argc);
			app = Server::create(span.at(1));
		}

		app->run();

		app->close();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unhandled exception\n";
	}

	system("pause");
	return 0;
}

