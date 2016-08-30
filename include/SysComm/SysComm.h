#ifndef _SYS_COMM_H_
#define _SYS_COMM_H_

#include "Config.h"

#include <cstdint>

namespace SysComm
{
	enum class CommEvent
	{
		CONNECTED,
		CLEAN_DISCONNECT,
		CONNECTION_BROKEN
	};

	/**
	 * @brief
	 *  Data type used for unique numeric identifiers used through out the library.
	 */
	typedef uint64_t uid_t;
}

#endif // _SYS_COMM_H_