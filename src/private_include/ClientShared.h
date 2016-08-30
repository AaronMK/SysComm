#ifndef _SYS_COMM_CLIENT_SHARED_H_
#define _SYS_COMM_CLIENT_SHARED_H_

#include "PrivateCommon.h"

#include <SysComm/Client.h>
#include <SysComm/Internal/DataPoint.h>

#include <Concurrent/Task.h>
#include <Concurrent/Reference.h>

#include <memory>
#include <atomic>

namespace SysComm
{
	/**
	 * @internal
	 *
	 * @brief
	 *  Handles the actual communication between any number of Client objects to a SysComm Server
	 *  on a given IP/port.
	 *  
	 *  A ClientShared object maintains a single tcp/ip connection to a remote Server.  This minimizes
	 *  the number of threads and resources even if an application has many seperate modules connecting
	 *  to the same Server.
	 */
	class ClientShared
	{
	public:
		virtual ~ClientShared();

		/**
		 * @brief
		 *  Increments the reference count to and returns a ClientInternal object for a given
		 *  IP address and port.  The ClientInternal object is created
		 *  if it does not exist.
		 */
		static ClientShared* acquire(const IpPort &key);

		/**
		 * @brief
		 *  Decrements the reference count for a ClientInternal object, deleting
		 *  the object if the count reaches zero.
		 */
		static void release(ClientShared* ptrCI);

	private:
		ClientShared();

		IpPort mIpPort;
		std::atomic<uint32_t> mRefcount;

		std::map<Client*, Client::StatusHandler> mStatusHandlers;
	};

	Concurrent::Reference<ClientShared> acquireInternalClient(const IpPort &key);

	void releaseInternalClient(const IpPort &key);
}

#endif // _SYS_COMM_CLIENT_SHARED_H_