#include <SysComm/Server.h>

#include "ServerInternal.h"

namespace SysComm
{
	Server::Server()
	{
		mInternal = std::make_shared<ServerInternal>();
	}

	Server::~Server()
	{
	}

	void Server::uplink(const IpComm::IpAddress& addr, IpComm::Port)
	{
	}

	void Server::disconnect()
	{
	}
}