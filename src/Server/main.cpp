#include "..\pch.h" 

//#include "Application.hpp"
#include "..\Network.hpp"
// #pragma comment (lib, "Mswsock.lib")
// #pragma comment(linker, "/MERGE:.rdata=.text")
// #pragma comment(linker, "/FILEALIGN:512 /SECTION:.text,EWRX /IGNORE:4078")
// #pragma comment(linker, "/ENTRY:WinMain")

int __cdecl main(int argc, char **argv)
{
	/*signal(SIGINT, shutdown);

	boost::asio::io_service io;
	boost::asio::io_service::work work(io);

	boost::asio::ip::tcp::acceptor acceptor(io, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
	boost::asio::ip::tcp::socket socket(io);

	// accept 1 client
	std::vector<unsigned char> buffer(2048, 0);
	acceptor.async_accept(socket, [&socket, &buffer](boost::system::error_code ec)
	{
		// options
		socket.set_option(boost::asio::ip::tcp::no_delay(true));
		socket.set_option(boost::asio::socket_base::receive_buffer_size(1920 * 1080 * 4));
		socket.set_option(boost::asio::socket_base::send_buffer_size(1920 * 1080 * 4));

		socket.async_receive(
			boost::asio::buffer(buffer, 2048),
			0,
			boost::bind(justReceive, _1, _2, boost::ref(socket),
				boost::ref(buffer)));
	});

	while (keepGoing)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	io.stop();
	*/
	try
	{
		TCPServer server("");
		server.accept();
	}
	catch (...)
	{
		std::cerr << "Unhandled exception\n";
	}
	/*Application app;
	if (!app.init())
	{
		system("pause");
		return -1;
	}
		
	app.run();
	*/
	system("pause");
	return 0;
}

