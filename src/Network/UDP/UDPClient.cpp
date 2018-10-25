// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\..\Service\pch.hpp"

#include "UDPClient.hpp"
#include "UDPParticipiant.hpp"
#include "..\Protocols\CommandMessageProtocol.hpp"
#include "..\Protocols\ImageMessageProtocol.hpp"
#include "..\..\Service\Debugger.hpp"

UDPClient::UDPClient(boost::asio::io_context &io_context, const boost::asio::ip::udp::resolver::results_type &endpoint) :
	m_io{ io_context },
	m_endpoint{ *endpoint }
{ }

void UDPClient::send(const CMPROTO *msg)
{
	std::thread t(
		[this, &msg]()
		{
			UDPParticipiant client(m_io, m_endpoint);
			client.send(msg);
			while (true)
			{
				IMPROTO *imsg = new IMPROTO;
				client.recv(imsg);
				$info std::cout << "[THREAD " << std::this_thread::get_id() << "] Recieved " << imsg->get_body_length() << " bytes\n";

				std::copy(imsg->get_body(), imsg->get_body() + imsg->get_body_length(), std::ostream_iterator<char>(std::cout, ""));
				delete imsg;
			}
		});

	t.detach();
}
