#ifndef _SYS_COMM_LINK_H_
#define _SYS_COMM_LINK_H_

#include "Config.h"
#include "LinkPoint.h"

#include <StdExt/Any.h>

#include <memory>

namespace SysComm
{
	class SYS_COMM_EXPORT Link
	{
		friend class Client;
		friend class ClientInternal;
	private:
		std::shared_ptr<ClientInternal> mClientInternal;

	public:
		enum class Permission
		{
			Open,
			ExclusivePublish,
			ExclusiveReceive
		};

		Link();
		virtual ~Link();

		virtual StdExt::Any handleUpdate(const StdExt::Any& update) = 0;

		virtual Permission permission() const = 0;

		virtual uint32_t password() const;

	protected:
		void bind(const LinkPoint* linkpoint, Client* client);
		void unbind();
	};
}

#endif // _SYS_COMM_LINK_H_