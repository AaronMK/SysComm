#ifndef _SYS_COMM_PRIVATE_COMMON_H_
#define _SYS_COMM_PRIVATE_COMMON_H_

#include <SysComm/SysComm.h>
#include <IpComm/IpAddress.h>

#include <map>
#include <string>

namespace SysComm
{
	/**
	 * @brief
	 *  Obtains a numeric ID that is unique within the loaded instance of the library.
	 */
	uid_t getUid();
}

#endif // _SYS_COMM_PRIVATE_COMMON_H_