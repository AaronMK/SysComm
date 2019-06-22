#ifndef _SYS_COMM_LINK_POINT_H_
#define _SYS_COMM_LINK_POINT_H_

#include "SysComm.h"

#include <Serialize/Binary/Binary.h>
#include <Serialize/Binary/ByteStream.h>

#include <StdExt/Any.h>
#include <StdExt/Buffer.h>
#include <StdExt/String.h>
#include <StdExt/InPlace.h>

#include <type_traits>

namespace SysComm
{
	class SYS_COMM_EXPORT LinkPoint
	{
	protected:
		LinkPoint(const StdExt::String& pName);
		virtual ~LinkPoint();

	public:
		using Container = StdExt::InPlace<LinkPoint, 2 * sizeof(StdExt::String)>;
		virtual Container clone() const = 0;

		const StdExt::String& name() const;

		virtual StdExt::Any deserializeInput(Serialize::Binary::ByteStream* inStream) const = 0;
		virtual void serializeOutput(const StdExt::Any& value, Serialize::Binary::ByteStream* outStream) const = 0;

		virtual bool sendResponse() const = 0;

	private:
		StdExt::String mName;
	};
}

#endif // _SYS_COMM_LINK_POINT_H_