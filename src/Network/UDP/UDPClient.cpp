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

void UDPClient::send(const std::shared_ptr<CMPROTO> &msg)
{
	std::thread t(
		[this, &msg]()
		{		
			std::unique_ptr<UDPParticipiant> client{ std::make_unique<UDPParticipiant>(m_io, m_endpoint) };
			client->send(msg);

			std::shared_ptr<IMPROTO> imsg{ std::make_shared<IMPROTO>() };
			while (true)
			{
				imsg->clear_data();

				client->recv(imsg);
				$info std::cout << "[THREAD " << std::this_thread::get_id() << "] Recieved " << imsg->get_data_length() << " bytes\n";

				std::cout.write(imsg->get_data().data(), imsg->get_data_length());
			}
		});

	t.detach();
}
