#ifndef _SYS_COMM_MESSAGES_H_
#define _SYS_COMM_MESSAGES_H_

#include <StdExt/UID.h>
#include <StdExt/Buffer.h>
#include <StdExt/Span.h>

#include <Serialize/Binary/Binary.h>
#include <Serialize/Binary/ByteStream.h>

#include <IpComm/IpEndPoint.h>

namespace SysComm
{
	struct NodeEndpoint
	{
		StdExt::UID::uid_t Tag;
		IpComm::IpEndPoint IP;

		NodeEndpoint() noexcept;

		bool operator<(const NodeEndpoint& other) const;
		bool operator==(const NodeEndpoint& other) const;
		bool operator!=(const NodeEndpoint& other) const;
	};

	enum class message_t
	{
		NONE = 0,
		
	};

	struct Packet
	{
		message_t Type;
		Serialize::Binary::bytesize_t ActiveSize;
		StdExt::Buffer PayloadBuffer;
	};

	class Message
	{
	public:
		NodeEndpoint Source;
		NodeEndpoint Destination;
		message_t Type;

		Message() noexcept;
		virtual ~Message();
	};
}

namespace Serialize::Binary
{
	template<>
	void read<SysComm::Packet>(ByteStream* stream, SysComm::Packet* out);

	template<>
	void write<SysComm::Packet>(ByteStream* stream, const SysComm::Packet& val);
}

#endif // !_SYS_COMM_MESSAGES_H_
