#include <SysComm/LinkPoint.h>

namespace SysComm
{
	LinkPoint::LinkPoint(const StdExt::String& pName)
		: mName(pName)
	{

	}

	LinkPoint::~LinkPoint()
	{
	}

	const StdExt::String& LinkPoint::name() const
	{
		return mName;
	}
}