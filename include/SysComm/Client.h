#ifndef _SYS_COMM_CLIENT_H_
#define _SYS_COMM_CLIENT_H_

#include "Config.h"

#include <IpComm/IpAddress.h>

namespace SysComm
{
	class Server;
	class ClientInternal;

	class SYS_COMM_EXPORT Client
	{
	public:
		enum class HandlingContext
		{
			/**
			 * @brief
			 *  Server calls handlers as soon as messages are received.  When events
			 *  are triggered between two direct clients attached to the same local
			 *  Server object, handling happens inline at the call of the event. 
			 */
			Direct,

			/**
			 * @brief
			 *  The client has an event loop, and handling of events is done in
			 *  that context.
			 */
			EventLoop,

			/**
			 * @brief
			 *  Handling of events happens by a manual call to processEvents()
			 *  and in the context of the calling thread.
			 */
			Manual
		};

		Client(HandlingContext context = HandlingContext::Direct);

		void connect(Server& server);
		void connect(IpComm::IpAddress, IpComm::Port);

		void processEvents();

	private:
		std::shared_ptr<ClientInternal> mInternal;
	};
}

#endif // _SYS_COMM_CLIENT_H_