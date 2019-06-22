#ifndef _SYS_COMM_SERVER_H_
#define _SYS_COMM_SERVER_H_

#include "Config.h"

#include <IpComm/IpAddress.h>

#include <Memory>

namespace SysComm
{
	class ServerInternal;

	class SYS_COMM_EXPORT Server
	{
	public:
		Server();
		virtual ~Server();

		void uplink(const IpComm::IpAddress& addr, IpComm::Port);
		void disconnect();

		std::shared_ptr<ServerInternal> mInternal;
	};
}

#endif // _SYS_COMM_SERVER_H_