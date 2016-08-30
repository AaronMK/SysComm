#include <SysComm/Internal/DataPoint.h>

#include "private_include/PrivateCommon.h"

namespace SysComm
{
	DataPointBase::DataPointBase()
	{
		mID = getUid();
	}

	DataPointBase::~DataPointBase()
	{

	}
}