#include <SysComm/Link.h>
#include "..\include\SysComm\Link.h"

namespace SysComm
{
	Link::Link()
	{
	}

	Link::~Link()
	{
	}

	uint32_t Link::password() const
	{
		return 0;
	}

	void Link::bind(const LinkPoint* linkpoint, Client* client)
	{
		if (mClientInternal)
			throw StdExt::invalid_operation("Attempting to bind a link that is already binded.");
	}

	void Link::unbind()
	{
	}
}
