#include <SysComm/Client.h>

#include "ClientInternal.h"

#include <Concurrent/ReadLocker.h>
#include <Concurrent/WriteLocker.h>

using namespace std;
using namespace std::placeholders;
using namespace Concurrent;

namespace SysComm
{
	using HandlingContext = Client::HandlingContext;

	ClientInternal::ClientInternal(HandlingContext context)
	{
		mHandlingContext = context;
		
		if (HandlingContext::EventLoop == mHandlingContext)
			mQueue.emplace<loop_t>(std::bind(&ClientInternal::handleMessage, this, _1));
		else if (HandlingContext::Manual == mHandlingContext)
			mQueue.emplace<queue_t>();
	}

	void ClientInternal::handleMessage(const message_t& msg)
	{
		message_t();
	}

	void ClientInternal::enqueueMessage(const message_t& msg)
	{
		if (HandlingContext::EventLoop == mHandlingContext)
			std::get<loop_t>(mQueue).push(msg);
		else if (HandlingContext::Manual == mHandlingContext)
			std::get<queue_t>(mQueue).push(msg);
		else
			handleMessage(msg);
	}

	void ClientInternal::enqueueMessage(message_t&& msg)
	{
		if (HandlingContext::EventLoop == mHandlingContext)
			std::get<loop_t>(mQueue).push(std::move(msg));
		else if (HandlingContext::Manual == mHandlingContext)
			std::get<queue_t>(mQueue).push(std::move(msg));
		else
			handleMessage(msg);
	}

	void ClientInternal::bind(Link* link, LinkPoint* lp)
	{
		WriteLocker lock(&mRecordsLock);

		auto itr = mRecords.find(lp->name());

		if (itr == mRecords.end())
		{

		}
	}

	///////////////////////////////////////////

	Client::Client(HandlingContext context)
	{
		mInternal = make_shared<ClientInternal>(context);
	}

	void Client::connect(Server& server)
	{

	}

	void Client::connect(IpComm::IpAddress, IpComm::Port)
	{

	}

	void Client::processEvents()
	{

	}
}