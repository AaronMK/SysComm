#ifndef _SYS_COMM_CLIENT_INTERNAL_H_
#define _SYS_COMM_CLIENT_INTERNAL_H_ 

#include <SysComm/Link.h>
#include <SysComm/Client.h>
#include <SysComm/LinkPoint.h>

#include <Concurrent/Queue.h>
#include <Concurrent/RWLock.h>
#include <Concurrent/MessageLoop.h>

#include <StdExt/Signals/Event.h>
#include <StdExt/Any.h>
#include <StdExt/UID.h>

#include <variant>
#include <map>

namespace SysComm
{
	class ClientInternal
	{

	public:
		using message_t = std::function<void()>;

		ClientInternal(Client::HandlingContext);

		void enqueueMessage(const message_t& msg);
		void enqueueMessage(message_t&& msg);

		void bind(Link* link, LinkPoint* lp);

		StdExt::UID uid;

	private:
		using loop_t = Concurrent::MessageLoop<message_t>;
		using queue_t = Concurrent::Queue<message_t>;

		struct LPRecord
		{
			LinkPoint::Container LinkPoint;
			StdExt::Signals::Event<const StdExt::Any&> LocalSubscribers;
			StdExt::Signals::Event<const StdExt::Buffer&> RemoteSubscribers;
			StdExt::Any Value;
			uint32_t Passcode = 0;
		};

		Concurrent::RWLock mRecordsLock;
		std::map<StdExt::String, LPRecord> mRecords;

		Client::HandlingContext mHandlingContext;

		std::variant<std::monostate, loop_t, queue_t> mQueue;

		void handleMessage(const message_t& msg);
	};
}

#endif // _SYS_COMM_CLIENT_INTERNAL_H_
