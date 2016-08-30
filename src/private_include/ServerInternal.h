#ifndef _SYS_COMM_SERVER_INTERNAL_H_
#define _SYS_COMM_SERVER_INTERNAL_H_

#include <SysComm/SysComm.h>
#include <SysComm/ByteArray.h>

#include <IpComm/TcpServer.h>
#include <IpComm/IpAddress.h>

#include <Concurrent/Queue.h>

#include <sqlite3.h>

#include <map>
#include <string>

namespace SysComm
{
	/**
	 * @brief
	 *  Accepts connections from clients, processes messages, and serves as a
	 *  repository for all global data.
	 */
	class ServerInternal
	{
	public:
		ServerInternal();
		virtual ~ServerInternal();
	};
}

#endif // _SYS_COMM_SERVER_INTERNAL_H_
