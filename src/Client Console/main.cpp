// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\Service\pch.hpp"

#include "Client.hpp"
#include "..\Service\Log.hpp"
#include "..\Service\Constants.hpp"

// _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

int __cdecl main(int argc, char **argv)
{
	const std::filesystem::path CLIENT_LOG_FMT_FILEPATH{ CLIENT_LOG_FMT_FILENAME };
	InitLog(CLIENT_LOG_FMT_FILEPATH);

	LOG(info) << "Client started";
	try
	{
		std::shared_ptr<Client> app;

		if (argc < 3)
		{
			LOG(warning) << "Usage: client [server_ip] [port]";

			app = Client::create();
		}
		else
		{
			const gsl::span<char*> span(argv, argc);
			app = Client::create(span.at(1), span.at(2));
		}

		app->run();

		app->close();
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unhandled exception\n";
	}

	LOG(info) << "Client finished";

	system("pause");
	return 0;
}
