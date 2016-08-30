#include "private_include/PrivateCommon.h"

#include <atomic>

namespace SysComm
{
	static std::atomic<uid_t> nextUid(1);

	uid_t getUid()
	{
		return nextUid.fetch_add(1);
	}
}